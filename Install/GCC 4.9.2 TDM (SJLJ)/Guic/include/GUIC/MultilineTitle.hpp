#ifndef MULTILINETITLE_HPP
#define MULTILINETITLE_HPP

#include "Interface.hpp"

#ifndef GUIC_MAX_MLTITLE_LENGHT
#define GUIC_MAX_MLTITLE_LENGHT 300
#endif

#ifndef GUIC_MAX_MLTITLE_ROWS
#define GUIC_MAX_MLTITLE_ROWS 100
#endif

#ifndef GUIC_BASE_CHAR_SIZE
#define GUIC_BASE_CHAR_SIZE 15
#endif

#ifndef GUIC_BASE_MLTITLE_LAYER
#define GUIC_BASE_MLTITLE_LAYER 6
#endif

namespace guic

{

using namespace sf;

class DLLIMPORT MultilineTitle :public Interface

{

private:

String linetitle;
String words[GUIC_MAX_MLTITLE_LENGHT];
Text lines[GUIC_MAX_MLTITLE_ROWS];
IntRect rect;
Font font;

int size=0;
int lenght = 0;
float charwidth;
float charheight;

void create();
	
public:
	
	MultilineTitle();
	
	MultilineTitle(IntRect mlRect, const char* mlTitle, String file);
	
	MultilineTitle(IntRect mlRect, const char* mlTitle, Image* mlImage);
	
	MultilineTitle(IntRect mlRect, const char* mlTitle);
	
	int getCharacterSize();
	
	float getCharWidth();
	
	void setString(String string);
	
	void setFont(Font mlFont);
	
	void setColor(Color mlColor);
	
	void setPosition(float x, float y);
	
	void setRect(IntRect mlRect) override;
	
	void setCharacterSize(int charSize);
	
	void draw(RenderWindow* window) override;
};

}

#endif
