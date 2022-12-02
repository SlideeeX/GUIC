#include "Button.hpp"

namespace guic

{
	
void Button::create(IntRect Rect){
	Image* image = getImagePointer();
	
	if(image->getSize().x<1 || image->getSize().y<1){
		image->create(Rect.width, Rect.height, Color::White);
	}
	
	int width = image->getSize().x;
	int height = image->getSize().y;
	
	if(width>Rect.width) width = Rect.width;
	if(height>Rect.height) height = Rect.height;
	
	for(int i=0; i<F; i++){ // Прикольно, всё работает, закрепи
		for(int j=0; j!=width; j++){
			image->setPixel(j, i, Color::Black);
			image->setPixel(j, i+height-F, Color::Black);
		}
		for(int j=0; j!=height; j++){
			image->setPixel(i, j, Color::Black);
			image->setPixel(i+width-F, j, Color::Black);
		}
	}
		
	image->createMaskFromColor(Color::White);
	setRectSprite(image, Rect);
}

Button::Button(){ setLayer(GUIC_BASE_BUTTON_LAYER); F=GUIC_BASE_BUTTON_FRAMEFAT; };

Button::Button(IntRect Rect, const char* Title):Trigger(Rect){
	title.setString(Title);
	F=GUIC_BASE_BUTTON_FRAMEFAT;
	create(Rect);
	setLayer(GUIC_BASE_BUTTON_LAYER);
}

Button::Button(IntRect Rect, const char* Title, String File):Trigger(Rect, File){
	title.setString(Title);
	F=GUIC_BASE_BUTTON_FRAMEFAT;
	setLayer(GUIC_BASE_BUTTON_LAYER);
}

Button::Button(IntRect Rect, const char* Title, Image* Image) :Trigger(Rect, Image){
	title.setString(Title);
	F=GUIC_BASE_BUTTON_FRAMEFAT;
	setLayer(GUIC_BASE_BUTTON_LAYER);
}

void Button::setCharacterSize(int Size) {
	title.setCharacterSize(Size);
}

void Button::setFrameFat(int Fat) {
	F = Fat;
}

void Button::setRect(IntRect Rect) {
	Addable::setRect(Rect);
	title.setPosition(Rect.left+(Rect.width-title.getTitleWidth())/2, Rect.top+(Rect.height-title.getTitleHeight()*2)/2);
}
		
void Button::draw(RenderWindow* window) {
	window->draw(getSprite());
	title.draw(window);
}

}
