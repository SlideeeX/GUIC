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

class DLLIMPORT Button :public Trigger

{

private:
	
	Title title;
	int fat;
	
	void create(IntRect rect);
	
public:
	
	Button();
	
	Button(IntRect rect, String title_s);
	
	Button(IntRect rect, String title_s, String file);
	
	Button(IntRect rect, String title_s, Image* image);
	
	void setCharacterSize(int charSize);
	
	void setFrameFat(int frameFat);
	
	void setRect(IntRect rect) override;
	
	void setTitle(String title_s);
	
	void draw(RenderWindow* window) override;
	
};

}

#endif
