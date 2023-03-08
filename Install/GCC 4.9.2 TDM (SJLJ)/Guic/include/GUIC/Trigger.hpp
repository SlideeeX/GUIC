#ifndef TRIGGER_HPP
#define TRIGGER_HPP

#include "Interface.hpp"

namespace guic

{

using namespace sf;

class DLLIMPORT Trigger : public Interface

{

private:

protected:

public:

	Trigger();
	
	Trigger(IntRect rect);
	
	Trigger(IntRect rect, String file);
			
	Trigger(IntRect rect, Image* image);
			
	bool LMB(Event event, Vector2f pos);
	
	bool LMB(Modal modal);
	
	bool RMB(Event event, Vector2f pos);
	
	bool RMB(Modal modal);
	
	bool Highlight(Event event, Vector2f pos);
	
	bool Highlight(Modal modal);

};

};

#endif
