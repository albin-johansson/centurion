#include <SDL.h>
#include <stdio.h>
#include "Centurion.h"
#include "Window.h"
#include "Image.h"
#include "Screen.h"

using namespace centurion;

//TODO remove main.c from the library
int main(int argc, char** argv)
{
	Centurion::init();

	std::string s = "HelloWorld";
	Window window = Window(s);
	Image* img = window.createImage("player_ph.png");

	window.setResizable(false);
	window.show();

	bool running = true;
	SDL_Event event;
	while (running) {

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EventType::SDL_QUIT) {
				running = false;
			} else if (event.type == SDL_EventType::SDL_KEYUP) {
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					running = false;
				}
			}
		}

		window.render(*img, 300, 200, 190, 300);
		window.update();
		SDL_Delay(2);
	}

	printf("Screen width: %i\n", Screen::getWidth());
	printf("Screen height: %i\n", Screen::getHeight());
	printf("Window width: %i\n", window.getWidth());
	printf("Window height: %i\n", window.getHeight());

	Image::destroy(img);
	Centurion::close();
	return 0;
}