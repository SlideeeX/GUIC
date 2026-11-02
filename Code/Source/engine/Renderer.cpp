#include "Guic/engine/Renderer.hpp"
#include "Guic/external/maxrects/MaxRectsBinPack.hpp"
#include <algorithm>
#include <cstring>
#include <SDL2/SDL.h>

#define ATLAS_EXPAND_SIZE 256

namespace guic { namespace engine {
    struct Renderer::Impl {
        SDL_Renderer* renderer = nullptr;

        struct Atlas {
            ~Atlas() {
                if(texture != nullptr) SDL_DestroyTexture(texture);
                if(bin != nullptr) delete bin;
            };

            bool needFlush = false;
            SDL_Texture* texture = nullptr;
            rbp::MaxRectsBinPack* bin = nullptr;

            std::vector<Uint8> pixels;
            Uint16 width = 0;
            Uint16 height = 0;

            Atlas(SDL_Renderer* renderer){
                this->width = ATLAS_EXPAND_SIZE;
                this->height = ATLAS_EXPAND_SIZE;
                pixels.assign(size_t(width) * height * 4, 0);

                texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, this->width, this->height);

                SDL_SetTextureBlendMode(
                    texture,
                    SDL_BLENDMODE_BLEND
                );

                SDL_RendererInfo info;
                SDL_GetRendererInfo(renderer, &info);

                bin = new rbp::MaxRectsBinPack();
                bin->Init(info.max_texture_width, info.max_texture_height, false);
            }
        };

        struct AtlasDock {
            Atlas* atlas = nullptr;
            Uint16 x = 0;
            Uint16 y = 0;
            Uint16 width = 0;
            Uint16 height = 0;
        };

        // Владение страницами: Impl удаляет их в деструкторе Renderer.
        std::vector<Atlas*> atlases;

        struct LoadedResource {
            Resource* resource = nullptr;
            AtlasDock dock;
            Uint32 revision = 0;
        };

        std::vector<LoadedResource> loadedResources;

        // Площадь, освобождённая выгрузкой с прошлой перестройки атласов (в пикселях).
        Uint64 freedArea = 0;

        Uint64 maxTextureArea() {
            SDL_RendererInfo info;
            SDL_GetRendererInfo(renderer, &info);
            return Uint64(info.max_texture_width) * info.max_texture_height;
        }

        Atlas* createAtlas() {
            atlases.push_back(new Atlas(renderer));
            return atlases.back();
        }

        // Возвращает место под ресурс. Если dock.atlas == nullptr — ресурс не помещается даже в максимальную страницу.
        AtlasDock getAtlasDock(Uint16 width, Uint16 height) {
            AtlasDock dock;

            for(size_t i=0; i<atlases.size(); i++){
                Rect rect = atlases[i]->bin->Insert(width, height, rbp::MaxRectsBinPack::RectBestAreaFit);
                if(rect.width>0){
                    dock.x = rect.x;
                    dock.y = rect.y;
                    dock.width = rect.width;
                    dock.height = rect.height;
                    dock.atlas = atlases[i];

                    return dock;
                }
            }

            Atlas* atlas = createAtlas();
            Rect rect = atlas->bin->Insert(width, height, rbp::MaxRectsBinPack::RectBestAreaFit);

            // Ресурс не помещается даже в пустую страницу (или пустой): страницу убираем.
            if (rect.width <= 0 || rect.height <= 0) {
                atlases.pop_back();
                delete atlas;
                return AtlasDock();
            }

            dock.x = rect.x;
            dock.y = rect.y;
            dock.width = rect.width;
            dock.height = rect.height;
            dock.atlas = atlas;

            return dock;
        };

        // Возвращает false, если страницу не удалось расширить до нужного размера: пиксели не пишутся.
        bool setAtlasDock(AtlasDock dock, const std::vector<Uint8>& pixels) {
            Atlas* atlas = dock.atlas;

            const Uint16 requiredWidth  = dock.x + dock.width;
            const Uint16 requiredHeight = dock.y + dock.height;

            if (requiredWidth > atlas->width || requiredHeight > atlas->height){
                if (!growAtlas(atlas, requiredWidth, requiredHeight)) return false;
            }

            for (Uint16 y = 0; y < dock.height; y++)
            {
                memcpy(
                    &atlas->pixels[(size_t(dock.y + y) * atlas->width + dock.x) * 4],
                    &pixels[size_t(y) * dock.width * 4],
                    size_t(dock.width) * 4
                );
            }

            atlas->needFlush = true;
            return true;
        }

