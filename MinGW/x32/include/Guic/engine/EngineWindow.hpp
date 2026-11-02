#pragma once
#include <string>
#include <Guic/config/Functions.hpp>
#include <Guic/config/Export.hpp>
#include <Guic/engine/Resource.hpp>
#include <Guic/engine/Renderer.hpp>
#include <Guic/common/Size.hpp>

namespace guic { namespace engine {

class GUIC_API EngineWindow
{
public:
    EngineWindow(const EngineWindow&) = delete;
    EngineWindow& operator=(const EngineWindow&) = delete;

    EngineWindow();
    EngineWindow(std::string name, Size size);
    ~EngineWindow();

    void open();
    void close();

    void show();
    void hide();
    void focus();

    void setSize(Size size);
    void setName(std::string name);

    void display();

    void setClipRect(Rect rect);

    void load(Resource& resource);
    void unload(Resource& resource);

    bool isOpen() const;
    bool isShow() const;
    bool isFocused() const;

    Uint32 getId() const;

    Renderer* getRenderer() const;

    Size getSize() const;
    std::string getName() const;
protected:
    void createWindow();
    bool opened = false;
    bool shown = false;
    std::string name = "";
    Size size;
    Renderer* renderer = nullptr;
private:
    struct Impl;
    Impl* impl;
    EngineWindowNative native() const;
};

}}
