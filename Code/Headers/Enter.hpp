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
		
	Enter(IntRect enterRect);
		
	Enter(IntRect enterRect, Image* enterImage);
		
	Enter(IntRect enterRect, String file);
		
	std::string getValue();
	
	void setRect(IntRect enterRect) override;
	
	void setValue(std::string enterStr);
		
	void draw(RenderWindow* window);

};

}

#endif
