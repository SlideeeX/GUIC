#include <GUIC/Button.hpp>

namespace guic

{

Button::Button(IntRect rect, String title_s):Trigger(rect){
	title.setString(title_s);
	fat=GUIC_BASE_BUTTON_FRAMEFAT;
	create(rect);
	setLayer(GUIC_BASE_BUTTON_LAYER);
}

Button::Button(IntRect rect, String title_s, String file):Trigger(rect, file){
	title.setString(title_s);
	fat=GUIC_BASE_BUTTON_FRAMEFAT;
	setLayer(GUIC_BASE_BUTTON_LAYER);
}

Button::Button(IntRect rect, String title_s, Image* image) :Trigger(rect, image){
	title.setString(title_s);
	fat=GUIC_BASE_BUTTON_FRAMEFAT;
	setLayer(GUIC_BASE_BUTTON_LAYER);
}

void Button::create(IntRect rect){
	Image* image = getImagePointer();
	
	if(image->getSize().x<1 || image->getSize().y<1){
		image->create(rect.width, rect.height, Color::White);
	}
	
	int width = image->getSize().x;
	int height = image->getSize().y;
	
	if(width>rect.width) width = rect.width;
	if(height>rect.height) height = rect.height;
	
	for(int i=0; i<fat; i++){ // Прикольно, всё работает, закрепи
		for(int j=0; j!=width; j++){
			image->setPixel(j, i, Color::Black);
			image->setPixel(j, i+height-fat, Color::Black);
		}
		for(int j=0; j!=height; j++){
			image->setPixel(i, j, Color::Black);
			image->setPixel(i+width-fat, j, Color::Black);
		}
	}
		
	image->createMaskFromColor(Color::White);
	setRectImage(image, rect);
	
	changed = true;
}

Button::Button(){ setLayer(GUIC_BASE_BUTTON_LAYER); fat=GUIC_BASE_BUTTON_FRAMEFAT; };

void Button::setCharacterSize(int charSize) {
	title.setCharacterSize(charSize);
	changed = true;
}

void Button::setFrameFat(int frameFat) {
	fat = frameFat;
	changed = true;
}

void Button::setRect(IntRect rect) {
	Addable::setRect(rect);
	title.setPosition(rect.left+(rect.width-title.getTitleWidth())/2, rect.top+(rect.height-title.getTitleHeight()*2)/2);
	changed = true;
}

void Button::setTitle(String title_s) {
	title.setString(title_s);
	create(getRect());
}
		
void Button::draw(RenderWindow* window) {
	window->draw(getSprite());
	title.draw(window);
}

}
