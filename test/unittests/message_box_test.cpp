#include "message_box.h"

#include <catch.hpp>
#include <cstdint>
#include <string>

#include "colors.h"

using namespace centurion;
using namespace centurion::messagebox;
using namespace centurion::video;

TEST_CASE("MessageBoxID enum values", "[MessageBox]")
{
  CHECK(MessageBoxID::Info == SDL_MESSAGEBOX_INFORMATION);
  CHECK(MessageBoxID::Error == SDL_MESSAGEBOX_ERROR);
  CHECK(MessageBoxID::Warning == SDL_MESSAGEBOX_WARNING);

  CHECK(SDL_MESSAGEBOX_INFORMATION == MessageBoxID::Info);
  CHECK(SDL_MESSAGEBOX_ERROR == MessageBoxID::Error);
  CHECK(SDL_MESSAGEBOX_WARNING == MessageBoxID::Warning);

  CHECK(MessageBoxID::Info != SDL_MESSAGEBOX_ERROR);
  CHECK(SDL_MESSAGEBOX_WARNING != MessageBoxID::Error);
}

TEST_CASE("ButtonDataHint enum values", "[MessageBox]")
{
  CHECK(ButtonDataHint::ReturnKey == SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT);
  CHECK(ButtonDataHint::EscapeKey == SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT);

  CHECK(SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT == ButtonDataHint::ReturnKey);
  CHECK(SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT == ButtonDataHint::EscapeKey);

  CHECK(ButtonDataHint::None != SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT);
  CHECK(SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT != ButtonDataHint::EscapeKey);
}

TEST_CASE("ColorType enum values", "[MessageBox]")
{
  CHECK(ColorType::ButtonSelected == SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED);
  CHECK(ColorType::ButtonBackground == SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND);
  CHECK(ColorType::ButtonBorder == SDL_MESSAGEBOX_COLOR_BUTTON_BORDER);
  CHECK(ColorType::Background == SDL_MESSAGEBOX_COLOR_BACKGROUND);

  CHECK(SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED == ColorType::ButtonSelected);
  CHECK(SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND == ColorType::ButtonBackground);
  CHECK(SDL_MESSAGEBOX_COLOR_BUTTON_BORDER == ColorType::ButtonBorder);
  CHECK(SDL_MESSAGEBOX_COLOR_BACKGROUND == ColorType::Background);

  CHECK(ColorType::Background != SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND);
  CHECK(SDL_MESSAGEBOX_COLOR_BUTTON_BORDER != ColorType::ButtonSelected);
}

TEST_CASE("ButtonData general test", "[MessageBox]")
{
  const auto hint = ButtonDataHint::ReturnKey;
  const auto id = 7;
  const std::string text{"foo"};

  const ButtonData buttonData{hint, id, text};
  const SDL_MessageBoxButtonData data = buttonData;

  CHECK(id == data.buttonid);
  CHECK(static_cast<Uint32>(hint) == data.flags);
  CHECK_THAT(text, Catch::Equals(data.text));
}

TEST_CASE("ColorScheme general test", "[MessageBox]")
{
  ColorScheme scheme;

  scheme.set_color(ColorType::Background, video::aquamarine);
  scheme.set_color(ColorType::ButtonBackground, video::azure);
  scheme.set_color(ColorType::ButtonBorder, video::tomato);
  scheme.set_color(ColorType::ButtonSelected, video::cornsilk);

  const auto sdlScheme = static_cast<SDL_MessageBoxColorScheme>(scheme);

  const auto index = [](ColorType type) noexcept {
    return static_cast<int>(type);
  };

  CHECK(sdlScheme.colors[index(ColorType::Background)] == aquamarine);
  CHECK(sdlScheme.colors[index(ColorType::ButtonBackground)] == azure);
  CHECK(sdlScheme.colors[index(ColorType::ButtonBorder)] == tomato);
  CHECK(sdlScheme.colors[index(ColorType::ButtonSelected)] == cornsilk);

  CHECK(&scheme.get());
}

TEST_CASE("MessageBox(const char*)", "[MessageBox]")
{
  CHECK_NOTHROW(MessageBox{nullptr});
  CHECK_NOTHROW(MessageBox{"foo"});
}

TEST_CASE("MessageBox::set_type", "[MessageBox]")
{
  MessageBox mb;
  CHECK(MessageBoxID::Info == mb.get_type());

  const auto type = MessageBoxID::Error;
  mb.set_type(type);

  CHECK(type == mb.get_type());
}

TEST_CASE("MessageBox::set_color_scheme", "[MessageBox]")
{
  MessageBox mb;
  CHECK_NOTHROW(mb.set_color_scheme(tl::nullopt));
}

TEST_CASE("MessageBox::set_title", "[MessageBox]")
{
  MessageBox mb;
  CHECK_NOTHROW(mb.set_title(nullptr));
  CHECK_NOTHROW(mb.set_title("foo"));
}

TEST_CASE("MessageBox::set_message", "[MessageBox]")
{
  MessageBox mb;
  CHECK_NOTHROW(mb.set_message(nullptr));
  CHECK_NOTHROW(mb.set_message("foo"));
}