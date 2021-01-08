#include "hints.hpp"

#include <fff.h>
#include <gtest/gtest.h>

// clang-format off
extern "C" {
FAKE_VOID_FUNC(SDL_ClearHints)
FAKE_VALUE_FUNC(SDL_bool, SDL_SetHintWithPriority, const char*, const char*, SDL_HintPriority)
FAKE_VALUE_FUNC(const char*, SDL_GetHint, const char*)
FAKE_VALUE_FUNC(SDL_bool, SDL_GetHintBoolean, const char*, SDL_bool)
}
// clang-format on

class HintsTest : public testing::Test
{
 protected:
  void SetUp() override
  {
    RESET_FAKE(SDL_ClearHints);
    RESET_FAKE(SDL_SetHintWithPriority);
    RESET_FAKE(SDL_GetHint);
    RESET_FAKE(SDL_GetHintBoolean);
  }
};

TEST_F(HintsTest, ClearHints)
{
  cen::clear_hints();
  EXPECT_EQ(1, SDL_ClearHints_fake.call_count);
}

TEST_F(HintsTest, SetHint)
{
  using cen::hint::render_driver;
  const auto res = cen::set_hint<render_driver>(render_driver::value::opengl);

  EXPECT_EQ(1, SDL_SetHintWithPriority_fake.call_count);
  EXPECT_STREQ(render_driver::name(), SDL_SetHintWithPriority_fake.arg0_val);
}

TEST_F(HintsTest, GetHint)
{
  {  // Boolean hint
    using cen::hint::allow_screensaver;
    const auto res = cen::get_hint<allow_screensaver>();

    EXPECT_EQ(1, SDL_GetHintBoolean_fake.call_count);
    EXPECT_STREQ(allow_screensaver::name(), SDL_GetHintBoolean_fake.arg0_val);
  }

  {  // Enum hint
    using cen::hint::render_driver;
    const auto res = cen::get_hint<render_driver>();

    EXPECT_EQ(1, SDL_GetHint_fake.call_count);
    EXPECT_STREQ(render_driver::name(), SDL_GetHint_fake.arg0_val);
  }

  {  // Integer hint
    using cen::hint::event_logging;
    const auto res = cen::get_hint<event_logging>();

    EXPECT_EQ(2, SDL_GetHint_fake.call_count);
    EXPECT_STREQ(event_logging::name(), SDL_GetHint_fake.arg0_val);
  }

  {  // Unsigned integer hint
    using cen::hint::thread_stack_size;
    const auto res = cen::get_hint<thread_stack_size>();

    EXPECT_EQ(3, SDL_GetHint_fake.call_count);
    EXPECT_STREQ(thread_stack_size::name(), SDL_GetHint_fake.arg0_val);
  }

  {  // Float hint
    using cen::hint::mouse::normal_speed_scale;
    const auto res = cen::get_hint<normal_speed_scale>();

    EXPECT_EQ(4, SDL_GetHint_fake.call_count);
    EXPECT_STREQ(normal_speed_scale::name(), SDL_GetHint_fake.arg0_val);
  }

  {  // String hint
    using cen::hint::orientations;
    const auto res = cen::get_hint<orientations>();

    EXPECT_EQ(5, SDL_GetHint_fake.call_count);
    EXPECT_STREQ(orientations::name(), SDL_GetHint_fake.arg0_val);
  }
}