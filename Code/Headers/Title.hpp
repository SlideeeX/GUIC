#ifndef TITLE_HPP
#define TITLE_HPP

#include "Interface.hpp"

#ifndef GUIC_BASE_CHAR_SIZE
#define GUIC_BASE_CHAR_SIZE 15
#endif

namespace guic

{

using namespace sf;

class DLLIMPORT Title : public Interface
{
private:
	float* charwidth;
	float* charheight;
	int size;
	
	IntRect rect;
	Text title;
	String strtitle;
public:

	Title();
	
	Title(IntRect titleRect, String titleString);
	
	Title(IntRect titleRect, String titleString, int charSize);
	
	String getString();
	
	Vector2f getPosition();
	
	IntRect getTitleRect();
	
	IntRect setTitleRect(IntRect titleRect);
	
	int getLenght();
	
	float getTitleWidth();
	
	float getTitleHeight();
	
	float getCharWidth();
	
	float getCharHeight();
	
	int getCharacterSize();
	
	void setBackground(Color color);
	
	void setString(String string);
	
	void setCharacterSize(unsigned int charSize);
	
	void setFont(Font Font);
	
	void setColor(Color Color);
	
	void setRect(IntRect titleRect) override;
	
	void setPosition(float x, float y);
	
	void setPosition(Vector2f pos);
	
	void draw(RenderWindow* window) override;
};

};

#endif
