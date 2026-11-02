#include "Guic/engine/Resource.hpp"

namespace guic { namespace engine {

bool Resource::pull(Resource*& src) {
    if (src == nullptr || src == this) return false;
    if (cache_refs > 0) return false;
    if (src->cache == nullptr || src->cache_refs != 1) return false;

    if (!copyMetadataFrom(*src)) return false;

    delete cache;
    cache = src->cache;
    src->cache = nullptr;
    src->cache_refs = 0;

    is_metadata_loaded = src->is_metadata_loaded;
    nextRevision();
    cacheRevision = revision;

    delete src;
    src = nullptr;
    return true;
}

bool Resource::copyMetadataFrom(Resource&) {
    return true;
}

Resource::~Resource() {
    delete cache;
}

const Bitmap* Resource::load() {
    if (cache != nullptr && cacheRevision != revision && cache_refs == 0) {
        delete cache;
        cache = nullptr;
    }

    if (cache == nullptr) {
        Bitmap* bitmap = createBitmap();
        if (bitmap == nullptr) {
            return nullptr;
        }
        cache = bitmap;
        cacheRevision = revision;
    }

    cache_refs++;
    return cache;
}

void Resource::unload() {
    if (cache_refs > 0 && --cache_refs == 0) {
        delete cache;
        cache = nullptr;
    }
}

bool Resource::isMetadataLoaded() const {
    return is_metadata_loaded;
}

Uint32 Resource::getRevision() const {
    return revision;
}

Uint32 Resource::getCacheRevision() const {
    return cacheRevision;
}

void Resource::nextRevision() {
    revision++;
}

}}
