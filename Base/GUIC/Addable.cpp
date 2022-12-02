#include "Addable.hpp"

#ifndef BASE_HIGH_LAYER
#define BASE_HIGH_LAYER 0
#endif

namespace guic

{
	
Addable::Addable(){
	_rect = IntRect(0, 0, 0, 0);
	added = false;
	forshow = false;
	layer = BASE_HIGH_LAYER;
}
	
Addable::Addable(IntRect Rect){
	_rect = Rect;
	added = false;
	forshow = false;
	layer = BASE_HIGH_LAYER;
};
	
Addable::Addable(IntRect Rect, Image* Image){
	_rect = Rect;
	added = false;
	forshow = false;
	layer = BASE_HIGH_LAYER;
	setRectSprite(Image, Rect);
}

Image Addable::getImage() { return _image; }

Image* Addable::getImagePointer() { return &_image; }

Texture Addable::getTexture() { return _texture; }

Texture* Addable::getTexturePointer() { return &_texture; }

Sprite Addable::getSprite() { return _sprite; }

Sprite* Addable::getSpritePointer() { return &_sprite; }

IntRect Addable::getRect() { return _rect; }

IntRect Addable::getTextureRect() { return _sprite.getTextureRect(); }

int Addable::getLayer() { return layer; }

bool Addable::isAdded() { return added; }

bool Addable::isShow() { return forshow; }

void Addable::show() { forshow = true; }

void Addable::hide() { forshow = false; }

void Addable::_add() { added = true; }

void Addable::_remove() { added = false; }

void Addable::setTextureRect(IntRect Rect) { _sprite.setTextureRect(Rect); }

void Addable::setPosition(int X, int Y){
	_sprite.setPosition(X, Y);
	_rect.left = X;
	_rect.top = Y;
}

void Addable::setRectSprite(Image* Image, IntRect Rect){
	_rect = Rect;
	_texture.loadFromImage(*Image);
	_sprite.setTexture(_texture);
	_sprite.setPosition(Vector2f(Rect.left, Rect.top));
	_sprite.setTextureRect(IntRect(0, 0, Rect.width, Rect.height));
	_sprite.setTexture(_texture);
}

void Addable::setSprite(String Path) {
	_image.loadFromFile(Path);
	_texture.loadFromImage(_image);
	
	_sprite.setTextureRect(IntRect(0, 0, _rect.width, _rect.height));
	_sprite.setPosition(_rect.left, _rect.top);
	_sprite.setTexture(_texture);
}

void Addable::setRect(IntRect Rect) { _rect = Rect; _sprite.setPosition(Rect.left, Rect.top); }

void Addable::setLayer(unsigned int Layer) { layer = Layer; }

void Addable::createMaskFromColor(Color color, IntRect Rect){
	if(Rect.height && Rect.width && _image.getSize().x && _image.getSize().y){
		_image.createMaskFromColor(color);
		_texture.loadFromImage(_image);
		_sprite.setTextureRect(Rect);
		_sprite.setTexture(_texture);
	}
}

void Addable::createMaskFromColor(Color color){
	if(_rect.height && _rect.width && _image.getSize().x && _image.getSize().y){
		_image.createMaskFromColor(color);
		_texture.loadFromImage(_image);
		_sprite.setTextureRect(_rect);
		_sprite.setTexture(_texture);
	}
}

void Addable::draw(RenderWindow* window){};

}
