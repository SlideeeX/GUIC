#ifndef MODALWINDOW_HPP
#define MODALWINDOW_HPP

#include "Container.hpp"

namespace guic

{

using namespace sf;

class DLLIMPORT ModalWindow :public Container

{

private:
	RenderWindow window; 
	
	Event insEvent;
	Vector2f insPos;
	Modal modal;
	
	bool _isTextEntered;
	
public:
	ModalWindow(int W, int H, String windowName);
	
	ModalWindow(int W, int H, String windowName, Uint32 windowStyle);
	
	RenderWindow* getWindow();
	
	void control();
	
	void display();
	
	bool isOpen();
	
	bool isTextEntered();
	
	Modal getModal();
	
	Event getEvent();
	
	Vector2f getPos();
	
	Vector2u getSize();
	
	Vector2i getPosition();
	
	void setPosition(Vector2i Pos);
	
	void create(int W, int H, String windowTitle);
	
	void create(int W, int H, String windowTitle, Uint32 windowStyle);
	
	void close();
	
	void setTitle(String title);
	
	void setSize(Vector2u size);
	
	void setVisible(bool visible);
	
	void setFramerateLimit(int fps);
};

}

#endif
