#include "input/key_modifier.hpp"

#include <gtest/gtest.h>

#include "core/to_underlying.hpp"

TEST(KeyModifier, Values)
{
  ASSERT_EQ(cen::to_underlying(cen::key_mod::none), KMOD_NONE);

  ASSERT_EQ(cen::to_underlying(cen::key_mod::left_shift), KMOD_LSHIFT);
  ASSERT_EQ(cen::to_underlying(cen::key_mod::right_shift), KMOD_RSHIFT);
  ASSERT_EQ(cen::to_underlying(cen::key_mod::left_ctrl), KMOD_LCTRL);
  ASSERT_EQ(cen::to_underlying(cen::key_mod::right_ctrl), KMOD_RCTRL);
  ASSERT_EQ(cen::to_underlying(cen::key_mod::left_alt), KMOD_LALT);
  ASSERT_EQ(cen::to_underlying(cen::key_mod::right_alt), KMOD_RALT);
  ASSERT_EQ(cen::to_underlying(cen::key_mod::left_gui), KMOD_LGUI);
  ASSERT_EQ(cen::to_underlying(cen::key_mod::right_gui), KMOD_RGUI);

  ASSERT_EQ(cen::to_underlying(cen::key_mod::shift), KMOD_SHIFT);
  ASSERT_EQ(cen::to_underlying(cen::key_mod::ctrl), KMOD_CTRL);
  ASSERT_EQ(cen::to_underlying(cen::key_mod::alt), KMOD_ALT);
  ASSERT_EQ(cen::to_underlying(cen::key_mod::gui), KMOD_GUI);
  ASSERT_EQ(cen::to_underlying(cen::key_mod::num), KMOD_NUM);
  ASSERT_EQ(cen::to_underlying(cen::key_mod::caps), KMOD_CAPS);
  ASSERT_EQ(cen::to_underlying(cen::key_mod::mode), KMOD_MODE);

  ASSERT_EQ(cen::to_underlying(cen::key_mod::reserved), KMOD_RESERVED);
}

TEST(KeyModifier, BitwiseNot)
{
  ASSERT_EQ(cen::u16(~cen::u16{KMOD_SHIFT}), cen::to_underlying(~cen::key_mod::shift));
}

TEST(KeyModifier, BitwiseOR)
{
  ASSERT_EQ(cen::key_mod::shift, cen::key_mod::shift | cen::key_mod::shift);
  ASSERT_EQ(cen::key_mod::shift, cen::key_mod::left_shift | cen::key_mod::right_shift);
  ASSERT_EQ(KMOD_LCTRL | KMOD_RALT,
            cen::to_underlying(cen::key_mod::left_ctrl | cen::key_mod::right_alt));
}

TEST(KeyModifier, BitwiseAND)
{
  ASSERT_EQ(cen::key_mod::shift, cen::key_mod::shift & cen::key_mod::shift);
  ASSERT_EQ(KMOD_LSHIFT & KMOD_RGUI,
            cen::to_underlying(cen::key_mod::left_shift & cen::key_mod::right_gui));
}
