#pragma once
#include <Guic/config/Export.hpp>
#include <Guic/engine/Bitmap.hpp>
#include <Guic/config/Types.hpp>

namespace guic { namespace engine {

class GUIC_API Resource
{
public:
    Resource() = default;
    Resource(const Resource&) = delete;
    Resource& operator=(const Resource&) = delete;
    virtual ~Resource();

    const Bitmap* load();
    void unload();

    bool isMetadataLoaded() const;
    Uint32 getRevision() const;
    Uint32 getCacheRevision() const;

    bool pull(Resource*& src);

protected:
    virtual Bitmap* createBitmap() = 0;
    void nextRevision();

    bool is_metadata_loaded = false;

    virtual bool copyMetadataFrom(Resource& src);

private:
    Bitmap* cache = nullptr;
    Uint32 cacheRevision = 0;
    int cache_refs = 0;

    Uint32 revision = 0;
};

}}
