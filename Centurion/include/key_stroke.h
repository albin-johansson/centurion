#pragma once
#include "centurion.h"
#include <SDL_events.h>

class centurion::events::KeyStroke {

private:
	SDL_Keycode keycode;
	SDL_EventType eventType;
	centurion::events::Action& action;

public:
	//TODO enum for key values, enum for event types
	KeyStroke(SDL_Keycode keycode, SDL_EventType type, centurion::events::Action& action);

	~KeyStroke();

	void Check(SDL_Event& e);
};