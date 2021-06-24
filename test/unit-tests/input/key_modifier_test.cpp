#include "input/key_modifier.hpp"

#include <gtest/gtest.h>

#include "core/to_underlying.hpp"

TEST(KeyModifier, Values)
{
  ASSERT_EQ(cen::to_underlying(cen::key_modifier::none), KMOD_NONE);

  ASSERT_EQ(cen::to_underlying(cen::key_modifier::left_shift), KMOD_LSHIFT);
  ASSERT_EQ(cen::to_underlying(cen::key_modifier::right_shift), KMOD_RSHIFT);
  ASSERT_EQ(cen::to_underlying(cen::key_modifier::left_ctrl), KMOD_LCTRL);
  ASSERT_EQ(cen::to_underlying(cen::key_modifier::right_ctrl), KMOD_RCTRL);
  ASSERT_EQ(cen::to_underlying(cen::key_modifier::left_alt), KMOD_LALT);
  ASSERT_EQ(cen::to_underlying(cen::key_modifier::right_alt), KMOD_RALT);
  ASSERT_EQ(cen::to_underlying(cen::key_modifier::left_gui), KMOD_LGUI);
  ASSERT_EQ(cen::to_underlying(cen::key_modifier::right_gui), KMOD_RGUI);

  ASSERT_EQ(cen::to_underlying(cen::key_modifier::shift), KMOD_SHIFT);
  ASSERT_EQ(cen::to_underlying(cen::key_modifier::ctrl), KMOD_CTRL);
  ASSERT_EQ(cen::to_underlying(cen::key_modifier::alt), KMOD_ALT);
  ASSERT_EQ(cen::to_underlying(cen::key_modifier::gui), KMOD_GUI);
  ASSERT_EQ(cen::to_underlying(cen::key_modifier::num), KMOD_NUM);
  ASSERT_EQ(cen::to_underlying(cen::key_modifier::caps), KMOD_CAPS);
  ASSERT_EQ(cen::to_underlying(cen::key_modifier::mode), KMOD_MODE);

  ASSERT_EQ(cen::to_underlying(cen::key_modifier::reserved), KMOD_RESERVED);
}
