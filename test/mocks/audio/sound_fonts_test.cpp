#include "audio/sound_fonts.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

#include "core/integers.hpp"
#include "core_mocks.hpp"

using namespace cen::literals;

extern "C"
{
  using each_sound_font = int(SDLCALL*)(const char*, void*);

  FAKE_VALUE_FUNC(int, Mix_EachSoundFont, each_sound_font, void*)
  FAKE_VALUE_FUNC(int, Mix_SetSoundFonts, const char*)
  FAKE_VALUE_FUNC(const char*, Mix_GetSoundFonts)
}

class MixerTest : public testing::Test
{
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(Mix_SetSoundFonts)
    RESET_FAKE(Mix_GetSoundFonts)
    RESET_FAKE(Mix_EachSoundFont)
  }
};

TEST_F(MixerTest, SetSoundFonts)
{
  std::array values{0, 1};
  SET_RETURN_SEQ(Mix_SetSoundFonts, values.data(), cen::isize(values));

  ASSERT_EQ(cen::failure, cen::set_sound_fonts("foo"));
  ASSERT_EQ(cen::success, cen::set_sound_fonts("foo"));

  ASSERT_EQ(2u, Mix_SetSoundFonts_fake.call_count);
  ASSERT_STREQ("foo", Mix_SetSoundFonts_fake.arg0_val);
}

TEST_F(MixerTest, GetSoundFonts)
{
  const auto* fonts [[maybe_unused]] = cen::get_sound_fonts();
  ASSERT_EQ(1u, Mix_GetSoundFonts_fake.call_count);
}

TEST_F(MixerTest, EachSoundFont)
{
  std::array values{0, 1};
  SET_RETURN_SEQ(Mix_EachSoundFont, values.data(), cen::isize(values));

  const auto callable = [](cen::str /*font*/, void* /*data*/) noexcept { return 0; };

  ASSERT_EQ(cen::failure, cen::each_sound_font(callable));
  ASSERT_EQ(cen::success, cen::each_sound_font(callable));
  ASSERT_EQ(2u, Mix_EachSoundFont_fake.call_count);
}