        void load(const std::vector<Resource*>& resources)
        {
            for(Resource* resource : resources){
                bool foundRes = false;

                for (auto it = loadedResources.begin(); it != loadedResources.end(); ++it)
                {
                    if (it->resource == resource) {
                        foundRes = true;
                        break;
                    }
                }

                if(foundRes) continue;

                AtlasDock dock;
                const Bitmap* bitmap = resource->load();

                if (bitmap != nullptr) {
                    dock = getAtlasDock(bitmap->width, bitmap->height);
                    if (dock.atlas && !setAtlasDock(dock, bitmap->pixels)) dock = AtlasDock();
                    resource->unload();
                }

                loadedResources.push_back({
                    resource,
                    dock,
                    resource->getRevision()
                });
            }
        }

        void unload(const std::vector<Resource*>& resources)
        {
            for(const Resource* resource : resources){
                for (auto it = loadedResources.begin(); it != loadedResources.end(); ++it)
                {
                    if (it->resource == resource) {
                        freedArea += Uint64(it->dock.width) * it->dock.height;
                        loadedResources.erase(it);
                        break;
                    }
                }
            }

            // Перестройка дорогая: делаем её, когда освобождено больше половины максимальной страницы.
            if (freedArea * 2 > maxTextureArea()) rebuild();
        }

        void rebuild()
        {
            // Старые страницы удаляются, их пиксели уже выгружены — ресурсы грузятся заново.
            std::vector<Resource*> resources;
            resources.reserve(loadedResources.size());
            for (const LoadedResource& loaded : loadedResources) resources.push_back(loaded.resource);

            loadedResources.clear();

            for (Atlas* atlas : atlases) delete atlas;
            atlases.clear();
            freedArea = 0;

            load(resources);
        }

        // Меняет только GPU-текстуру: координаты в пакере и ожидающие загрузки пиксели не трогаются.
        bool resizeAtlas(Atlas* atlas, Uint16 width, Uint16 height)
        {
            SDL_Texture* next = SDL_CreateTexture(
                renderer,
                SDL_PIXELFORMAT_RGBA32,
                SDL_TEXTUREACCESS_TARGET,
                width,
                height
            );

            if (!next) return false;

            SDL_Texture* previousTarget = SDL_GetRenderTarget(renderer);

            if (SDL_SetRenderTarget(renderer, next) < 0) {
                SDL_DestroyTexture(next);
                return false;
            }

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            const bool cleared = SDL_RenderClear(renderer) == 0;

            SDL_BlendMode previousBlend;
            SDL_GetTextureBlendMode(atlas->texture, &previousBlend);
            SDL_SetTextureBlendMode(atlas->texture, SDL_BLENDMODE_NONE);

            SDL_Rect srcdst = SDL_Rect{0, 0, atlas->width, atlas->height};
            const bool copied = cleared && SDL_RenderCopy(renderer, atlas->texture, &srcdst, &srcdst) == 0;

            SDL_SetTextureBlendMode(atlas->texture, previousBlend);
            const bool restored = SDL_SetRenderTarget(renderer, previousTarget) == 0;

            if (!copied || !restored) {
                SDL_DestroyTexture(next);
                return false;
            }

            SDL_SetTextureBlendMode(next, SDL_BLENDMODE_BLEND);

            SDL_DestroyTexture(atlas->texture);
            atlas->texture = next;
            atlas->width = width;
            atlas->height = height;

            return true;
        }

