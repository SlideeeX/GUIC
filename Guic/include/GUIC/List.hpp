#ifndef LIST_HPP
#define LIST_HPP

#include "Trigger.hpp"
#include "Title.hpp"

#ifndef GUIC_MAX_LIST_ITEMS
#define GUIC_MAX_LIST_ITEMS 100
#endif

#ifndef GUIC_BASE_LIST_LAYER
#define GUIC_BASE_LIST_LAYER 3
#endif

#ifndef GUIC_BASE_LIST_TAB
#define GUIC_BASE_LIST_TAB 5
#endif

#ifndef GUIC_BASE_LIST_INTERVAL
#define GUIC_BASE_LIST_INTERVAL 5
#endif

#ifndef GUIC_BASE_CHAR_SIZE
#define GUIC_BASE_CHAR_SIZE 15
#endif

namespace guic

{

using namespace sf;

struct DLLIMPORT ListItems
{
	std::string name;
	std::string imagename;
	std::string description;
	Texture texture;
	Sprite sprite;
	IntRect rect;
	Title title;
	Interface background;
};

class DLLIMPORT List :public Trigger

{

private:
	
	float w=0;
	float h=0;
	float x=0;
	float y=0;
	float item_w=0;
	float item_h=0;
	
	int count=0;
	int factcount=0;
	int metacount=0;
	int h_factcount=0;
	int h_metacount=0;
	int rows=0;
	int columns=0;
	
	float gap=0;
	float h_gap=0;
	float dif_h_gap=0;
	float dif_gap=0;
	
	bool updown=false;
	bool maximized_x=false;
	bool maximized_y=false;
	
	Vector2f vector;
	IntRect rect;
	ListItems items[GUIC_MAX_LIST_ITEMS];
	
	void createOnlyText();
	
	void createOnlyImages();
	
	void createAll();
		
	void create(ListItems* Items);
	
public:
	
	using Trigger::LMB;
	using Trigger::RMB;
	using Trigger::Highlight;
	
	List();
	
	List(IntRect Rect, ListItems Items[], String File, int Count);
	
	List(IntRect Rect, ListItems Items[], Image* Image, int Count);
	
	Sprite getItemSprite(int num);
	
	void setItemSprite(Sprite sprite, int num);
	
	void setUpDown(bool set);
	
	void setItemBackgrounds(String File);
	
	void setItemBackgrounds(Image* Image);
	
	void setItemBackgrounds(Color color);
	
	void setItemBackground(Color color, int num);
	
	void hideItemBackgrounds();
	
	void showItemBackground(int num);
	
	void hideItemBackground(int num);
	
	void setItemColor(Color color, int num);
	
	IntRect getItemRect(int num);
	
	void setItemRect(int num, IntRect Rect);
	
	void centerItem(int num);
	
	void setRect(IntRect Rect) override;
	
	ListItems* getItems();
	
	void setTitleSize(unsigned int size);
	
	void setTitleFont(Font font);
	
	void setTitleString(String string, int num);
	
	void maximizeWidth();
	
	void maximizeHeight();
	
	void setListSide(Vector2i Sides);
	
	void draw(RenderWindow* window) override;
	
	bool LMB(Event event, Vector2f pos, int num);
	
	bool LMB(Modal modal, int num);
	
	bool RMB(Event event, Vector2f pos, int num);
	
	bool RMB(Modal modal, int num);
	
	bool Highlight(Event event, Vector2f pos, int num);
	
	bool Highlight(Modal modal, int num);
};

}

#endif
