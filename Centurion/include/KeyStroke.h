#pragma once
#include "Centurion.h"
#include <SDL.h>

class centurion::KeyStroke {

private:
	SDL_Keycode keycode;
	SDL_EventType eventType;

public:
	KeyStroke(SDL_Keycode keycode, SDL_EventType type); //TODO enum for key values, enum for event type

	~KeyStroke();

};