        // Наращивает страницу степенями двойки до размера, вмещающего required*.
        bool growAtlas(Atlas* atlas, Uint16 requiredWidth, Uint16 requiredHeight)
        {
            // int, а не Uint16: иначе сложение может переполниться и цикл не завершится.
            int newWidth = atlas->width;
            int newHeight = atlas->height;

            while (newWidth < requiredWidth) newWidth += ATLAS_EXPAND_SIZE;
            while (newHeight < requiredHeight) newHeight += ATLAS_EXPAND_SIZE;

            if (newWidth > 65535 || newHeight > 65535) return false;
            if (newWidth == atlas->width && newHeight == atlas->height) return true;

            const Uint16 oldWidth = atlas->width;
            const Uint16 oldHeight = atlas->height;

            if (!resizeAtlas(atlas, static_cast<Uint16>(newWidth), static_cast<Uint16>(newHeight))) return false;

            // Пиксели переносятся построчно: строка меняет шаг, а не позицию в атласе.
            std::vector<Uint8> grown(size_t(newWidth) * newHeight * 4, 0);
            for (Uint16 y = 0; y < oldHeight; y++)
            {
                memcpy(
                    &grown[size_t(y) * newWidth * 4],
                    &atlas->pixels[size_t(y) * oldWidth * 4],
                    size_t(oldWidth) * 4
                );
            }
            atlas->pixels.swap(grown);
            return true;
        }

        void flushAtlas(Atlas* atlas)
        {
            SDL_Rect rect{
                0,
                0,
                atlas->width,
                atlas->height
            };

            SDL_UpdateTexture(
                atlas->texture,
                &rect,
                atlas->pixels.data(),
                atlas->width * 4
            );

            atlas->needFlush = false;
        }

        // Команда отрисовки. UV считаются в present(), после flush(), когда размеры страниц уже известны.
        struct DrawCommand {
            const Resource* resource = nullptr;
            size_t offset = 0; // позиция в frameVertices
            size_t count = 0;
        };

        std::vector<DrawCommand> drawCommands;
        // Вершины всех команд кадра в одном буфере: без отдельной аллокации на каждую команду.
        std::vector<Vertex> frameVertices;

        struct GeometryBatch {
            Atlas* atlas;
            std::vector<SDL_Vertex> geometry;

            GeometryBatch(Atlas* atlas){
                this->atlas = atlas;
            }
        };

        AtlasDock findDock(const Resource* resource) const {
            for(const LoadedResource& loaded : loadedResources){
                if(loaded.resource == resource) return loaded.dock;
            }

            return AtlasDock();
        }

        void appendGeometry(std::vector<SDL_Vertex>& result, const Vertex* vertices, size_t count, const AtlasDock& dock){

            // Геометрия без атласа (dock.atlas == nullptr) получает единичный масштаб.
            const float atlasWidth  = dock.atlas ? float(dock.atlas->width)  : 1.0f;
            const float atlasHeight = dock.atlas ? float(dock.atlas->height) : 1.0f;

            for(const Vertex* vp = vertices; vp != vertices + count; ++vp)
            {
                const Vertex& vertex = *vp;
                SDL_Vertex sdlVertex;

                sdlVertex.position = {
                    vertex.x,
                    vertex.y
                };

                sdlVertex.tex_coord = {
                    (dock.x + vertex.u * dock.width) / atlasWidth,
                    (dock.y + vertex.v * dock.height) / atlasHeight
                };

                sdlVertex.color = {
                    vertex.color.getR(),
                    vertex.color.getG(),
                    vertex.color.getB(),
                    vertex.color.getA()
                };

                result.push_back(sdlVertex);
            }
        };
    };

    // END OF IMPL

    Renderer::~Renderer() {
        // Атласы удаляются до SDL_DestroyRenderer: их текстуры принадлежат рендереру.
        for (Impl::Atlas* atlas : impl->atlases)
        {
            delete atlas;
        }

        SDL_DestroyRenderer(impl->renderer);

        delete impl;
    };

    Renderer::Renderer(EngineWindowNative native) {
        impl = new Impl();
        impl->renderer = SDL_CreateRenderer(static_cast<SDL_Window*>(native), -1, SDL_RENDERER_ACCELERATED);
        // Без этого геометрия без текстуры игнорирует альфа-канал.
        SDL_SetRenderDrawBlendMode(impl->renderer, SDL_BLENDMODE_BLEND);
    };

    void Renderer::load(Resource &resource) {
        for(const Impl::LoadedResource& lres : impl->loadedResources) {
            if(lres.resource == &resource) {
                if(lres.revision != resource.getRevision()) unloading_resources.push_back(&resource);
                break;
            }
        }

        loading_resources.push_back(&resource);
    }

