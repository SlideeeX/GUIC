#include "ModalWindow.hpp"

namespace guic

{

ModalWindow::ModalWindow(int W, int H, String Name) :Container(IntRect(0, 0, W, H)){
	window.create(VideoMode(W, H), Name);
};

ModalWindow::ModalWindow(int W, int H, String Name, Uint32 Style) :Container(IntRect(0, 0, W, H)){
	window.create(VideoMode(W, H), Name, Style);
};

RenderWindow* ModalWindow::getWindow(){
	return &window;
}

void ModalWindow::control(){
	Event event;
	
	Vector2i localPosition = Mouse::getPosition(window);
	Vector2f pos = window.mapPixelToCoords(localPosition);
	
	insPos = pos;
	
	while(window.pollEvent(event)) { if (event.type == Event::Closed) window.close(); }
	
	insEvent = event;
	
	View view;
	view.reset(FloatRect(0, 0, window.getSize().x, window.getSize().y));
	window.setView(view);
}

void ModalWindow::display(){
	window.clear();
	
	draw(&window);
	
	window.display();
}

bool ModalWindow::isOpen(){
	return window.isOpen();
}

Modal ModalWindow::getModal(){
	Modal modal;
	modal.event = insEvent;
	modal.pos = insPos;
	return modal;
}

Event ModalWindow::getEvent(){
	return insEvent;
}

Vector2f ModalWindow::getPos(){
	return insPos;
}

Vector2u ModalWindow::getSize(){
	return window.getSize();
}

Vector2i ModalWindow::getPosition(){
	return window.getPosition();
}

void ModalWindow::setPosition(Vector2i Pos){
	window.setPosition(Pos);
}

void ModalWindow::create(int W, int H, String Title){
	window.create(VideoMode(W, H), Title);
}

void ModalWindow::create(int W, int H, String Title, Uint32 Style){
	window.create(VideoMode(W, H), Title, Style);
}

void ModalWindow::close(){
	window.close();
}

void ModalWindow::setTitle(String title){
	window.setTitle(title);
}

void ModalWindow::setSize(Vector2u size){
	window.setSize(size);
}

void ModalWindow::setVisible(bool visible){
	window.setVisible(visible);
}

void ModalWindow::setFramerateLimit(int Int){
	window.setFramerateLimit(Int);
}

}

