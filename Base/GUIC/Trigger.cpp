#include "Trigger.hpp"

namespace guic

{

Trigger::Trigger(){};

Trigger::Trigger(IntRect Rect) :Interface(Rect){
	createMaskFromColor(Color::White);
}
		
Trigger::Trigger(IntRect Rect, String File) :Interface(Rect, File){
	createMaskFromColor(Color::White);
}
		
Trigger::Trigger(IntRect Rect, Image* Image) :Interface(Rect, Image){
	createMaskFromColor(Color::White);
}

bool Trigger::LMB(Event event, Vector2f pos){
	if (event.type == Event::MouseButtonPressed){
		if (event.mouseButton.button == Mouse::Left){
			if(getRect().contains(pos.x, pos.y)) {return 1;}
		}
	}
	return 0;
}

bool Trigger::LMB(Modal modal){
	if (modal.event.type == Event::MouseButtonPressed){
		if (modal.event.mouseButton.button == Mouse::Left){
			if (getRect().contains(modal.pos.x, modal.pos.y)){return 1;}
		}
	}
	return 0;
}

bool Trigger::RMB(Event event, Vector2f pos){
	if (event.type == Event::MouseButtonPressed){
		if (event.mouseButton.button == Mouse::Right){
			if (getRect().contains(pos.x, pos.y)){return 1;}
		}
	}
	return 0;
}

bool Trigger::RMB(Modal modal){
	if (modal.event.type == Event::MouseButtonPressed){
		if (modal.event.mouseButton.button == Mouse::Right){
			if (getRect().contains(modal.pos.x, modal.pos.y)){return 1;}
		}
	}
	return 0;
}

bool Trigger::Highlight(Event event, Vector2f pos){
	if (getRect().contains(pos.x, pos.y)){return 1;}
	return 0;
}
		
bool Trigger::Highlight(Modal modal){
	if (getRect().contains(modal.pos.x, modal.pos.y)){return 1;}
	return 0;
}

};
