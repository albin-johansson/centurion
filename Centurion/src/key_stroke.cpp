#include "key_stroke.h"
#include "action.h"

using centurion::events::KeyStroke;
using centurion::events::Action;

KeyStroke::KeyStroke(SDL_Keycode keycode,
					 SDL_EventType eventType,
					 Action& action)
	: action(action)
{
	this->keycode = keycode;
	this->eventType = eventType;
}

KeyStroke::~KeyStroke() = default;

void KeyStroke::Check(SDL_Event& e)
{
	if (e.type != eventType) {
		return;
	} else {
		if (e.key.keysym.sym == keycode) {
			action.Execute();
		}
	}
}