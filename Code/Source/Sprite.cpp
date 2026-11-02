#include "Guic/Sprite.hpp"

#include <algorithm>
#include <cmath>

using namespace guic::engine;

namespace {
    struct Point {
        float x = 0;
        float y = 0;
        float a = 1; // альфа вершины, 0..1
    };

    using Polygon = std::vector<Point>;

    Polygon clipHalfPlane(const Polygon& input, bool useX, float bound, bool keepGreater) {
        auto coord = [useX](const Point& p) { return useX ? p.x : p.y; };
        auto inside = [&](const Point& p) {
            return keepGreater ? coord(p) >= bound : coord(p) <= bound;
        };

        Polygon output;
        for (size_t i = 0; i < input.size(); i++) {
            const Point& a = input[i];
            const Point& b = input[(i + 1) % input.size()];
            bool aInside = inside(a);
            bool bInside = inside(b);

            if (aInside) output.push_back(a);
            if (aInside != bInside) {
                float t = (bound - coord(a)) / (coord(b) - coord(a));
                output.push_back({a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.a + (b.a - a.a) * t});
            }
        }
        return output;
    }
}

namespace guic {
    Sprite::Sprite() {
        setMode(Mode::Color);
        setColor(Color::White);
        image = nullptr;
    }

	Sprite::Sprite(Rect rect) {
        setMode(Mode::Color);
        setColor(Color::White);
        image = nullptr;
        setRect(rect);
    }

	Sprite::Sprite(Rect rect, Image &image) {
        setMode(Mode::Image);
        setColor(Color::White);
        setImage(image);
        setRect(rect);
    }

	Sprite::Sprite(Rect rect, Color color) {
        setMode(Mode::Color);
        setColor(color);
        image = nullptr;
        setRect(rect);
    }

	void Sprite::setImage(Image &_image) {
        if(mode != Mode::Mashup) mode = Mode::Image;
        image = &_image;
        calculateImageRect = true;
        update();
    }

    const Image* Sprite::getImage() const {
        return image;
    }

    void Sprite::setImageRect(Rect rect) {
        imageRect = rect;
        calculateImageRect = false;
        update();
    }

    void Sprite::setRadius(int _radius) {
        radius = _radius < 0 ? 0 : _radius;
        update();
    }

    int Sprite::getRadius() const {
        return radius;
    }

    Element* Sprite::hit(int x, int y) {
        if (radius <= 0) return Element::hit(x, y);
        if (!isShow() || !isHit() || !getGlobalVisibleRect().contains(x, y)) return nullptr;
        if (!getGlobalRect().contains(x, y, radius)) return nullptr;
        return this;
    }

    void Sprite::setColor(Color _color) {
        if(mode != Mode::Mashup) mode = Mode::Color;
        color = _color;
        update();
    }

    Color Sprite::getColor() const {
        return color;
    }

    void Sprite::setMode(Mode _mode) {
        mode = _mode;
        update();
    }

    Sprite::Mode Sprite::getMode() const {
        return mode;
    }

    void Sprite::preload(Renderer &renderer) {
        if(!isShow() || !isChanged()) return;

        if(mode == Mode::Color) return;
        if(image == nullptr) return;
        if(!getGlobalVisibleRect().intersects(renderer.getClippedRect())) return;

        if(!image->isMetadataLoaded() || !renderer.isLoaded(*image)) renderer.load(*image);
    }

    void Sprite::draw(Renderer &renderer) {
        if(!isShow()) {
            unchange();
            return;
        }

        if((mode == Mode::Image || mode == Mode::Mashup) && image == nullptr) return;
        if(!getGlobalVisibleRect().intersects(renderer.getClippedRect())) return;

        if(isChanged()){
            if(mode == Mode::Image || mode == Mode::Mashup){
                if(image->getSize().width == 0 && image->getSize().height == 0){
                    setMode(Mode::Color);
                    setColor(Color(0xFF00FFFF));
                }
            }
            if(radius > 0) {
                buildRoundedGeometry();
            } else {
                buildGeometry();
            }
        }

        if(mode == Mode::Image || mode == Mode::Mashup){
            renderer.draw(*image, geometry);
        } else if (mode == Mode::Color){
            renderer.draw(geometry);
        }

        unchange();
    }

