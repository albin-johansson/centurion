#pragma once
#include <SDL.h>
#include "centurion.h"

class centurion::KeyStroke {

private:
	SDL_Keycode keycode;
	SDL_EventType eventType;
	centurion::Action& action;

public:
	//TODO enum for key values, enum for event types
	KeyStroke(SDL_Keycode keycode, SDL_EventType type, centurion::Action& action);

	~KeyStroke();

	void Check(SDL_Event& e);
};