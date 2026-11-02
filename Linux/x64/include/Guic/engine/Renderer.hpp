#pragma once
#include <vector>
#include <Guic/config/Export.hpp>
#include <Guic/engine/EngineWindowNative.hpp>
#include <Guic/engine/Resource.hpp>
#include <Guic/engine/Vertex.hpp>
#include <Guic/common/Rect.hpp>
#include <Guic/common/Size.hpp>

namespace guic { namespace engine {

class GUIC_API Renderer
{
public:
    Renderer(EngineWindowNative native);
    ~Renderer();

    void load(Resource &resource);
    void unload(Resource &resource);
    bool isLoaded(const Resource &resource) const;
    void flush();

    void draw(const std::vector<Vertex>& geometry);
    void draw(Resource &resource, const std::vector<Vertex>& geometry);

    void clear(Color color);
    void clearClip();
    void present();

    void setClipRect(Rect rect);
    Rect getClippedRect();

    Size getMaxTextureSize();

protected:
private:
    struct Impl;
    Impl* impl;

    std::vector<Resource*> loading_resources;
    std::vector<Resource*> unloading_resources;
};

}}
