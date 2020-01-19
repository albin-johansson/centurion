#include "catch.hpp"
#include "message_box.h"

using namespace centurion::messagebox;

TEST_CASE("MessageBox::set_type", "[MessageBox]") {
  MessageBox mb;
  CHECK(MessageBoxID::Info == mb.get_type());

  const auto type = MessageBoxID::Error;
  mb.set_type(type);

  CHECK(type == mb.get_type());
}

TEST_CASE("MessageBoxID enum values", "[MessageBox]") {
  CHECK(MessageBoxID::Info == SDL_MESSAGEBOX_INFORMATION);
  CHECK(MessageBoxID::Error == SDL_MESSAGEBOX_ERROR);
  CHECK(MessageBoxID::Warning == SDL_MESSAGEBOX_WARNING);

  CHECK(SDL_MESSAGEBOX_INFORMATION == MessageBoxID::Info);
  CHECK(SDL_MESSAGEBOX_ERROR == MessageBoxID::Error);
  CHECK(SDL_MESSAGEBOX_WARNING == MessageBoxID::Warning);
}

TEST_CASE("ButtonData enum values", "[MessageBox]") {
  CHECK(ButtonData::ReturnKey == SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT);
  CHECK(ButtonData::EscapeKey == SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT);

  CHECK(SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT == ButtonData::ReturnKey);
  CHECK(SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT == ButtonData::EscapeKey);
}

TEST_CASE("ColorSchemeType enum values", "[MessageBox]") {
  CHECK(ColorSchemeType::ButtonSelected == SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED);
  CHECK(ColorSchemeType::ButtonBackground == SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND);
  CHECK(ColorSchemeType::ButtonBorder == SDL_MESSAGEBOX_COLOR_BUTTON_BORDER);
  CHECK(ColorSchemeType::Background == SDL_MESSAGEBOX_COLOR_BACKGROUND);

  CHECK(SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED == ColorSchemeType::ButtonSelected);
  CHECK(SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND == ColorSchemeType::ButtonBackground);
  CHECK(SDL_MESSAGEBOX_COLOR_BUTTON_BORDER == ColorSchemeType::ButtonBorder);
  CHECK(SDL_MESSAGEBOX_COLOR_BACKGROUND == ColorSchemeType::Background);
}