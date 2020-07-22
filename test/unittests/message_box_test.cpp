#include "message_box.hpp"

#include <catch.hpp>
#include <string>

#include "centurion_as_ctn.hpp"
#include "colors.hpp"

using namespace ctn::messagebox;

TEST_CASE("button_data_hint enum values", "[message_box]")
{
  CHECK(button_data_hint::return_key ==
        SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT);
  CHECK(button_data_hint::escape_key ==
        SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT);

  CHECK(SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT ==
        button_data_hint::return_key);
  CHECK(SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT ==
        button_data_hint::escape_key);

  CHECK(button_data_hint::none != SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT);
  CHECK(SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT !=
        button_data_hint::escape_key);
}

TEST_CASE("color_type enum values", "[message_box]")
{
  CHECK(color_type::button_selected == SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED);
  CHECK(color_type::button_background ==
        SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND);
  CHECK(color_type::button_border == SDL_MESSAGEBOX_COLOR_BUTTON_BORDER);
  CHECK(color_type::background == SDL_MESSAGEBOX_COLOR_BACKGROUND);

  CHECK(SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED == color_type::button_selected);
  CHECK(SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND ==
        color_type::button_background);
  CHECK(SDL_MESSAGEBOX_COLOR_BUTTON_BORDER == color_type::button_border);
  CHECK(SDL_MESSAGEBOX_COLOR_BACKGROUND == color_type::background);

  CHECK(color_type::background != SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND);
  CHECK(SDL_MESSAGEBOX_COLOR_BUTTON_BORDER != color_type::button_selected);
}

TEST_CASE("color_scheme::set_color", "[message_box]")
{
  color_scheme scheme;

  scheme.set_color(color_type::background, ctn::colors::aquamarine);
  scheme.set_color(color_type::button_background, ctn::colors::azure);
  scheme.set_color(color_type::button_border, ctn::colors::tomato);
  scheme.set_color(color_type::button_selected, ctn::colors::cornsilk);

  const auto sdlScheme = scheme.convert();

  const auto index = [](color_type type) noexcept {
    return static_cast<int>(type);
  };

  CHECK(sdlScheme.colors[index(color_type::background)] ==
        ctn::colors::aquamarine);

  CHECK(sdlScheme.colors[index(color_type::button_background)] ==
        ctn::colors::azure);

  CHECK(sdlScheme.colors[index(color_type::button_border)] ==
        ctn::colors::tomato);

  CHECK(sdlScheme.colors[index(color_type::button_selected)] ==
        ctn::colors::cornsilk);
}

TEST_CASE("message_box()", "[message_box]")
{
  message_box mb;
  CHECK(!mb.get_color_scheme());
  CHECK(mb.get_type() == message_box::type::information);
  CHECK(mb.get_button_order() == message_box::button_order::left_to_right);
  CHECK_THAT(mb.title(), Catch::Equals("Centurion message box"));
  CHECK_THAT(mb.message(), Catch::Equals("N/A"));
}

TEST_CASE("message_box(czstring, czstring)", "[message_box]")
{
  SECTION("Null arguments")
  {
    message_box mb{nullptr, nullptr};
    CHECK_THAT(mb.title(), Catch::Equals("Centurion message box"));
    CHECK_THAT(mb.message(), Catch::Equals("N/A"));
  }
  SECTION("Normal arguments")
  {
    ctn::czstring title = "This is a title";
    ctn::czstring message = "This is a message";
    message_box mb{title, message};
    CHECK_THAT(mb.title(), Catch::Equals(title));
    CHECK_THAT(mb.message(), Catch::Equals(message));
  }
}

TEST_CASE("message_box::show [static]", "[.message_box]")
{
  SECTION("Checking defaults")
  {
    ctn::czstring title = nullptr;
    ctn::czstring message = nullptr;
    message_box_config config;
    message_box::show(title, message, config, nullptr);
  }
  SECTION("Actual parameters")
  {
    ctn::czstring title = "This is a title";
    ctn::czstring message =
        "This message box was created with the static show!";
    message_box_config config;
    config.type = message_box::type::warning;
    config.buttonOrder = message_box::button_order::right_to_left;
    message_box::show(title, message, config);
  }
}

TEST_CASE("message_box::show [non-static]", "[.message_box]")
{
  message_box mb;
  mb.show(nullptr);
}

TEST_CASE("message_box::add_button", "[message_box]")
{
  message_box mb;
  CHECK_NOTHROW(mb.add_button(button_data_hint::return_key, 0, nullptr));
  CHECK_NOTHROW(mb.add_button(button_data_hint::escape_key, 12, "Foo"));
}

TEST_CASE("message_box::set_title", "[message_box]")
{
  message_box mb;
  ctn::czstring title = "This is a title";

  mb.set_title(title);
  CHECK_THAT(mb.title(), Catch::Equals(title));

  mb.set_title(nullptr);
  CHECK_THAT(mb.title(), Catch::Equals(title));
}

TEST_CASE("message_box::set_message", "[message_box]")
{
  message_box mb;
  ctn::czstring msg = "Foobar";

  mb.set_message(msg);
  CHECK_THAT(mb.message(), Catch::Equals(msg));

  mb.set_message(nullptr);
  CHECK_THAT(mb.message(), Catch::Equals(msg));
}

TEST_CASE("message_box::set_type", "[message_box]")
{
  message_box mb;

  const auto error = message_box::type::error;
  mb.set_type(error);

  CHECK(mb.get_type() == error);

  const auto warn = message_box::type::warning;
  mb.set_type(warn);

  CHECK(mb.get_type() == warn);

  const auto info = message_box::type::information;
  mb.set_type(info);

  CHECK(mb.get_type() == info);
}

TEST_CASE("message_box::set_button_order", "[message_box]")
{
  message_box mb;

  const auto rightToLeft = message_box::button_order::right_to_left;
  mb.set_button_order(rightToLeft);

  CHECK(mb.get_button_order() == rightToLeft);

  const auto leftToRight = message_box::button_order::left_to_right;
  mb.set_button_order(leftToRight);

  CHECK(mb.get_button_order() == leftToRight);
}

TEST_CASE("message_box::set_color_scheme", "[message_box]")
{
  const auto colorType = color_type::background;
  message_box mb;

  color_scheme scheme;
  scheme.set_color(colorType, ctn::colors::red);

  mb.set_color_scheme(scheme);

  CHECK(mb.get_color_scheme());

  const auto sdlScheme = scheme.convert();
  CHECK(sdlScheme.colors[static_cast<int>(colorType)] == ctn::colors::red);

  mb.set_color_scheme(ctn::nothing);
  CHECK(!mb.get_color_scheme());
}

TEST_CASE("message_box::title", "[message_box]")
{
  message_box mb;
  CHECK_THAT(mb.title(), Catch::Equals("Centurion message box"));
}

TEST_CASE("message_box::message", "[message_box]")
{
  message_box mb;
  CHECK_THAT(mb.message(), Catch::Equals("N/A"));
}

TEST_CASE("message_box::color_scheme", "[message_box]")
{
  message_box mb;
  CHECK(!mb.get_color_scheme());
}

TEST_CASE("message_box::type", "[message_box]")
{
  message_box mb;
  CHECK(mb.get_type() == message_box::type::information);
}

TEST_CASE("message_box::button_order", "[message_box]")
{
  message_box mb;
  CHECK(mb.get_button_order() == message_box::button_order::left_to_right);
}