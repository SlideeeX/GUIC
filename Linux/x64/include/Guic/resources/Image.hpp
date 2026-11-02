#pragma once
#include <Guic/engine/Resource.hpp>
#include <Guic/common/Size.hpp>
#include <string>

namespace guic {

class GUIC_API Image : public engine::Resource
{
public:
    Image(const std::string& path);

    engine::Bitmap* createBitmap() override;

    Size getSize() const;

protected:
    bool copyMetadataFrom(Resource& src) override;

private:
    std::string path;
    Size img_size;
};

}
