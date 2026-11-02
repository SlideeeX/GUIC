#include "Guic/resources/Image.hpp"
#include "Guic/external/stb/stb_image.h"
#include <cstring>

using namespace guic::engine;

namespace guic {

namespace {

constexpr int MAX_SIDE = 65535; // Bitmap::width/height are Uint16

}

Image::Image(const std::string& path) : path(path) {};

Bitmap* Image::createBitmap()
{
    int width = 0;
    int height = 0;
    int channels = 0;

    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 4);
    if (data == nullptr)
    {
        return nullptr;
    }

    if (width <= 0 || height <= 0 || width > MAX_SIDE || height > MAX_SIDE)
    {
        stbi_image_free(data);
        return nullptr;
    }

    Bitmap* bitmap = new Bitmap();
    bitmap->width = static_cast<Uint16>(width);
    bitmap->height = static_cast<Uint16>(height);
    bitmap->pixels.assign(
        data,
        data + static_cast<size_t>(width) * static_cast<size_t>(height) * 4
    );
    stbi_image_free(data);

    img_size.width = bitmap->width;
    img_size.height = bitmap->height;

    is_metadata_loaded = true;
    return bitmap;
}

Size Image::getSize() const {
    return img_size;
}

bool Image::copyMetadataFrom(engine::Resource& src)
{
    const Image* other = dynamic_cast<const Image*>(&src);
    if (other == nullptr) return false;

    path = other->path;
    img_size = other->img_size;
    return true;
}

}