    void Sprite::buildGeometry() {
        geometry.clear();

        Rect visibleRect = getGlobalVisibleRect();
        if (visibleRect.width == 0 || visibleRect.height == 0) return;

        Rect globalRect = getGlobalRect();

        float iu0 = 0;
        float iv0 = 0;
        float iu1 = 0;
        float iv1 = 0;

        float u0 = 0;
        float v0 = 0;
        float u1 = 0;
        float v1 = 0;


        float left = float(visibleRect.x - globalRect.x) / globalRect.width;
        float top = float(visibleRect.y - globalRect.y) / globalRect.height;

        float right = float(visibleRect.x + visibleRect.width - globalRect.x)
                    / globalRect.width;
        float bottom = float(visibleRect.y + visibleRect.height - globalRect.y)
                     / globalRect.height;

        Size imageSize;
        if(mode == Mode::Image || mode == Mode::Mashup) {
            imageSize = image->getSize();

            if (calculateImageRect || imageRect.width == 0 || imageRect.height == 0) {
                imageRect = Rect(0, 0, imageSize.width, imageSize.height);
            }


            iu0 = float(imageRect.x) / imageSize.width;
            iv0 = float(imageRect.y) / imageSize.height;
            iu1 = float(imageRect.x + imageRect.width) / imageSize.width;
            iv1 = float(imageRect.y + imageRect.height) / imageSize.height;


            u0 = iu0 + (iu1 - iu0) * left;
            v0 = iv0 + (iv1 - iv0) * top;
            u1 = iu0 + (iu1 - iu0) * right;
            v1 = iv0 + (iv1 - iv0) * bottom;
        }

        float x0 = float(visibleRect.x);
        float y0 = float(visibleRect.y);
        float x1 = float(visibleRect.x + visibleRect.width);
        float y1 = float(visibleRect.y + visibleRect.height);

        Color colored = (mode == Mode::Image) ? Color::White : color;

        geometry = {
            {x0, y0, u0, v0, colored},
            {x0, y1, u0, v1, colored},
            {x1, y1, u1, v1, colored},

            {x0, y0, u0, v0, colored},
            {x1, y0, u1, v0, colored},
            {x1, y1, u1, v1, colored}
        };
    }

