#include "Interface.hpp"

namespace guic

{
	
Interface::Interface() :Addable(){
	file="";
	setLayer(GUIC_BASE_INTERFACE_LAYER);
}

Interface::Interface(IntRect Rect) :Addable(Rect){
	file="";
	setLayer(GUIC_BASE_INTERFACE_LAYER);
};

Interface::Interface(IntRect Rect, String File) :Addable(Rect){
	file = File;
	setRect(Rect);
	
	if(!File.isEmpty()) {
		setSprite(File);
	}
			
	forshow = false;
	added = false;
	setLayer(1);
};
	
Interface::Interface(IntRect Rect, Image* Image) :Addable(Rect, Image){
	file = "";
	setRect(Rect);
	forshow = false;
	added = false;
	
	setLayer(1);
};
		
Vector2f Interface::getPosition(){
	Vector2f out;
	out.x = getRect().left;
	out.y = getRect().top;
	return out;
}
		
void Interface::draw(RenderWindow* window){
	window->draw(getSprite());
}

}
