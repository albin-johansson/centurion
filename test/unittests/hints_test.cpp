#include "hints.h"

#include <catch.hpp>

using namespace centurion::hint;

TEST_CASE("set_hint", "[Hints]")
{
  const auto prev = get_hint<RenderDriver>();

  set_hint<RenderDriver>(OpenGL);
  CHECK(get_hint<RenderDriver>() == OpenGL);

//  set_hint<RenderDriver, HintPrio::Override>(OpenGL);
//  set_hint<NoSignalHandlers>(true);
//
//  SDL_SetHintWithPriority(SDL_HINT_RENDER_DRIVER, "opengl", SDL_HINT_OVERRIDE);
//  SDL_SetHint(SDL_HINT_NO_SIGNAL_HANDLERS, "1");
//
//  set_hint<NoSignalHandlers>(false);
//
//  const auto renderDriver = get_hint<RenderDriver>();
//  if (renderDriver == OpenGL) {
//    // do something
//  }
//
//  const auto noSignalHandles = get_hint<NoSignalHandlers>();
//  if (noSignalHandles) {
//  }

  set_hint<RenderDriver, HintPrio::Default>(prev);
}