    void Sprite::buildRoundedGeometry() {
        geometry.clear();

        Rect visibleRect = getGlobalVisibleRect();
        if (visibleRect.width == 0 || visibleRect.height == 0) return;

        Rect globalRect = getGlobalRect();


        const float gx = float(globalRect.x);
        const float gy = float(globalRect.y);
        const float gw = float(globalRect.width);
        const float gh = float(globalRect.height);

        const float r = float(std::min({radius, globalRect.width / 2, globalRect.height / 2}));
        const float halfPi = 3.14159265358979f / 2.0f;

        // Число граней на угол считаем по радиусу: отклонение хорд не больше arcTolerance.
        const float tolerance = arcTolerance;
        const int minSegments = cornerSegments;
        const float halfAngle = std::acos(std::max(0.0f, 1.0f - tolerance / std::max(r, 1.0f)));
        const int segments = std::max(minSegments, int(std::ceil(halfPi / (2.0f * halfAngle))));

        float iu0 = 0, iv0 = 0, iu1 = 0, iv1 = 0;
        if(mode == Mode::Image || mode == Mode::Mashup) {
            Size imageSize = image->getSize();

            if (calculateImageRect || imageRect.width == 0 || imageRect.height == 0) {
                imageRect = Rect(0, 0, imageSize.width, imageSize.height);
            }

            iu0 = float(imageRect.x) / imageSize.width;
            iv0 = float(imageRect.y) / imageSize.height;
            iu1 = float(imageRect.x + imageRect.width) / imageSize.width;
            iv1 = float(imageRect.y + imageRect.height) / imageSize.height;
        }

        auto makeVertex = [&](const Point& p) {
            float u = 0;
            float v = 0;
            if(mode == Mode::Image || mode == Mode::Mashup) {
                u = iu0 + (iu1 - iu0) * (p.x - gx) / gw;
                v = iv0 + (iv1 - iv0) * (p.y - gy) / gh;
                // Обрезка по видимому прямоугольнику даёт точки с погрешностью float (например, y = -6e-8),
                // из-за которой UV выходит за границы. SDL_RenderGeometry отвергает такие вершины целиком.
                u = std::min(std::max(u, std::min(iu0, iu1)), std::max(iu0, iu1));
                v = std::min(std::max(v, std::min(iv0, iv1)), std::max(iv0, iv1));
            }
            Color vertexColor(color.getR(), color.getG(), color.getB(), Uint8(color.getA() * p.a + 0.5f));
            if(mode == Mode::Image) vertexColor = Color(0xFF, 0xFF, 0xFF, Uint8(0xFF * p.a + 0.5f));

            return engine::Vertex{p.x, p.y, u, v, vertexColor};
        };


        // Ширина кольца сглаживания. Все заливки строятся внутри внутреннего контура (отступ на feather),
        // иначе прямые края остаются жёсткими, а на дугах появляется перепад альфы в точках касания.
        const float feather = std::min(1.0f, r);

        std::vector<Polygon> triangles;
        auto addRect = [&](float x0, float y0, float x1, float y1) {
            triangles.push_back({{x0, y0}, {x0, y1}, {x1, y1}});
            triangles.push_back({{x0, y0}, {x1, y1}, {x1, y0}});
        };

        addRect(gx + r, gy + feather, gx + gw - r, gy + r);
        addRect(gx + feather, gy + r, gx + gw - feather, gy + gh - r);
        addRect(gx + r, gy + gh - r, gx + gw - r, gy + gh - feather);

        struct Corner {
            float cx;
            float cy;
            float startAngle;
        };

        const Corner corners[4] = {
            {gx + r,      gy + r,      2 * halfPi},
            {gx + gw - r, gy + r,      3 * halfPi},
            {gx + gw - r, gy + gh - r, 0},
            {gx + r,      gy + gh - r, halfPi},
        };

        // Контур скругления по часовой: точка на дуге и внешняя нормаль.
        // Прямые участки между углами выходят из концев дуг с одинаковой нормалью.
        struct Outline {
            Point p;
            float nx;
            float ny;
        };
        std::vector<Outline> outline;

        for (const Corner& corner : corners) {
            for (int i = 0; i <= segments; i++) {
                float angle = corner.startAngle + halfPi * i / segments;
                float nx = std::cos(angle);
                float ny = std::sin(angle);
                outline.push_back({{corner.cx + r * nx, corner.cy + r * ny}, nx, ny});
            }
        }

        // Кольцо 1 px внутрь от контура: внутренняя кромка с альфой 1, внешняя (контур) с альфой 0.
        // Кольцо не выходит за границы спрайта, иначе обрезка по видимому прямоугольнику срезает край.
        // Так сглаживается без антиалиасинга в SDL.
        std::vector<Point> inner;
        inner.reserve(outline.size());
        for (const Outline& o : outline) {
            inner.push_back({o.p.x - o.nx * feather, o.p.y - o.ny * feather, 1.0f});
        }

        // Внутренняя часть: вееры от центра угла до внутренней кромки кольца.
        for (size_t c = 0; c < 4; c++) {
            const Corner& corner = corners[c];
            for (int i = 0; i < segments; i++) {
                const size_t idx = c * (segments + 1) + i;
                triangles.push_back({{corner.cx, corner.cy}, inner[idx], inner[idx + 1]});
            }
        }

        if (r > 0) {
            const size_t count = outline.size();
            for (size_t k = 0; k < count; k++) {
                const Point& in0 = inner[k];
                const Point& in1 = inner[(k + 1) % count];
                Point out0{outline[k].p.x, outline[k].p.y, 0.0f};
                Point out1{outline[(k + 1) % count].p.x, outline[(k + 1) % count].p.y, 0.0f};
                triangles.push_back({in0, out0, out1});
                triangles.push_back({in0, out1, in1});
            }
        }


        const float vx0 = float(visibleRect.x);
        const float vy0 = float(visibleRect.y);
        const float vx1 = float(visibleRect.x + visibleRect.width);
        const float vy1 = float(visibleRect.y + visibleRect.height);

        for (const Polygon& triangle : triangles) {
            Polygon poly = clipHalfPlane(triangle, true, vx0, true);
            poly = clipHalfPlane(poly, true, vx1, false);
            poly = clipHalfPlane(poly, false, vy0, true);
            poly = clipHalfPlane(poly, false, vy1, false);

            for (size_t k = 1; k + 1 < poly.size(); k++) {
                geometry.push_back(makeVertex(poly[0]));
                geometry.push_back(makeVertex(poly[k]));
                geometry.push_back(makeVertex(poly[k + 1]));
            }
        }
    }

}
