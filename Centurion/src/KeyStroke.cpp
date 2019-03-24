#include "KeyStroke.h"
#include "IAction.h"

using centurion::KeyStroke;
using centurion::IAction;

KeyStroke::KeyStroke(SDL_Keycode keycode, SDL_EventType eventType, IAction& action)
	: action(action)
{
	this->keycode = keycode;
	this->eventType = eventType;
}

KeyStroke::~KeyStroke() = default;

void KeyStroke::check(SDL_Event& e)
{
	if (e.type != eventType) {
		return;
	} else {
		if (e.key.keysym.sym == keycode) {
			action.execute();
		}
	}
}