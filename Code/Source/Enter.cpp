#include <GUIC/Enter.hpp>

namespace guic

{

Enter::Enter():Trigger(){
	counter = 0;
	shift = false;
	setLayer(GUIC_BASE_ENTER_LAYER);
};

Enter::Enter(IntRect enterRect):Trigger(enterRect){
	defpos.x = enterRect.left+GUIC_BASE_ENTER_INTERVAL;
	defpos.y = enterRect.top+enterRect.height/4+title.getCharHeight()/6-title.getCharHeight()/2;
	title.setPosition(defpos);
	leftpos = defpos;
	
	counter = 0;
	shift = false;
	setLayer(GUIC_BASE_ENTER_LAYER);
};

Enter::Enter(IntRect enterRect, Image* enterImage):Trigger(enterRect, enterImage){
	defpos.x = enterRect.left+GUIC_BASE_ENTER_INTERVAL;
	defpos.y = enterRect.top+enterRect.height/4+title.getCharHeight()/6-title.getCharHeight()/2;
	title.setPosition(defpos);
	leftpos = defpos;
	
	counter = 0;
	shift = false;
	setLayer(GUIC_BASE_ENTER_LAYER);
};

Enter::Enter(IntRect enterRect, String file):Trigger(enterRect, file){
	defpos.x = enterRect.left+GUIC_BASE_ENTER_INTERVAL;
	defpos.y = enterRect.top+enterRect.height/4+title.getCharHeight()/6-title.getCharHeight()/2;
	title.setPosition(defpos);
	leftpos = defpos;
	
	counter = 0;
	shift = false;
	setLayer(GUIC_BASE_ENTER_LAYER);
};

void Enter::control(Modal modal){
	if (modal.event.type == Event::MouseButtonPressed){
		isEditMode = false;
		changed = true;
		title.setPosition(defpos);
		
		if (modal.event.mouseButton.button == Mouse::Left){
			if (getRect().contains(modal.pos.x, modal.pos.y)){
				if(Highlight(modal)){
					isEditMode = true;
					title.setPosition(leftpos);
				}
			}
		}
	}

	if (isEditMode && modal.event.type == sf::Event::TextEntered && modal.event.text.unicode < 1280){
		if(modal.event.text.unicode==8){
			if(shift){
				Vector2f pos = leftpos;
				pos.x += title.getCharWidth();
				leftpos = pos;
				counter--;
				if(counter==0){
					shift = false;
				}
			}
			if(str.length()){
				str.pop_back();
			}
		} else {
			str += static_cast<char>(modal.event.text.unicode);
			if(!(title.getTitleWidth()<getRect().width-GUIC_BASE_ENTER_INTERVAL*3)){
				counter++;
				Vector2f pos = leftpos;
				pos.x -= title.getCharWidth();
				leftpos = pos;
				shift = true;
			}
		}
		
		title.setPosition(leftpos);
		title.setString(str);
		changed = true;
	}
}

std::string Enter::getValue(){ return str; }

void Enter::setRect(IntRect Rect){
	Trigger::setRect(Rect);
	defpos.x = Rect.left+GUIC_BASE_ENTER_INTERVAL;
	defpos.y = Rect.top+Rect.height/4+title.getCharHeight()/6-title.getCharHeight()/2;
	leftpos = defpos;
	changed = true;
}

void Enter::setValue(std::string enterStr){ str = enterStr; changed = true; }

void Enter::draw(RenderWindow* window){
	Trigger::draw(window);
	title.draw(window);
}

}
