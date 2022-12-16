#ifndef ENTER_HPP
#define ENTER_HPP

#include "Trigger.hpp"
#include "Title.hpp"

#ifndef GUIC_BASE_ENTER_INTERVAL
#define GUIC_BASE_ENTER_INTERVAL 5
#endif

namespace guic

{

class DLLIMPORT Enter : public Trigger
{
private:
	
	std::string str;
	
	int counter;
	bool shift;
	
	Vector2f leftpos;
	Vector2f defpos;
	Title title;
	
	void control(Modal modal) override;
	
protected:

public:
	
	bool isEditMode;
		
	Enter();
		
	Enter(IntRect Rect);
		
	Enter(IntRect Rect, Image* Image);
		
	Enter(IntRect Rect, String File);
		
	std::string getValue();
	
	void setRect(IntRect Rect) override;
	
	void setValue(std::string Str);
		
	void draw(RenderWindow* window);

};

}

#endif
