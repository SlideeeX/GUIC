#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Trigger.hpp"
#include "Title.hpp"

#ifndef GUIC_BASE_BUTTON_FRAMEFAT
#define GUIC_BASE_BUTTON_FRAMEFAT 4
#endif

#ifndef GUIC_BASE_BUTTON_LAYER
#define GUIC_BASE_BUTTON_LAYER 4
#endif

namespace guic

{

using namespace sf;

class Button :public Trigger

{

private:
	
	Title title;
	int F;
	
	void create(IntRect Rect);
	
public:
	
	Button();
	
	Button(IntRect Rect, const char* Title);
	
	Button(IntRect Rect, const char* Title, String File);
	
	Button(IntRect Rect, const char* Title, Image* Image);
	
	void setCharacterSize(int Size);
	
	void setFrameFat(int Fat);
	
	void setRect(IntRect Rect) override;
	
	void draw(RenderWindow* window) override;
	
};

}

#endif
