#include "input/key_modifier.hpp"

#include <gtest/gtest.h>

#include <iostream>  // clog

#include "core/common.hpp"

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

TEST(KeyModifier, SetModifiers)
{
  const auto previous = cen::get_modifiers();

  cen::set_modifiers(cen::key_mod::left_shift | cen::key_mod::right_alt);
  ASSERT_EQ(cen::key_mod::left_shift | cen::key_mod::right_alt, cen::get_modifiers());

  cen::set_modifiers(previous);
}

TEST(KeyModifier, GetModifiers)
{
  ASSERT_EQ(SDL_GetModState(), cen::to_underlying(cen::get_modifiers()));
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

TEST(KeyModifier, ToString)
{
  {  // Invalid modifier
    ASSERT_EQ("", cen::to_string(cen::key_mod::reserved));
  }

  {  // Singles
    ASSERT_EQ("none", cen::to_string(cen::key_mod::none));
    ASSERT_EQ("left_shift", cen::to_string(cen::key_mod::left_shift));
    ASSERT_EQ("right_shift", cen::to_string(cen::key_mod::right_shift));
    ASSERT_EQ("left_ctrl", cen::to_string(cen::key_mod::left_ctrl));
    ASSERT_EQ("right_ctrl", cen::to_string(cen::key_mod::right_ctrl));
    ASSERT_EQ("left_alt", cen::to_string(cen::key_mod::left_alt));
    ASSERT_EQ("right_alt", cen::to_string(cen::key_mod::right_alt));
    ASSERT_EQ("left_gui", cen::to_string(cen::key_mod::left_gui));
    ASSERT_EQ("right_gui", cen::to_string(cen::key_mod::right_gui));
    ASSERT_EQ("num", cen::to_string(cen::key_mod::num));
    ASSERT_EQ("caps", cen::to_string(cen::key_mod::caps));
    ASSERT_EQ("mode", cen::to_string(cen::key_mod::mode));
  }

  {  // Two modifiers
    const auto mods = cen::key_mod::left_shift | cen::key_mod::caps;
    ASSERT_EQ("left_shift,caps", cen::to_string(mods));
  }

  {  // Three modifiers
    const auto mods = cen::key_mod::left_ctrl | cen::key_mod::right_alt | cen::key_mod::num;
    ASSERT_EQ("left_ctrl,right_alt,num", cen::to_string(mods));
  }

  {  // Composite enumerator
    const auto mods = cen::key_mod::alt;
    ASSERT_EQ("left_alt,right_alt", cen::to_string(mods));
  }

  {  // Everything
    const auto mods = static_cast<cen::key_mod>(0xFFFF);
    ASSERT_EQ(
        "left_shift,right_shift,left_ctrl,right_ctrl,left_alt,right_alt,left_gui,right_"
        "gui,num,caps,mode",
        cen::to_string(mods));
  }

  std::clog << "Key modifier example: " << cen::key_mod::left_shift << '\n';
}
