#include <SDL.h>
#undef main  // SDL is unhappy without this (it wants to use its own main)

#include <fff.h>

#include <iostream>

DEFINE_FFF_GLOBALS;

FAKE_VOID_FUNC(hello)

extern "C" {
FAKE_VALUE_FUNC(SDL_Renderer*, SDL_CreateRenderer, SDL_Window*, int, Uint32)
}

int main(int argc, char* argv[])
{
  SDL_CreateRenderer(nullptr, 0, 0);

  std::cout << "Called SDL_CreateRenderer "
            << SDL_CreateRenderer_fake.call_count << " times\n";

  return 0;
}