    bool Renderer::isLoaded(const Resource &resource) const {
        for(const Impl::LoadedResource& lres : impl->loadedResources) {
            if(lres.resource == &resource) return lres.revision == resource.getRevision();
        }

        return false;
    }

    void Renderer::unload(Resource &resource) {
        unloading_resources.push_back(&resource);
    };

    void Renderer::flush() {
        impl->unload(unloading_resources);
        unloading_resources.clear();
        impl->load(loading_resources);
        loading_resources.clear();
    };

    void Renderer::draw(Resource &resource, const std::vector<Vertex>& geometry) {
        // load() сам проверяет, не устарела ли загрузка (версия ресурса).
        load(resource);

        Impl::DrawCommand command;
        command.resource = &resource;
        command.offset = impl->frameVertices.size();
        command.count = geometry.size();
        impl->frameVertices.insert(impl->frameVertices.end(), geometry.begin(), geometry.end());
        impl->drawCommands.push_back(command);
    };

    void Renderer::draw(const std::vector<Vertex>& geometry) {
        Impl::DrawCommand command;
        command.offset = impl->frameVertices.size();
        command.count = geometry.size();
        impl->frameVertices.insert(impl->frameVertices.end(), geometry.begin(), geometry.end());
        impl->drawCommands.push_back(command);
    };

    void Renderer::setClipRect(Rect rect) {
        SDL_Rect sdl_rect{rect.x, rect.y, rect.width, rect.height};
        SDL_RenderSetClipRect(impl->renderer, &sdl_rect);
    };

    void Renderer::clear(Color color) {
        SDL_SetRenderDrawColor(
            impl->renderer,
            color.getR(),
            color.getG(),
            color.getB(),
            color.getA()
        );

        SDL_RenderClear(impl->renderer);
    };

    void Renderer::clearClip() {
        const Rect clip = getClippedRect();
        if (clip.isEmpty()) return;

        const float x0 = static_cast<float>(clip.x);
        const float y0 = static_cast<float>(clip.y);
        const float x1 = static_cast<float>(clip.x + clip.width);
        const float y1 = static_cast<float>(clip.y + clip.height);
        const Color black = Color::Black;

        draw(std::vector<Vertex>{
            {x0, y0, 0, 0, black},
            {x0, y1, 0, 0, black},
            {x1, y1, 0, 0, black},
            {x0, y0, 0, 0, black},
            {x1, y0, 0, 0, black},
            {x1, y1, 0, 0, black}
        });
    };

    void Renderer::present() {
        // Порядок важен: загрузка → выгрузка пикселей в GPU → конвертация геометрии → отрисовка.
        flush();

        for (Impl::Atlas* atlas : impl->atlases)
        {
            if (atlas->needFlush) impl->flushAtlas(atlas);
        }

        std::vector<Impl::GeometryBatch> batches;
        for (const Impl::DrawCommand& command : impl->drawCommands)
        {
            Impl::AtlasDock dock;
            if (command.resource) dock = impl->findDock(command.resource);

            if (batches.empty() || batches.back().atlas != dock.atlas) {
                batches.emplace_back(dock.atlas);
            }

            impl->appendGeometry(batches.back().geometry, impl->frameVertices.data() + command.offset, command.count, dock);
        }

        for (const Impl::GeometryBatch& batch : batches)
        {
            SDL_Texture* texture = nullptr;

            if(batch.atlas != nullptr) texture = batch.atlas->texture;

            SDL_RenderGeometry(
                impl->renderer,
                texture,
                batch.geometry.data(),
                static_cast<int>(batch.geometry.size()),
                nullptr,
                0
            );
        }

        SDL_RenderPresent(impl->renderer);
        impl->drawCommands.clear();
        impl->frameVertices.clear();
    };

    Rect Renderer::getClippedRect() {
        SDL_Rect rect{0, 0, 0, 0};
        SDL_RenderGetClipRect(impl->renderer, &rect);
        return {rect.x, rect.y, rect.w, rect.h};
    };

    Size Renderer::getMaxTextureSize() {
        SDL_RendererInfo info;
        SDL_GetRendererInfo(impl->renderer, &info);
        return Size(info.max_texture_width, info.max_texture_height);
    }

}}
