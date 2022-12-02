#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "Addable.hpp"

#ifndef GUIC_BASE_INTERFACE_LAYER
#define GUIC_BASE_INTERFACE_LAYER 2
#endif

#ifndef GUIC_BASE_CHAR_SIZE
#define GUIC_BASE_CHAR_SIZE 15
#endif

#ifndef GUIC_BASE_TITLE_LAYER
#define GUIC_BASE_TITLE_LAYER 5
#endif

namespace guic

{

using namespace sf;

class Interface : public Addable

{

private:

	String file;

protected:

public:
	
	Interface();
		
	Interface(IntRect Rect);
		
	Interface(IntRect Rect, String File);
		
	Interface(IntRect Rect, Image* Image);
		
	Vector2f getPosition();
		
	void draw(RenderWindow* window);
	
};

}

#endif
