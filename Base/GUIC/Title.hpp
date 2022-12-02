#ifndef TITLE_HPP
#define TITLE_HPP

#include "Interface.hpp"
#include "Variables.hpp"

#ifndef GUIC_BASE_CHAR_SIZE
#define GUIC_BASE_CHAR_SIZE 15
#endif

namespace guic

{

using namespace sf;

class Title : public Interface
{
private:
	float charwidth;
	float charheight;
	int size;
	
	IntRect rect;
	Text title;
	String strtitle;
public:

	Title();
	
	Title(IntRect Rect, const char* Title);
	
	Title(IntRect Rect, const char* Title, int Size);
	
	String getString();
	
	Vector2f getPosition();
	
	IntRect getTitleRect();
	
	IntRect setTitleRect(IntRect Rect);
	
	int getLenght();
	
	float getTitleWidth();
	
	float getTitleHeight();
	
	float getCharWidth();
	
	float getCharHeight();
	
	int getCharacterSize();
	
	void setBackground(Color color);
	
	void setString(String string);
	
	void setCharacterSize(unsigned int Size);
	
	void setFont(Font Font);
	
	void setColor(Color Color);
	
	void setRect(IntRect Rect) override;
	
	void setPosition(float x, float y);
	
	void setPosition(Vector2f pos);
	
	void draw(RenderWindow* window) override;
};

};

#endif
