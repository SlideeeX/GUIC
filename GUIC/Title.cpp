#include "Title.hpp"

namespace guic

{

Title::Title(){
	title.setFont(BaseFont);
	title.setCharacterSize(GUIC_BASE_CHAR_SIZE);
	title.setFillColor(BaseTextColor);
	size = GUIC_BASE_CHAR_SIZE-GUIC_BASE_CHAR_SIZE/3;
	charheight = GUIC_BASE_CHAR_SIZE-GUIC_BASE_CHAR_SIZE/3;
	charwidth = GUIC_BASE_CHAR_SIZE/2+GUIC_BASE_CHAR_SIZE%2;
		
	rect.width = charwidth;
	rect.height = charheight;
	rect.top = 0;
	rect.left = 0;
	
	setLayer(GUIC_BASE_TITLE_LAYER);
};

Title::Title(IntRect Rect, const char* Title) :Interface(Rect){
	rect = Rect;
	size = GUIC_BASE_CHAR_SIZE;
	
	charheight = GUIC_BASE_CHAR_SIZE-GUIC_BASE_CHAR_SIZE/3;
	charwidth = GUIC_BASE_CHAR_SIZE/2+GUIC_BASE_CHAR_SIZE%2;
	
	title.setFont(BaseFont);
	title.setCharacterSize(GUIC_BASE_CHAR_SIZE);
	
	setLayer(GUIC_BASE_TITLE_LAYER);
	
	strtitle = Title;
	
	title.setString(Title);
	title.setPosition(Rect.left, Rect.top);
	title.setFillColor(BaseTextColor);
	
	createMaskFromColor(Color::White);
	
	rect.width = getTitleWidth();
	rect.height = getTitleHeight();
	
	setLayer(GUIC_BASE_TITLE_LAYER);
};

Title::Title(IntRect Rect, const char* Title, int Size) :Interface(Rect){
	strtitle = Title;
	rect = Rect;
	
	title.setString(Title);
	title.setFont(BaseFont);
	title.setPosition(Rect.left, Rect.top);
	title.setCharacterSize(Size);
	title.setFillColor(BaseTextColor);
	
	createMaskFromColor(Color::White);
	
	charwidth = Size/2+Size%2;
	charheight = Size-Size/3;
	
	rect.width = getTitleWidth();
	rect.height = getTitleHeight();
	
	setLayer(GUIC_BASE_TITLE_LAYER);
};

String Title::getString(){ return strtitle; }

Vector2f Title::getPosition(){ return title.getPosition(); }

IntRect Title::getTitleRect(){ return rect; }

IntRect Title::setTitleRect(IntRect Rect){	rect = Rect; }

int Title::getLenght(){ return strtitle.getSize(); }

float Title::getTitleWidth(){ return charwidth*strtitle.getSize(); }

float Title::getTitleHeight(){ return charheight*!strtitle.isEmpty(); }
		
float Title::getCharWidth(){ return charwidth; }

float Title::getCharHeight(){ return charheight; }

int Title::getCharacterSize(){ title.getCharacterSize(); }

void Title::setBackground(Color color){
	IntRect rect = getTitleRect();
	
	Image image;
	image.create(rect.width, rect.height, color);
	setRectSprite(&image, rect);
	
	createMaskFromColor(Color::White, rect);
}

void Title::setString(String string){
	title.setString(string);
	strtitle = string;
	rect.width = getTitleWidth();
}

void Title::setCharacterSize(unsigned int Size){
	title.setCharacterSize(Size);
	charwidth = Size/2+Size%2;
	charheight = Size-Size/3;;
	
	rect.height = getTitleHeight(); 
	rect.width = getTitleWidth();
}

void Title::setFont(Font Font){
	title.setFont(Font);
}

void Title::setColor(Color Color){
	title.setFillColor(Color);
}

void Title::setPosition(float x, float y){
	title.setPosition(x, y);
	rect.left = x;
	rect.top = y;
}

void Title::setRect(IntRect Rect) {
	Addable::setRect(Rect);
	title.setPosition(Rect.left, Rect.top);
}

void Title::setPosition(Vector2f pos){
	title.setPosition(pos);
	rect.left = pos.x;
	rect.top = pos.y;
}

void Title::draw(RenderWindow* window) {
	window->draw(getSprite());
	window->draw(title);
}

}
