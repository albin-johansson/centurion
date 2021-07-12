#include "input/key_modifier.hpp"

#include <gtest/gtest.h>

#include "core/to_underlying.hpp"

TEST(KeyModifier, Values)
{
  ASSERT_EQ(cen::to_underlying(cen::keymod::none), KMOD_NONE);

  ASSERT_EQ(cen::to_underlying(cen::keymod::left_shift), KMOD_LSHIFT);
  ASSERT_EQ(cen::to_underlying(cen::keymod::right_shift), KMOD_RSHIFT);
  ASSERT_EQ(cen::to_underlying(cen::keymod::left_ctrl), KMOD_LCTRL);
  ASSERT_EQ(cen::to_underlying(cen::keymod::right_ctrl), KMOD_RCTRL);
  ASSERT_EQ(cen::to_underlying(cen::keymod::left_alt), KMOD_LALT);
  ASSERT_EQ(cen::to_underlying(cen::keymod::right_alt), KMOD_RALT);
  ASSERT_EQ(cen::to_underlying(cen::keymod::left_gui), KMOD_LGUI);
  ASSERT_EQ(cen::to_underlying(cen::keymod::right_gui), KMOD_RGUI);

  ASSERT_EQ(cen::to_underlying(cen::keymod::shift), KMOD_SHIFT);
  ASSERT_EQ(cen::to_underlying(cen::keymod::ctrl), KMOD_CTRL);
  ASSERT_EQ(cen::to_underlying(cen::keymod::alt), KMOD_ALT);
  ASSERT_EQ(cen::to_underlying(cen::keymod::gui), KMOD_GUI);
  ASSERT_EQ(cen::to_underlying(cen::keymod::num), KMOD_NUM);
  ASSERT_EQ(cen::to_underlying(cen::keymod::caps), KMOD_CAPS);
  ASSERT_EQ(cen::to_underlying(cen::keymod::mode), KMOD_MODE);

  ASSERT_EQ(cen::to_underlying(cen::keymod::reserved), KMOD_RESERVED);
}

TEST(KeyModifier, BitwiseNot)
{
  ASSERT_EQ(cen::u16(~cen::u16{KMOD_SHIFT}), cen::to_underlying(~cen::keymod::shift));
}

TEST(KeyModifier, BitwiseOR)
{
  ASSERT_EQ(cen::keymod::shift, cen::keymod::shift | cen::keymod::shift);
  ASSERT_EQ(cen::keymod::shift, cen::keymod::left_shift | cen::keymod::right_shift);
  ASSERT_EQ(KMOD_LCTRL | KMOD_RALT,
            cen::to_underlying(cen::keymod::left_ctrl | cen::keymod::right_alt));
}

TEST(KeyModifier, BitwiseAND)
{
  ASSERT_EQ(cen::keymod::shift, cen::keymod::shift & cen::keymod::shift);
  ASSERT_EQ(KMOD_LSHIFT & KMOD_RGUI,
            cen::to_underlying(cen::keymod::left_shift & cen::keymod::right_gui));
}
