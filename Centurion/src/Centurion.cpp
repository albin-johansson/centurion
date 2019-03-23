#include "Centurion.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

namespace c = centurion;

void c::Centurion::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_InitFlags::IMG_INIT_PNG | IMG_InitFlags::IMG_INIT_JPG);
	Mix_Init(MIX_InitFlags::MIX_INIT_MP3 | MIX_InitFlags::MIX_INIT_OGG | MIX_InitFlags::MIX_INIT_FLAC);
	TTF_Init();
}

void c::Centurion::close()
{
	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}