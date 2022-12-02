#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include "Interface.hpp"

#ifndef GUIC_BASE_CONTAINER_LAYER
#define GUIC_BASE_CONTAINER_LAYER 1
#endif

#ifndef GUIC_MAX_LAYER
#define GUIC_MAX_LAYER 6
#endif

namespace guic

{

using namespace sf;

class Container :public Interface

{

private:
	
	Items items;
	
public:
	
	Container();
		
	Container(IntRect Rect);
		
	void add(Addable &Item);
		
	void remove(Addable &Item);
		
	void clear();
		
	void draw(RenderWindow* window);
	
};

}

#endif
