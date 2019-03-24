#pragma once
#include "Centurion.h"
#include <SDL.h>

class centurion::KeyStroke {

private:
	SDL_Keycode keycode;
	SDL_EventType eventType;
	centurion::IAction& action;

public:
	//TODO enum for key values, enum for event types
	KeyStroke(SDL_Keycode keycode, SDL_EventType type, centurion::IAction& action);

	~KeyStroke();

	void check(SDL_Event& e);
};