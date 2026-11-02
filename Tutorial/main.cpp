#include <Guic/Guic.hpp>

using namespace guic;

int likes = 0;

class ResetButton : public Composite {
public:
    ResetButton(Rect rect, Font& font) : Composite(rect) {
        resetShape.setRect(Rect(0, 0, 140, 50));
        resetShape.setColor(Color("#f4e1c1"));
        resetShape.setRadius(25);

        resetCaption.setRect(Rect(35, 16, 100, 30));
        resetCaption.setString("Сбросить");
        resetCaption.setFont(font);
        resetCaption.setColor(Color("#1b4242"));

        reset.setRect(Rect(0, 0, 140, 50));
        reset.setRadius(25);
        reset.onLMB([](){ likes = 0; });

        add(resetShape);
        add(resetCaption);
        add(reset);
    }
private:
    Sprite resetShape;
    Text resetCaption;
    Trigger reset;
};

class MoodCard : public Composite {
public:
    MoodCard(Rect rect, Image& picture, Font& font, const std::string& mood) : Composite(rect) {
        background.setRect(Rect(0, 0, rect.width, rect.height));
        background.setColor(Color("#f4e1c1"));
        background.setRadius(36);

        photo.setRect(Rect(20, 20, 140, 140));
        photo.setImage(picture);
        photo.setRadius(70);

        caption.setRect(Rect(20, 170, 140, 50));
        caption.setString(mood);
        caption.setFont(font);
        caption.setColor(Color("#1b4242"));

        heart.setRect(Rect(20, 20, 140, 140));
        heart.setRadius(70);
        heart.onLMB([this] {
            likes++;
            if(container == nullptr) return;
            container->remove(*this);
            container->add(*this);
        });

        add(background);
        add(photo);
        add(caption);
        add(heart);
    }

    void setContainer(Container &container) {
        this->container = &container;
    }

    Container* container = nullptr;

private:
    Sprite background;
    Sprite photo;
    Text caption;
    Trigger heart;
};

int main() {
    Window window("Как настроение?", Size(640, 480));
    window.open();

    Sprite background(Rect(0, 0, 640, 480), Color("#1b4242"));
    window.add(background);

    Font font("UbuntuMono-Bold.ttf", 16);
    font.addPack(Font::Pack::RU);
    font.addPack(Font::Pack::Sign);

    Text title(Rect(25, 25, 580, 40), "Какой ты котик сегодня?", font);
    title.setColor(Color::White);
    window.add(title);

    Image picture("kit.png");

    MoodCard happy(Rect(0, 0, 180, 230), picture, font, "Сегодня бодрый,\nкак утренний чай");
    MoodCard tired(Rect(150, 0, 180, 230), picture, font, "Немного устал,\nно держусь");
    MoodCard coffee(Rect(300, 0, 180, 230), picture, font, "Нужен кофе\nи немного тишины");

    Container cards(Rect(30, 110, 580, 230));

    cards.add(happy);
    happy.setContainer(cards);

    cards.add(tired);
    tired.setContainer(cards);

    cards.add(coffee);
    coffee.setContainer(cards);

    window.add(cards);

    ResetButton resetButton(Rect(460, 400, 140, 50), font);
    window.add(resetButton);

    Text total(Rect(25, 40, 280, 40), "Лайков сегодня: 0", font);
    total.setColor(Color::White);
    window.add(total);

    int shown = 0;
    while (window.isOpen()) {
        window.tune();

        if (likes != shown) {
            shown = likes;
            total.setString("Лайков сегодня: " + std::to_string(likes));
        }

        window.display();

        guic_delay(10);
    }

    return 0;
}
