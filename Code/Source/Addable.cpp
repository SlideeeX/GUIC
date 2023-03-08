#include <GUIC/Addable.hpp>

#ifndef BASE_HIGH_LAYER
#define BASE_HIGH_LAYER 0
#endif

namespace guic

{
	
Addable::Addable()
{
	_rect = IntRect(0, 0, 0, 0);
	added = false;
	forshow = false;
	layer = BASE_HIGH_LAYER;
	_sprite = new Sprite;
	_image = new Image;
	_texture = new Texture;
}
	
Addable::Addable(IntRect rect){
	_rect = rect;
	added = false;
	forshow = false;
	layer = BASE_HIGH_LAYER;
	_sprite = new Sprite;
	_image = new Image;
	_texture = new Texture;
};
	
Addable::Addable(IntRect rect, Image* image){
	_rect = rect;
	added = false;
	forshow = false;
	layer = BASE_HIGH_LAYER;
	_sprite = new Sprite;
	_image = image;
	_texture = new Texture;
	
	setImage(image);
}

Image Addable::getImage() { return *_image; }

Image* Addable::getImagePointer() { return _image; }

Texture Addable::getTexture() { return *_texture; }

Texture* Addable::getTexturePointer() { return _texture; }

Sprite Addable::getSprite() { return *_sprite; }

Sprite* Addable::getSpritePointer() { return _sprite; }

IntRect Addable::getRect() { return _rect; }

IntRect Addable::getTextureRect() { return _sprite->getTextureRect(); }

int Addable::getLayer() { return layer; }

bool Addable::isAdded() { return added; }

bool Addable::isShow() { return forshow; }

bool Addable::isChanged() { return changed; }

void Addable::show() { forshow = true; changed = true; }

void Addable::hide() { forshow = false; changed = true; }

void Addable::_add() { added = true; changed = true; }

void Addable::_remove() { added = false; changed = true; }

void Addable::_unchange() { changed = false; }

void Addable::setTextureRect(IntRect rect) { _sprite->setTextureRect(rect); changed = true; }

void Addable::setPosition(int X, int Y){
	_sprite->setPosition(X, Y);
	_rect.left = X;
	_rect.top = Y;
	changed = true;
}

void Addable::setRectImage(Image* image, IntRect rect){
	_rect = rect;
	_image = image;
	_texture->loadFromImage(*_image);
	
	_sprite->setTexture(*_texture);
	_sprite->setTextureRect(IntRect(0, 0, rect.width, rect.height));
	_sprite->setPosition(Vector2f(rect.left, rect.top));
	
	changed = true;
}

void Addable::setImage(String path) {
	_image->loadFromFile(path);
	_texture->loadFromImage(*_image);
	
	_sprite->setTexture(*_texture);
	_sprite->setTextureRect(IntRect(0, 0, _rect.width, _rect.height));
	_sprite->setPosition(_rect.left, _rect.top);
	
	changed = true;
}

void Addable::setImage(Image* image) {
	_image = image;
	_texture->loadFromImage(*_image);
	
	_sprite->setTexture(*_texture);
	_sprite->setTextureRect(IntRect(0, 0, _rect.width, _rect.height));
	_sprite->setPosition(_rect.left, _rect.top);
	
	changed = true;
}

void Addable::setRect(IntRect rect) { _rect = rect; _sprite->setPosition(rect.left, rect.top); changed = true; }

void Addable::setLayer(unsigned int Layer) { layer = Layer; changed = true; }

void Addable::createMaskFromColor(Color color, IntRect rect){
	if(rect.height && rect.width && _image->getSize().x && _image->getSize().y){
		_image->createMaskFromColor(color);
		_texture->loadFromImage(*_image);
		_sprite->setTextureRect(rect);
		_sprite->setTexture(*_texture);
		changed = true;
	}
}

void Addable::createMaskFromColor(Color color){
	if(_rect.height && _rect.width && _image->getSize().x && _image->getSize().y){
		_image->createMaskFromColor(color);
		_texture->loadFromImage(*_image);
		_sprite->setTextureRect(_rect);
		_sprite->setTexture(*_texture);
		changed = true; 
	}
}

void Addable::control(Modal modal){};

void Addable::draw(RenderWindow* window){};

}
