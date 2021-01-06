#include <gtest/gtest.h>

#include "event.hpp"

TEST(DropEvent, Defaults)
{
  cen::drop_event event;
  EXPECT_GT(event.time(), 0);
  EXPECT_EQ(cen::event_type::drop_file, event.type());
}

TEST(DropEvent, SetWillFreeFile)
{
  cen::drop_event event;

  event.set_will_free_file(true);
  EXPECT_TRUE(event.will_free_file());

  event.set_will_free_file(false);
  EXPECT_FALSE(event.will_free_file());
}

TEST(DropEvent, SetFile)
{
  cen::drop_event event;
  EXPECT_NO_THROW(event.set_file(nullptr));

  // This is the only time in the tests that a drop_event should free the file,
  // check the code coverage reports in order to see if it's freed.
  event.set_file(static_cast<char*>(SDL_malloc(sizeof(char))));
  event.set_will_free_file(true);
}

TEST(DropEvent, SetWindowId)
{
  cen::drop_event event;

  constexpr auto id = 84;
  event.set_window_id(id);

  EXPECT_EQ(id, event.window_id());
}

TEST(DropEvent, WillFreeFile)
{
  const cen::drop_event event;
  EXPECT_FALSE(event.will_free_file());
}

TEST(DropEvent, File)
{
  char file = '1';  // pretend this is some raw data

  SDL_DropEvent sdl;
  sdl.file = &file;  // shouldn't be deleted, otherwise we're in trouble

  const cen::drop_event event{sdl};

  ASSERT_TRUE(event.file());
  EXPECT_EQ(file, *event.file());
}

TEST(DropEvent, WindowId)
{
  SDL_DropEvent sdl{};
  sdl.windowID = 32;

  const cen::drop_event event{sdl};
  EXPECT_EQ(sdl.windowID, event.window_id());
}
