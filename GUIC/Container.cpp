#include "Container.hpp"

namespace guic

{

Container::Container(){ setLayer(GUIC_BASE_CONTAINER_LAYER); }

Container::Container(IntRect Rect) :Interface(Rect){ setLayer(GUIC_BASE_CONTAINER_LAYER); };

void Container::add(Addable &Item){
	IntRect RectA = getRect();
	IntRect RectB = Item.getRect();
	
	Item.setRect(IntRect(RectA.left+RectB.left, RectA.top+RectB.top, RectB.width, RectB.height));
	
	items.item[items.size]=&Item;
	items.item[items.size]->_add();
	items.size++;
}

void Container::remove(Addable &Item){
	for(int i=0; i!=items.size; i++){
		if(items.item[i]==&Item){
			items.item[i]->_remove();
			break;
		}
	}
}

void Container::clear(){
	items.size = 0;
}

void Container::draw(RenderWindow* window){
	if(items.size<1) return;
	for(int j=1; j<=GUIC_MAX_LAYER; j++){
		for(int i=0; i<items.size; i++){
			if(items.item[i]->isShow() && items.item[i]->getLayer()==j) items.item[i]->draw(window);
		}
	}
	for(int i=0; i<items.size; i++){ // И это не работает
		if(items.item[i]->isShow() && items.item[i]->getLayer()==0) items.item[i]->draw(window);
	}
}

};

