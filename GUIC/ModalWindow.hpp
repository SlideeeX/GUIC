#ifndef MODALWINDOW_HPP
#define MODALWINDOW_HPP

#include "Container.hpp"

namespace guic

{

using namespace sf;

class ModalWindow :public Container

{

private:
	RenderWindow window; 
	
	Event insEvent;
	Vector2f insPos;
	
public:
	ModalWindow(int W, int H, String Name);
	
	ModalWindow(int W, int H, String Name, Uint32 Style);
	
	RenderWindow* getWindow();
	
	void control();
	
	void display();
	
	bool isOpen();
	
	Modal getModal();
	
	Event getEvent();
	
	Vector2f getPos();
	
	Vector2u getSize();
	
	Vector2i getPosition();
	
	void setPosition(Vector2i Pos);
	
	void create(int W, int H, String Title);
	
	void create(int W, int H, String Title, Uint32 Style);
	
	void close();
	
	void setTitle(String title);
	
	void setSize(Vector2u size);
	
	void setVisible(bool visible);
	
	void setFramerateLimit(int Int);
};

}

#endif
