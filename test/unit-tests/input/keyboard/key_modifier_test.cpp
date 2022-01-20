#include <gtest/gtest.h>

#include <iostream>  // clog

#include "common.hpp"
#include "keyboard.hpp"

TEST(KeyModifier, Values)
{
  ASSERT_EQ(cen::to_underlying(cen::KeyMod::None), KMOD_NONE);

  ASSERT_EQ(cen::to_underlying(cen::KeyMod::LShift), KMOD_LSHIFT);
  ASSERT_EQ(cen::to_underlying(cen::KeyMod::RShift), KMOD_RSHIFT);
  ASSERT_EQ(cen::to_underlying(cen::KeyMod::LCtrl), KMOD_LCTRL);
  ASSERT_EQ(cen::to_underlying(cen::KeyMod::RCtrl), KMOD_RCTRL);
  ASSERT_EQ(cen::to_underlying(cen::KeyMod::LAlt), KMOD_LALT);
  ASSERT_EQ(cen::to_underlying(cen::KeyMod::RAlt), KMOD_RALT);
  ASSERT_EQ(cen::to_underlying(cen::KeyMod::LGui), KMOD_LGUI);
  ASSERT_EQ(cen::to_underlying(cen::KeyMod::RGui), KMOD_RGUI);

  ASSERT_EQ(cen::to_underlying(cen::KeyMod::Shift), KMOD_SHIFT);
  ASSERT_EQ(cen::to_underlying(cen::KeyMod::Ctrl), KMOD_CTRL);
  ASSERT_EQ(cen::to_underlying(cen::KeyMod::Alt), KMOD_ALT);
  ASSERT_EQ(cen::to_underlying(cen::KeyMod::Gui), KMOD_GUI);
  ASSERT_EQ(cen::to_underlying(cen::KeyMod::Num), KMOD_NUM);
  ASSERT_EQ(cen::to_underlying(cen::KeyMod::Caps), KMOD_CAPS);
  ASSERT_EQ(cen::to_underlying(cen::KeyMod::Mode), KMOD_MODE);
}

TEST(KeyModifier, SetModifiers)
{
  const auto previous = cen::GetModifiers();

  cen::SetModifiers(cen::KeyMod::LShift | cen::KeyMod::RAlt);
  ASSERT_EQ(cen::KeyMod::LShift | cen::KeyMod::RAlt, cen::GetModifiers());

  cen::SetModifiers(previous);
}

TEST(KeyModifier, GetModifiers)
{
  ASSERT_EQ(SDL_GetModState(), cen::to_underlying(cen::GetModifiers()));
}

TEST(KeyModifier, BitwiseNot)
{
  ASSERT_EQ(Uint16(~Uint16{KMOD_SHIFT}), cen::to_underlying(~cen::KeyMod::Shift));
}

TEST(KeyModifier, BitwiseOR)
{
  ASSERT_EQ(cen::KeyMod::Shift, cen::KeyMod::Shift | cen::KeyMod::Shift);
  ASSERT_EQ(cen::KeyMod::Shift, cen::KeyMod::LShift | cen::KeyMod::RShift);
  ASSERT_EQ(KMOD_LCTRL | KMOD_RALT,
            cen::to_underlying(cen::KeyMod::LCtrl | cen::KeyMod::RAlt));
}

TEST(KeyModifier, BitwiseAND)
{
  ASSERT_EQ(cen::KeyMod::Shift, cen::KeyMod::Shift & cen::KeyMod::Shift);
  ASSERT_EQ(KMOD_LSHIFT & KMOD_RGUI,
            cen::to_underlying(cen::KeyMod::LShift & cen::KeyMod::RGui));
}

TEST(KeyModifier, ToString)
{
  {  // Singles
    ASSERT_EQ("None", cen::ToString(cen::KeyMod::None));
    ASSERT_EQ("LShift", cen::ToString(cen::KeyMod::LShift));
    ASSERT_EQ("RShift", cen::ToString(cen::KeyMod::RShift));
    ASSERT_EQ("LCtrl", cen::ToString(cen::KeyMod::LCtrl));
    ASSERT_EQ("RCtrl", cen::ToString(cen::KeyMod::RCtrl));
    ASSERT_EQ("LAlt", cen::ToString(cen::KeyMod::LAlt));
    ASSERT_EQ("RAlt", cen::ToString(cen::KeyMod::RAlt));
    ASSERT_EQ("LGui", cen::ToString(cen::KeyMod::LGui));
    ASSERT_EQ("RGui", cen::ToString(cen::KeyMod::RGui));
    ASSERT_EQ("Num", cen::ToString(cen::KeyMod::Num));
    ASSERT_EQ("Caps", cen::ToString(cen::KeyMod::Caps));
    ASSERT_EQ("Mode", cen::ToString(cen::KeyMod::Mode));
  }

  {  // Two modifiers
    const auto mods = cen::KeyMod::LShift | cen::KeyMod::Caps;
    ASSERT_EQ("LShift,Caps", cen::ToString(mods));
  }

  {  // Three modifiers
    const auto mods = cen::KeyMod::LCtrl | cen::KeyMod::RAlt | cen::KeyMod::Num;
    ASSERT_EQ("LCtrl,RAlt,Num", cen::ToString(mods));
  }

  {  // Composite enumerator
    const auto mods = cen::KeyMod::Alt;
    ASSERT_EQ("LAlt,RAlt", cen::ToString(mods));
  }

  {  // Everything
    const auto mods = static_cast<cen::KeyMod>(0xFFFF);
    ASSERT_EQ("LShift,RShift,LCtrl,RCtrl,LAlt,RAlt,LGui,RGui,Num,Caps,Mode",
              cen::ToString(mods));
  }

  std::clog << "Key modifier example: " << cen::KeyMod::LShift << '\n';
}
