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
  CHECK(ButtonDataHint::ReturnKey == SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT);
  CHECK(ButtonDataHint::EscapeKey == SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT);

  CHECK(SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT == ButtonDataHint::ReturnKey);
  CHECK(SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT == ButtonDataHint::EscapeKey);
}

TEST_CASE("ColorSchemeType enum values", "[MessageBox]") {
  CHECK(ColorType::ButtonSelected == SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED);
  CHECK(ColorType::ButtonBackground == SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND);
  CHECK(ColorType::ButtonBorder == SDL_MESSAGEBOX_COLOR_BUTTON_BORDER);
  CHECK(ColorType::Background == SDL_MESSAGEBOX_COLOR_BACKGROUND);

  CHECK(SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED == ColorType::ButtonSelected);
  CHECK(SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND == ColorType::ButtonBackground);
  CHECK(SDL_MESSAGEBOX_COLOR_BUTTON_BORDER == ColorType::ButtonBorder);
  CHECK(SDL_MESSAGEBOX_COLOR_BACKGROUND == ColorType::Background);
}