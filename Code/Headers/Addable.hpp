#ifndef ADDABLE_H
#define ADDABLE_H

#include <GUIC/Variables.hpp>

#ifndef GUIC_MAX_ITEMS
#define GUIC_MAX_ITEMS 10000
#endif

namespace guic

{

using namespace sf;

struct DLLIMPORT Modal
{
	Event event;
	Vector2f pos;
};

class DLLIMPORT Addable

{

public:
	
	bool changed;
	
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
	
	bool isChanged();
	
	void show();
		
	void hide();
	
	void _add();
	
	void _remove();
	
	void _unchange();
	
	void setTextureRect(IntRect rect);
	
	void setPosition(int X, int Y);
	
	void setRectImage(Image* image, IntRect rect);
	
	void setImage(Image* image);
	
	void setImage(String path);
	
	virtual void setRect(IntRect rect);
	
	void setLayer(unsigned int Layer);
	
	void createMaskFromColor(Color color, IntRect rect);
	
	void createMaskFromColor(Color color);
	
	virtual void control(Modal modal);
	
	virtual void draw(RenderWindow* window);
	
protected:
	
	bool added;
	bool forshow;
	unsigned int layer;
	
	Addable();
	
	Addable(IntRect Rect);
	
	Addable(IntRect Rect, Image* Image);
	
private:
	
	Sprite* _sprite;
	Image* _image;
	Texture* _texture;
	IntRect _rect;
	
};

struct DLLIMPORT Items
{
	Addable* item[GUIC_MAX_ITEMS];
	int size = 0;
};

}

#endif
