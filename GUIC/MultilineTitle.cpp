#include "MultilineTitle.hpp"

namespace guic

{

void MultilineTitle::create() {
	charwidth=size/2+size%2;
	charheight=size-size/3;
	lenght=0;
	Vector2f pos;
	pos.x = rect.left;
	pos.y = rect.top;
	int width = rect.width;
	int height = rect.height;
	String bufline="";
	
	for(int i=0; i<GUIC_MAX_MLTITLE_LENGHT; i++){
		words[i].clear();
	}
	
	for(int i=0, j=0; i<linetitle.getSize()+1; i++){
		words[j].operator +=(linetitle[i]);
		if(linetitle[i]==' ' || linetitle[i]=='\0'){
			j++;
		}
	}
	for(int i=0, j=0, k=0; !words[i].isEmpty() && i<GUIC_MAX_MLTITLE_ROWS; i++){
		lenght += words[i].getSize()*charwidth;
		bufline.operator +=(words[i]);
		if(lenght<width || k==0){
			lines[j].setString(bufline);
			lines[j].setPosition(pos);
			lines[j].setFont(font);
			lines[j].setCharacterSize(size);
			lines[j].setFillColor(Color::Black);
			j++;
			k++;
		} else {
			lenght = 0;
			pos.y += size;
			bufline="";
			i--;
			k=0;
		}
	}
}

MultilineTitle::MultilineTitle(){
	size = GUIC_BASE_CHAR_SIZE;
	linetitle.clear();
	setLayer(GUIC_BASE_MLTITLE_LAYER);
	font = BaseFont;
};

MultilineTitle::MultilineTitle(IntRect Rect, const char* Title, String File) :Interface(Rect, File){
	linetitle = Title;
	
	size = GUIC_BASE_CHAR_SIZE;
	font = BaseFont;
	
	createMaskFromColor(Color::White);
	setSprite(File);
	create();
	
	setLayer(GUIC_BASE_MLTITLE_LAYER);
};
		
MultilineTitle::MultilineTitle(IntRect Rect, const char* Title, Image* Image) :Interface(Rect, Image){
	linetitle = Title;
	
	size = GUIC_BASE_CHAR_SIZE;
	font = BaseFont;
	
	createMaskFromColor(Color::White);
	setRectSprite(Image, Rect);
	create();
		
	setLayer(GUIC_BASE_MLTITLE_LAYER);
};
		
MultilineTitle::MultilineTitle(IntRect Rect, const char* Title) :Interface(Rect){
	linetitle = Title;
			
	size = GUIC_BASE_CHAR_SIZE;
	font = BaseFont;
	
	createMaskFromColor(Color::White);
	create();
	
	setLayer(GUIC_BASE_MLTITLE_LAYER);
};

int MultilineTitle::getCharacterSize(){
	return size;
}

float MultilineTitle::getCharWidth(){ return charwidth; }
		
void MultilineTitle::setString(String string){
	linetitle = string;
	create();
}

void MultilineTitle::setFont(Font Font){
	font = Font;
	create();
}
		
void MultilineTitle::setColor(Color Color){
	for(int i=0; lines[i].getString()!=""; i++){
		lines[i].setFillColor(Color);
	}
}
		
void MultilineTitle::setPosition(float x, float y){
	for(int i=0; lines[i].getString()!=""; i++){
		lines[i].setPosition(x, y);
	}
}
		
void MultilineTitle::setRect(IntRect Rect){
	rect = Rect;
	create();
}
		
void MultilineTitle::setCharacterSize(int Size){
	size = Size;
	create();
}
		
void MultilineTitle::draw(RenderWindow* window){
	window->draw(getSprite());
	for(int i=0; lines[i].getString()!=""; i++){
		window->draw(lines[i]);
	}
}

}
