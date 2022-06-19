#include <gtest/gtest.h>

#include "centurion/event.hpp"

#if SDL_VERSION_ATLEAST(2, 0, 22)

TEST(TextEditingExtEvent, Defaults)
{
  cen::text_editing_ext_event event;
  ASSERT_EQ(cen::event_type::text_editing_ext, event.type());
}

TEST(TextEditingEvent, SetStart)
{
  cen::text_editing_event event;

  event.set_start(42);
  ASSERT_EQ(42, event.start());
}

TEST(TextEditingEvent, SetLength)
{
  cen::text_editing_event event;

  event.set_length(18);
  ASSERT_EQ(18, event.length());
}

TEST(TextEditingEvent, SetWindowId)
{
  cen::text_editing_event event;

  const Uint32 id = 2;
  event.set_window_id(id);

  ASSERT_EQ(id, event.window_id());
}

TEST(TextEditingExtEvent, AsSDLEvent)
{
  const cen::text_editing_ext_event event;
  const auto sdl = cen::as_sdl_event(event);

  ASSERT_EQ(sdl.edit.type, cen::to_underlying(event.type()));
  ASSERT_EQ(sdl.edit.timestamp, event.timestamp().count());
}

#endif // SDL_VERSION_ATLEAST(2, 0, 22)
