#include "message_box.hpp"

#include <catch.hpp>
#include <string>

#include "colors.hpp"

using namespace centurion;
using namespace centurion::messagebox;

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

TEST_CASE("ColorScheme::set_color", "[ColorScheme]")
{
  ColorScheme scheme;

  scheme.set_color(ColorType::Background, color::aquamarine);
  scheme.set_color(ColorType::ButtonBackground, color::azure);
  scheme.set_color(ColorType::ButtonBorder, color::tomato);
  scheme.set_color(ColorType::ButtonSelected, color::cornsilk);

  const auto sdlScheme = scheme.convert();

  const auto index = [](ColorType type) noexcept {
    return static_cast<int>(type);
  };

  CHECK(sdlScheme.colors[index(ColorType::Background)] == color::aquamarine);
  CHECK(sdlScheme.colors[index(ColorType::ButtonBackground)] == color::azure);
  CHECK(sdlScheme.colors[index(ColorType::ButtonBorder)] == color::tomato);
  CHECK(sdlScheme.colors[index(ColorType::ButtonSelected)] == color::cornsilk);
}

TEST_CASE("MessageBox()", "[MessageBox]")
{
  MessageBox mb;
  CHECK(!mb.color_scheme());
  CHECK(mb.type() == MessageBox::Type::Information);
  CHECK(mb.button_order() == MessageBox::ButtonOrder::LeftToRight);
  CHECK_THAT(mb.title(), Catch::Equals("Centurion message box"));
  CHECK_THAT(mb.message(), Catch::Equals("N/A"));
}

TEST_CASE("MessageBox(CZString, CZString)", "[MessageBox]")
{
  SECTION("Null arguments")
  {
    MessageBox mb{nullptr, nullptr};
    CHECK_THAT(mb.title(), Catch::Equals("Centurion message box"));
    CHECK_THAT(mb.message(), Catch::Equals("N/A"));
  }
  SECTION("Normal arguments")
  {
    CZString title = "This is a title";
    CZString message = "This is a message";
    MessageBox mb{title, message};
    CHECK_THAT(mb.title(), Catch::Equals(title));
    CHECK_THAT(mb.message(), Catch::Equals(message));
  }
}

#ifndef TRAVIS_TEST
TEST_CASE("MessageBox::show [static]", "[MessageBox]")
{
  SECTION("Checking defaults")
  {
    CZString title = nullptr;
    CZString message = nullptr;
    MessageBoxConfig config;
    MessageBox::show(title, message, config, nullptr);
  }
  SECTION("Actual parameters")
  {
    CZString title = "This is a title";
    CZString message = "This message box was created with the static show!";
    MessageBoxConfig config;
    config.type = MessageBox::Type::Warning;
    config.buttonOrder = MessageBox::ButtonOrder::RightToLeft;
    MessageBox::show(title, message, config);
  }
}

TEST_CASE("MessageBox::show [non-static]", "[MessageBox]")
{
  MessageBox mb;
  mb.show(nullptr);
}
#endif  // TRAVIS_TEST

TEST_CASE("MessageBox::add_button", "[MessageBox]")
{
  MessageBox mb;
  CHECK_NOTHROW(mb.add_button(ButtonDataHint::ReturnKey, 0, nullptr));
  CHECK_NOTHROW(mb.add_button(ButtonDataHint::EscapeKey, 12, "Foo"));
}

TEST_CASE("MessageBox::set_title", "[MessageBox]")
{
  MessageBox mb;
  CZString title = "This is a title";

  mb.set_title(title);
  CHECK_THAT(mb.title(), Catch::Equals(title));

  mb.set_title(nullptr);
  CHECK_THAT(mb.title(), Catch::Equals(title));
}

TEST_CASE("MessageBox::set_message", "[MessageBox]")
{
  MessageBox mb;
  CZString msg = "Foobar";

  mb.set_message(msg);
  CHECK_THAT(mb.message(), Catch::Equals(msg));

  mb.set_message(nullptr);
  CHECK_THAT(mb.message(), Catch::Equals(msg));
}

TEST_CASE("MessageBox::set_type", "[MessageBox]")
{
  MessageBox mb;

  const auto error = MessageBox::Type::Error;
  mb.set_type(error);

  CHECK(mb.type() == error);

  const auto warn = MessageBox::Type::Warning;
  mb.set_type(warn);

  CHECK(mb.type() == warn);

  const auto info = MessageBox::Type::Information;
  mb.set_type(info);

  CHECK(mb.type() == info);
}

TEST_CASE("MessageBox::set_button_order", "[MessageBox]")
{
  MessageBox mb;

  const auto rightToLeft = MessageBox::ButtonOrder::RightToLeft;
  mb.set_button_order(rightToLeft);

  CHECK(mb.button_order() == rightToLeft);

  const auto leftToRight = MessageBox::ButtonOrder::LeftToRight;
  mb.set_button_order(leftToRight);

  CHECK(mb.button_order() == leftToRight);
}

TEST_CASE("MessageBox::set_color_scheme", "[MessageBox]")
{
  const auto colorType = ColorType::Background;
  MessageBox mb;

  ColorScheme scheme;
  scheme.set_color(colorType, color::red);

  mb.set_color_scheme(scheme);

  CHECK(mb.color_scheme());

  const auto sdlScheme = scheme.convert();
  CHECK(sdlScheme.colors[static_cast<int>(colorType)] == color::red);

  mb.set_color_scheme(nothing);
  CHECK(!mb.color_scheme());
}

TEST_CASE("MessageBox::title", "[MessageBox]")
{
  MessageBox mb;
  CHECK_THAT(mb.title(), Catch::Equals("Centurion message box"));
}

TEST_CASE("MessageBox::message", "[MessageBox]")
{
  MessageBox mb;
  CHECK_THAT(mb.message(), Catch::Equals("N/A"));
}

TEST_CASE("MessageBox::color_scheme", "[MessageBox]")
{
  MessageBox mb;
  CHECK(!mb.color_scheme());
}

TEST_CASE("MessageBox::type", "[MessageBox]")
{
  MessageBox mb;
  CHECK(mb.type() == MessageBox::Type::Information);
}

TEST_CASE("MessageBox::button_order", "[MessageBox]")
{
  MessageBox mb;
  CHECK(mb.button_order() == MessageBox::ButtonOrder::LeftToRight);
}