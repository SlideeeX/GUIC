#include <GUIC/Interface.hpp>

namespace guic

{
	
Interface::Interface() :Addable(){
	setLayer(GUIC_BASE_INTERFACE_LAYER);
}

Interface::Interface(IntRect rect) :Addable(rect){
	setLayer(GUIC_BASE_INTERFACE_LAYER);
};

Interface::Interface(IntRect rect, String file) :Addable(rect){
	if(!file.isEmpty()) {
		setImage(file);
	}
	
	setLayer(GUIC_BASE_INTERFACE_LAYER);
};
	
Interface::Interface(IntRect rect, Image* image) :Addable(rect, image){
	setLayer(GUIC_BASE_INTERFACE_LAYER);
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
