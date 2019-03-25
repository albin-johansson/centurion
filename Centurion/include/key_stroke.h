#pragma once
#include <SDL.h>
#include "centurion.h"

class centurion::CTN_KeyStroke {

private:
	SDL_Keycode keycode;
	SDL_EventType eventType;
	centurion::CTN_Action& action;

public:
	//TODO enum for key values, enum for event types
	CTN_KeyStroke(SDL_Keycode keycode, SDL_EventType type, centurion::CTN_Action& action);

	~CTN_KeyStroke();

	void check(SDL_Event& e);
};