#include <GUIC/Container.hpp>

namespace guic

{

Container::Container(){ setLayer(GUIC_BASE_CONTAINER_LAYER); }

Container::Container(IntRect containerRect) :Interface(containerRect){ setLayer(GUIC_BASE_CONTAINER_LAYER); };

void Container::add(Addable &item){
	IntRect RectA = getRect();
	IntRect RectB = item.getRect();
	
	item.setRect(IntRect(RectA.left+RectB.left, RectA.top+RectB.top, RectB.width, RectB.height));
	items.item[items.size]=&item;
	items.item[items.size]->_add();
	items.size++;
	
	changed = true;
}

void Container::remove(Addable &item){
	for(int i=0; i!=items.size; i++){
		if(items.item[i]==&item){
			items.item[i]->_remove();
			changed = true;
			break;
		}
	}
}

void Container::clear(){
	items.size = 0;
}

void Container::control(Modal modal){
	for(int i=0; i<items.size; i++){
		items.item[i]->control(modal);
		if(items.item[i]->isShow() && items.item[i]->isChanged()) {
			changed = true;
			break;
		}
	}
}

void Container::draw(RenderWindow* window){
	if(items.size<1) return;
	
	for(int j=1; j<=GUIC_MAX_LAYER; j++){
		for(int i=0; i<items.size; i++){
			if(items.item[i]->isShow() && items.item[i]->getLayer()==j) {
				items.item[i]->draw(window);
				items.item[i]->_unchange();
			}
		}
	}
	
	for(int i=0; i<items.size; i++){ // И это не работает
		if(items.item[i]->isShow() && items.item[i]->getLayer()==0){
			items.item[i]->draw(window);
			items.item[i]->_unchange();
		}
	}
	
	changed = false;
}

};

