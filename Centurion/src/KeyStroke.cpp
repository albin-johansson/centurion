#include "KeyStroke.h"
#include "IAction.h"

using centurion::CTN_KeyStroke;
using centurion::CTN_Action;

CTN_KeyStroke::CTN_KeyStroke(SDL_Keycode keycode, SDL_EventType eventType, CTN_Action& action)
	: action(action)
{
	this->keycode = keycode;
	this->eventType = eventType;
}

CTN_KeyStroke::~CTN_KeyStroke() = default;

void CTN_KeyStroke::check(SDL_Event& e)
{
	if (e.type != eventType) {
		return;
	} else {
		if (e.key.keysym.sym == keycode) {
			action.execute();
		}
	}
}