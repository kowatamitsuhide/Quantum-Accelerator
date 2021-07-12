#include "OBSEVER.h"
std::list<OBSERVERLISTENER*> OBSERVER::listeners_ = {};

void OBSERVER::addListener(OBSERVERLISTENER* listener)
{
	listeners_.push_back(listener);
};

void OBSERVER::removeListener(OBSERVERLISTENER* listener) 
{
	listeners_.remove(listener);
};

// Õ“Ë”»’è‚µ‚½
void OBSERVER::IsCollision(std::string collsion_tag)
{
	// Õ“Ë”»’è‚µ‚½‚±‚Æ‚ðŠÏ‘ªŽÒ‚É’Ê’m 
	for (auto listener : listeners_){listener->OnCollision(collsion_tag);}
}


