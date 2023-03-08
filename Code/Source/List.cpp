#include <GUIC/List.hpp>

namespace guic

{

List::List(){
	count = 0;
	
	setLayer(GUIC_BASE_LIST_LAYER);
}

List::List(IntRect listRect, ListItems listItems[], String file, int listCount):Trigger(listRect, file){
	w = listRect.width;
	h = listRect.height;
	
	x = listRect.left; y = listRect.top;
	count = listCount;
	
	rect = listRect;
	
	item_w=0; item_h=0;
	
	create(listItems);
	setLayer(GUIC_BASE_LIST_LAYER);
}

List::List(IntRect listRect, ListItems listItems[], Image* listImage, int listCount) :Trigger(listRect, listImage){
	w = listRect.width;
	h = listRect.height;
	
	x = listRect.left; y = listRect.top;
	
	count = listCount;
	
	rect = listRect;
	
	item_w=0; item_h=0;
	
	create(listItems);
	setLayer(GUIC_BASE_LIST_LAYER);
}

void List::createOnlyText(){
	for(int i=0; i<count; i++){
		items[i].title.setString(items[i].name);
		items[i].title.setCharacterSize(GUIC_BASE_CHAR_SIZE);
		items[i].title.setColor(BaseTextColor);
		
		if(items[i].title.getTitleWidth()>item_w){
			item_w = items[i].title.getTitleWidth();
		}
		if(items[i].title.getTitleHeight()>item_h){
			item_h = items[i].title.getTitleHeight();
		}
	}
	
	metacount = w/item_w;
	h_metacount = h/item_h;
	
	factcount = ((metacount + count) - abs(metacount - count))/2;
	factcount = factcount<1 ? 1 : factcount;
	
	h_factcount = ((h_metacount + count) - abs(h_metacount - count))/2;
	h_factcount = h_factcount<1 ? 1 : h_factcount;
	
	rows = abs((count/factcount)-(count/h_factcount));
	columns = abs((count/h_factcount)-(count/factcount));
	
	updown ? (columns=count/h_factcount, rows=h_factcount) : (rows=count/factcount, columns=factcount);
	
	gap = abs((w - item_w*columns) / (columns+1));
	h_gap = abs((h - item_h*rows) / (rows+1));
	
	dif_gap = w - (item_w+gap)*columns;
	gap += dif_gap/(columns);
	
	dif_h_gap = h - (item_h+h_gap)*rows;
	h_gap += dif_h_gap/(rows);
	
	IntRect NewItemRect;
		
	if(updown){
		for(int i=0, l=0; i<columns && l<count; i++){
			vector.x = gap;
			vector.x += i*(item_w+gap);
			vector.x += rect.left;
			for(int j=0; j<rows && l<count; j++, l++){
				if(items[l].title.getString().isEmpty()) continue;
				
				vector.y = h_gap;
				vector.y += j*(item_h+h_gap);
				vector.y += rect.top;
				
				NewItemRect.width = item_w+gap;
				NewItemRect.height = item_h+h_gap;
				NewItemRect.left = vector.x-gap;
				NewItemRect.top = vector.y-h_gap;
				
				setItemRect(l, NewItemRect);
				centerItem(l);
			}
		}
	} else {
		for(int i=0, l=0; i<rows && l<count; i++){
			vector.y = h_gap;
			vector.y += i*(item_h+h_gap);
			vector.y += rect.top;
			
			for(int j=0; j<columns && l<count; j++, l++){
				if(items[l].title.getString().isEmpty()) continue;
				
				vector.x = gap;
				vector.x += j*(item_w+gap);
				vector.x += rect.left;
				
				NewItemRect.width = item_w+gap;
				NewItemRect.height = item_h+h_gap;
				NewItemRect.left = vector.x-gap;
				NewItemRect.top = vector.y-h_gap;
				
				setItemRect(l, NewItemRect);
				centerItem(l);
			}
		}
	}
	
	rect.width = w;
	rect.height = h;
	
	Addable::setRect(rect);
}

void List::createOnlyImages(){
	
	for(int i=0; i<count; i++){
		items[i].texture.loadFromFile(items[i].imagename);
		items[i].sprite.setTexture(items[i].texture);
		
		if(items[i].sprite.getTextureRect().width>item_w){
			item_w = items[i].sprite.getTextureRect().width;
		}
		if(items[i].sprite.getTextureRect().height>item_h){
			item_h = items[i].sprite.getTextureRect().height;
		}
	}
	
	metacount = w/item_w;
	h_metacount = h/item_h;
	
	factcount = ((metacount + count) - abs(metacount - count))/2;
	factcount = factcount<1 ? 1 : factcount;
	
	h_factcount = ((h_metacount + count) - abs(h_metacount - count))/2;
	h_factcount = h_factcount<1 ? 1 : h_factcount;
	
	rows = abs((count/factcount)-(count/h_factcount));
	columns = abs((count/h_factcount)-(count/factcount));
	
	updown ? (columns=count/h_factcount, rows=h_factcount) : (rows=count/factcount, columns=factcount);
	
	gap = abs((w - item_w*columns) / (columns+1));
	h_gap = abs((h - item_h*rows) / (rows+1));
	
	dif_gap = w - (item_w+gap)*columns;
	gap += dif_gap/(columns);
	
	dif_h_gap = h - (item_h+h_gap)*rows;
	h_gap += dif_h_gap/(rows);
	
	IntRect NewItemRect;
	
	if(updown){
		for(int i=0, l=0; i<columns && l<count; i++){
			
			vector.x = gap;
			vector.x += i*(item_w+gap);
			vector.x += rect.left;
		
			for(int j=0; j<rows && l<count; j++, l++){
				vector.y = gap;
				vector.y += j*(item_w+gap);
				vector.y += rect.top;
				
				NewItemRect.width = item_w+gap;
				NewItemRect.height = item_h+h_gap;
				NewItemRect.left = vector.x-gap;
				NewItemRect.top = vector.y-h_gap;
				
				setItemRect(l, NewItemRect);
				centerItem(l);
			}
		}
	} else {
		for(int i=0, l=0; i<rows && l<count; i++){
			
			vector.y = h_gap;
			vector.y += i*(item_h+h_gap);
			vector.y += rect.top;
		
			for(int j=0; j<columns && l<count; j++, l++){
				vector.x = gap;
				vector.x += j*(item_w+gap);
				vector.x += rect.left;
				
				NewItemRect.width = item_w+gap;
				NewItemRect.height = item_h+h_gap;
				NewItemRect.left = vector.x-gap;
				NewItemRect.top = vector.y-h_gap;
				
				setItemRect(l, NewItemRect);
				centerItem(l);
			}
		}
	}
	
	rect.width = w;
	rect.height = h;
	
	Addable::setRect(rect);
}

void List::createAll(){
	float image_w = 0;
	float image_h = 0;
	
	for(int i=0; i<count; i++){
		items[i].texture.loadFromFile(items[i].imagename);
		items[i].sprite.setTexture(items[i].texture);
		
		items[i].title.setString(items[i].name);
		items[i].title.setCharacterSize(GUIC_BASE_CHAR_SIZE);
		items[i].title.setColor(BaseTextColor);
		
		if(items[i].title.getTitleWidth()+items[i].sprite.getTextureRect().width>item_w){
			item_w = items[i].title.getTitleWidth()+items[i].sprite.getTextureRect().width;
		}
		
		if(items[i].title.getTitleHeight()+items[i].sprite.getTextureRect().height>item_h){
			item_h = items[i].title.getTitleHeight()+items[i].sprite.getTextureRect().height;
		}
	}
	
	metacount = w/item_w;
	h_metacount = h/item_h;
	
	factcount = ((metacount + count) - abs(metacount - count))/2;
	factcount = factcount<1 ? 1 : factcount;
	
	h_factcount = ((h_metacount + count) - abs(h_metacount - count))/2;
	h_factcount = h_factcount<1 ? 1 : h_factcount;
	
	rows = abs((count/factcount)-(count/h_factcount));
	columns = abs((count/h_factcount)-(count/factcount));
	
	updown ? (columns=count/h_factcount, rows=h_factcount) : (rows=count/factcount, columns=factcount);
	
	gap = abs((w - item_w*columns) / (columns+1));
	h_gap = abs((h - item_h*rows) / (rows+1));
	
	dif_gap = w - (item_w+gap)*columns;
	gap += dif_gap/(columns);
	
	dif_h_gap = h - (item_h+h_gap)*rows;
	h_gap += dif_h_gap/(rows);
	
	IntRect NewItemRect;
	
	if(updown){
		for(int i=0, l=0; i<columns && l<count; i++){
			vector.x = gap;
			vector.x += i*(item_w+gap);
			vector.x += rect.left;
		
			for(int j=0; j<rows && l<count; j++, l++){
				
				int image_h = items[i].sprite.getTextureRect().height;
				int image_w = items[i].sprite.getTextureRect().width;
				
				vector.y = gap;
				vector.y += j*(item_w+gap);
				vector.y += rect.top;
				
				NewItemRect.width = item_w+gap;
				NewItemRect.height = item_h+h_gap;
				NewItemRect.left = vector.x-gap;
				NewItemRect.top = vector.y-h_gap;
				
				setItemRect(l, NewItemRect);
				centerItem(l);
			}
		}
	} else {
		for(int i=0, l=0; i<rows && l<count; i++){
			
			vector.y = h_gap;
			vector.y += i*(item_h+h_gap)+y;
		
			for(int j=0; j<columns && l<count; j++, l++){
		
				int image_h = items[i].sprite.getTextureRect().height;
				int image_w = items[i].sprite.getTextureRect().width;
				
				vector.x = gap;
				vector.x += j*(item_w+gap)+x;
				
				NewItemRect.width = item_w+gap;
				NewItemRect.height = item_h+h_gap;
				NewItemRect.left = vector.x-gap;
				NewItemRect.top = vector.y-h_gap;
				
				setItemRect(l, NewItemRect);
				centerItem(l);
			}
		}
	}
	
	rect.width = w;
	rect.height = h;
	
	Addable::setRect(rect);
}

void List::create(ListItems* listItems){
	bool namebool=0, imagebool=0;
	
	for(int i=0; i<count; i++){
		if(listItems[i].imagename != ""){
			imagebool++;
		}
		if(listItems[i].name != ""){
			namebool++;
		}
		items[i] = listItems[i];
	}
	if(imagebool && namebool) {
		createAll();
	} else if (!namebool && imagebool) {
		createOnlyImages();
	} else if (count>0){
		createOnlyText();
	}
	
	changed = true;
}

Sprite List::getItemSprite(int num){
	return items[num].sprite;
}

void List::setItemSprite(Sprite sprite, int num){
	items[num].sprite = sprite;
	changed = true;
}

void List::setUpDown(bool set){
	updown = set;
	create(items);
}

void List::setItemBackgrounds(String file){
	Image image;
	image.loadFromFile(file);
	
	for(int i=0; i<count; i++){
		items[i].background.setRectImage(&image, items[i].background.getRect());
	}
	
	changed = true;
}

void List::setItemBackgrounds(Image* listImage){
	for(int i=0; i<count; i++){
		items[i].background.setRectImage(listImage, items[i].background.getRect());
	}
	
	changed = true;
}

void List::setItemBackgrounds(Color color){
	for(int i=0; i<count; i++){
		setItemBackground(color, i);
	}
	
	changed = true;
}

void List::setItemBackground(Color color, int num){
	IntRect rect = getItemRect(num);
	
	rect.width+=!(bool)rect.width;
	rect.height+=!(bool)rect.height;
	
	Image image;
	image.create(rect.width, rect.height, color);
	
	items[num].background.setRectImage(&image, rect);
	items[num].background.createMaskFromColor(Color::White, rect);
	
	changed = true;
}

void List::hideItemBackgrounds(){
	for(int i=0; i<count; i++){
		items[i].background.hide();
	}
	
	changed = true;
}

void List::showItemBackground(int num){
	items[num].background.show();
	changed = true;
}

void List::hideItemBackground(int num){
	items[num].background.hide();
	changed = true;
}

void List::setItemColor(Color color, int num){
	items[num].sprite.setColor(color);
	changed = true;
}

IntRect List::getItemRect(int num){
	return items[num].rect;
}

void List::setItemRect(int num, IntRect listRect){
	float title_x = abs(items[num].rect.left-items[num].title.getPosition().x);
	float title_y = abs(items[num].rect.top-items[num].title.getPosition().y);
	float sprite_x = abs(items[num].rect.left-items[num].sprite.getPosition().x);
	float sprite_y = abs(items[num].rect.top-items[num].sprite.getPosition().y);
	
	items[num].rect.left = listRect.left;
	items[num].rect.top = listRect.top;
	items[num].rect.width = listRect.width;
	items[num].rect.height = listRect.height;
	
	title_x += listRect.left;
	title_y += listRect.top;
	sprite_x += listRect.left;
	sprite_y += listRect.top;
	
	items[num].sprite.setPosition(sprite_x, sprite_y);
	items[num].title.setPosition(title_x, title_y);
	items[num].background.setRect(listRect);
	
	changed = true;
}

void List::centerItem(int num){
	float title_x = items[num].rect.left+items[num].rect.width/2-items[num].title.getTitleWidth()/2;
	float title_y = items[num].rect.top+items[num].rect.height/2-items[num].title.getTitleHeight();
	float sprite_x = items[num].rect.left+items[num].rect.width/2-items[num].sprite.getTextureRect().width/2;
	float sprite_y = items[num].rect.top+items[num].rect.height/2-items[num].sprite.getTextureRect().height/2;
	
	if(items[num].sprite.getTextureRect().width>0){
		items[num].sprite.setPosition(sprite_x, sprite_y-items[num].title.getTitleHeight());
		items[num].title.setPosition(title_x, title_y+(items[num].sprite.getTextureRect().height-items[num].title.getTitleHeight()*2.5));
	} else {
		items[num].sprite.setPosition(sprite_x, sprite_y);
		items[num].title.setPosition(title_x, title_y);
	}
	
	changed = true;
}

void List::setRect(IntRect listRect){
	Trigger::setRect(listRect);
	IntRect NewItemRect;
	
	for(int i=0; i<count; i++){	
		NewItemRect = getItemRect(i);
		
		NewItemRect.left += listRect.left;
		NewItemRect.top += listRect.top;
		
		setItemRect(i, NewItemRect);
	}
	
	changed = true;
}

ListItems* List::getItems(){
	return items;
}

void List::addItem(ListItems item){
	count++;
	items[count] = item;
	create(items);
};

void List::setTitleSize(unsigned int size) {
	for(int i=0; i<count; i++){
		items[i].title.setCharacterSize(size);
	}
	create(getItems());
}

void List::setTitleFont(Font font){
	for(int i=0; i<count; i++){
		items[i].title.setFont(font);
	}
	
	changed = true;
}

void List::setTitleString(String string, int num){
	items[num].title.setString(string);
	create(getItems());
}

void List::maximizeWidth(){
	IntRect Rect = getRect();
	IntRect ItemRect;
	
	ItemRect.width = Rect.width;
	
	for(int i=0; i<count; i++){
		ItemRect.top = getItemRect(i).top;
		ItemRect.left = getItemRect(i).left;
		ItemRect.height = getItemRect(i).height;
		setItemRect(i, ItemRect);
	}
	
	changed = true;
}

void List::maximizeHeight(){
	IntRect Rect = getRect();
	IntRect ItemRect;
	
	ItemRect.height= Rect.height;
	
	for(int i=0; i<count; i++){
		ItemRect.top = getItemRect(i).top;
		ItemRect.left = getItemRect(i).left;
		ItemRect.width = getItemRect(i).width;
		setItemRect(i, ItemRect);
	}
	
	changed = true;
}

void List::setListSide(Vector2i listSides){
	const IntRect MainRect = getRect();
	IntRect NewItemRect;
	
	if(listSides.x>0){
		int k=0;
		int item_width=0;
		int lenght=0;
		int checklenght=0;
		int item_top=0;
		for(int i=0; i<count; i++){
			if(items[i].title.getString().isEmpty()) continue;
			
			item_width = items[i].title.getTitleWidth()+items[i].sprite.getTextureRect().width;
			
			checklenght+=item_width+GUIC_BASE_LIST_TAB*2;
			
			if(MainRect.width<checklenght && k<150){
				k++;
				lenght=0;
				checklenght=0;
				i--;
				continue;
			}
			
			NewItemRect = getItemRect(i);
			
			item_top = NewItemRect.height;
			
			NewItemRect.left = lenght;
			NewItemRect.width = item_width+GUIC_BASE_LIST_TAB*2;
			NewItemRect.top = NewItemRect.height*k;
			
			setItemRect(i, NewItemRect);
			items[i].title.setPosition(Vector2f(NewItemRect.left+GUIC_BASE_LIST_TAB, items[i].title.getPosition().y));
			lenght+=item_width+GUIC_BASE_LIST_TAB*2;
		}
	} else if(listSides.x<0) {
		int k=0;
		int item_width=0;
		int lenght=w;
		int checklenght=0;
		for(int i=0; i<count; i++){
			if(items[i].title.getString().isEmpty()) continue;
			
			item_width = items[i].title.getTitleWidth()+items[i].sprite.getTextureRect().width;
			
			checklenght+=item_width+GUIC_BASE_LIST_TAB*2;
			lenght-=item_width+GUIC_BASE_LIST_TAB*2;
			
			if(MainRect.width<checklenght && k<150){
				k++;
				lenght=w;
				checklenght=0;
				i--;
				continue;
			}
	
			NewItemRect = getItemRect(i);
			
			NewItemRect.left = lenght;
			NewItemRect.width = item_width+GUIC_BASE_LIST_TAB*2;
			NewItemRect.top = NewItemRect.height*k;
			
			setItemRect(i, NewItemRect);
			items[i].title.setPosition(Vector2f(NewItemRect.left-GUIC_BASE_LIST_TAB, items[i].title.getPosition().y));
		}
	}
	
	if(listSides.y>0){
		int k=0;
		int item_height=0;
		int item_width=0;
		int checklenght=0;
		int high=0;
		int item_top=0;
		for(int i=0, l=0; i<count; i++){
			if(items[i].title.getString().isEmpty()) continue;
			
			item_height = items[i].title.getTitleHeight()+items[i].sprite.getTextureRect().height;
			item_width = items[i].title.getTitleWidth()+items[i].sprite.getTextureRect().width;
			
			NewItemRect = getItemRect(i);
			
			checklenght+=NewItemRect.width;
			
			if(MainRect.width<checklenght && k<150){
				k++;
				checklenght=0;
				high+=item_height+GUIC_BASE_LIST_INTERVAL*2;
				i--;
				continue;
			}
			
			NewItemRect.height = item_height+GUIC_BASE_LIST_INTERVAL*2;
			NewItemRect.top = high;
			
			setItemRect(i, NewItemRect);
			items[i].title.setPosition(Vector2f(items[i].title.getPosition().x, NewItemRect.top));
		}
	} else if(listSides.y<0) {
		int k=0;
		int item_height=0;
		int item_width=0;
		int checklenght=0;
		int high=0;
		int item_top=0;
		for(int i=0, l=0; i<count; i++){
			if(items[i].title.getString().isEmpty()) continue;
			
			item_height = items[i].title.getTitleHeight()+items[i].sprite.getTextureRect().height;
			item_width = items[i].title.getTitleWidth()+items[i].sprite.getTextureRect().width;
			
			NewItemRect = getItemRect(i);
			
			checklenght+=NewItemRect.width;
			
			if(MainRect.width<checklenght && k<150){
				k++;
				checklenght=0;
				i--;
				continue;
			}
			
			high=h-(item_height+GUIC_BASE_LIST_INTERVAL*2)*k;
			
			NewItemRect.height = item_height+GUIC_BASE_LIST_INTERVAL*2;
			NewItemRect.top = high;
			
			setItemRect(i, NewItemRect);
			items[i].title.setPosition(Vector2f(items[i].title.getPosition().x, NewItemRect.top));
		}
	}
	
	if(!(bool)listSides.x && !(bool)listSides.y){
		create(items);
	}
	
	changed = true;
}

void List::draw(RenderWindow* window) {
	window->draw(getSprite());
	for(int i=0; i<count; i++){
		if(items[i].background.isShow()) items[i].background.draw(window);
		window->draw(items[i].sprite);
		items[i].title.draw(window);
	}
}

bool List::LMB(Event event, Vector2f pos, int num) {
	if (event.type == Event::MouseButtonPressed){
		if (event.mouseButton.button == Mouse::Left){
			for(int i=0; i<=count && i<=num; i++){
				if (getItemRect(num).contains(pos.x, pos.y)){
					changed = true;
					return i+1;
				}
			}
		}
	}
	return 0;
}

bool List::LMB(Modal modal, int num) {
	if (modal.event.type == Event::MouseButtonPressed){
		if (modal.event.mouseButton.button == Mouse::Left){
			for(int i=0; i<=count && i<=num; i++){
				if (getItemRect(num).contains(modal.pos.x, modal.pos.y)){
					changed = true;
					return i+1;
				}
			}
		}
	}
	return 0;
}

bool List::RMB(Event event, Vector2f pos, int num) {
	if (event.type == Event::MouseButtonPressed){
		if (event.mouseButton.button == Mouse::Right){
			for(int i=0; i<=count && i<=num; i++){
				if (getItemRect(num).contains(pos.x, pos.y)){
					changed = true;
					return i+1;
				}
			}
		}
	}
	return 0;
}

bool List::RMB(Modal modal, int num) {
	if (modal.event.type == Event::MouseButtonPressed){
		if (modal.event.mouseButton.button == Mouse::Right){
			for(int i=0; i<=count && i<=num; i++){
				if (getItemRect(num).contains(modal.pos.x, modal.pos.y)){
					changed = true;
					return i+1;
				}
			}
		}
	}
	return 0;
}

bool List::Highlight(Event event, Vector2f pos, int num){
	if (getItemRect(num).contains(pos.x, pos.y)){
		changed = true;
		return 1;
	}
	return 0;
}

bool List::Highlight(Modal modal, int num){
	if (getItemRect(num).contains(modal.pos.x, modal.pos.y)){
		changed = true;
		return 1;
	}
	return 0;
}

}
