#include "syswm_event.h"

#include <catch.hpp>

using namespace centurion::event;

TEST_CASE("SysWMEvent constructors", "[SysWMEvent]")
{
  CHECK_NOTHROW(SysWMEvent{});
  CHECK_NOTHROW(SysWMEvent{{}});

  SDL_SysWMEvent e;
  CHECK_NOTHROW(SysWMEvent{e});
}

TEST_CASE("SysWMEvent::message", "[SysWMEvent]")
{
  SDL_SysWMmsg msg;
  msg.subsystem = SDL_SYSWM_WINDOWS;

  SDL_SysWMEvent e;
  e.msg = &msg;

  SysWMEvent event{e};

  CHECK(event.message());
  CHECK(event.message()->subsystem == SDL_SYSWM_WINDOWS);
}