#include "KeyStroke.h"

using centurion::KeyStroke;

KeyStroke::KeyStroke(SDL_Keycode keycode, SDL_EventType eventType)
{
	this->keycode = keycode;
	this->eventType = eventType;
}

KeyStroke::~KeyStroke()
{

}