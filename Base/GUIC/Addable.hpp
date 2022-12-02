#ifndef ADDABLE_H
#define ADDABLE_H

#include "Variables.hpp"

#ifndef GUIC_MAX_ITEMS
#define GUIC_MAX_ITEMS 10000
#endif

namespace guic

{

using namespace sf;

struct Modal
{
	Event event;
	Vector2f pos;
};

class Addable

{

public:
	
	Image getImage();
	
	Image* getImagePointer();
	
	Texture getTexture();
	
	Texture* getTexturePointer();
	
	Sprite getSprite();
	
	Sprite* getSpritePointer();
	
	IntRect getRect();
	
	IntRect getTextureRect();
	
	int getLayer();
	
	bool isAdded();
		
	bool isShow();
	
	void show();
		
	void hide();
	
	void _add();
		
	void _remove();
	
	void setTextureRect(IntRect Rect);
	
	void setPosition(int X, int Y);
	
	void setRectSprite(Image* Image, IntRect Rect);
	
	void setSprite(String Path);
	
	virtual void setRect(IntRect Rect);
	
	void setLayer(unsigned int Layer);
	
	void createMaskFromColor(Color color, IntRect Rect);
	
	void createMaskFromColor(Color color);
	
	virtual void draw(RenderWindow* window);
	
protected:
	
	bool added;
	bool forshow;
	unsigned int layer;
	
	Addable();
	
	Addable(IntRect Rect);
	
	Addable(IntRect Rect, Image* Image);
	
private:
	
	IntRect _rect;
	Image _image;
	Texture _texture;
	Sprite _sprite;
	
};

struct Items
{
	Addable* item[GUIC_MAX_ITEMS];
	int size = 0;
};

}

#endif
