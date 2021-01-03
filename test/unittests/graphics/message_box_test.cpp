#include "message_box.hpp"

#include <catch.hpp>
#include <string>

#include "colors.hpp"

TEST_CASE("message_box member show", "[.message_box]")
{
  using namespace std::string_literals;

  cen::message_box mb;

  mb.set_title("Member show"s);
  mb.set_message("Created with member show"s);

  mb.add_button(0, "Foo", cen::message_box::default_button::return_key);
  mb.add_button(1, "Bar", cen::message_box::default_button::escape_key);

  CHECK(mb.has_button(0));
  CHECK(mb.has_button(1));

  mb.show();
}

TEST_CASE("message_box static show", "[.message_box]")
{
  using namespace std::string_literals;

  cen::message_box::show("Static show"s,
                         "Created with static show"s,
                         cen::message_box::type::warning);
}

TEST_CASE("message_box(string, string)", "[message_box]")
{
  using namespace std::string_literals;

  const auto title = "foo"s;
  const auto message = "bar"s;

  const cen::message_box mb{title, message};

  CHECK(mb.get_title() == title);
  CHECK(mb.get_message() == message);
}

TEST_CASE("message_box::add_button", "[message_box]")
{
  cen::message_box mb;

  const cen::message_box::button_id id{3};

  mb.add_button(id, "Foo");

  CHECK(mb.has_button(id));
}

TEST_CASE("message_box::set_title", "[message_box]")
{
  using namespace std::string_literals;
  const auto title = "This is a title"s;

  cen::message_box mb;
  mb.set_title(title);

  CHECK(title == mb.get_title());
}

TEST_CASE("message_box::set_message", "[message_box]")
{
  using namespace std::string_literals;
  const auto message = "This is a message"s;

  cen::message_box mb;
  mb.set_message(message);

  CHECK(message == mb.get_message());
}

TEST_CASE("message_box::set_type", "[message_box]")
{
  using type = cen::message_box::type;

  cen::message_box mb;

  mb.set_type(type::information);
  CHECK(mb.get_type() == type::information);

  mb.set_type(type::warning);
  CHECK(mb.get_type() == type::warning);

  mb.set_type(type::error);
  CHECK(mb.get_type() == type::error);
}

TEST_CASE("message_box::set_button_order", "[message_box]")
{
  using order = cen::message_box::button_order;

  cen::message_box mb;

  mb.set_button_order(order::left_to_right);
  CHECK(mb.get_button_order() == order::left_to_right);

  mb.set_button_order(order::right_to_left);
  CHECK(mb.get_button_order() == order::right_to_left);
}

TEST_CASE("message_box::has_button", "[message_box]")
{
  cen::message_box mb;

  const auto id = 4;

  CHECK(!mb.has_button(id));

  mb.add_button(id, "foo");

  CHECK(mb.has_button(id));
}

TEST_CASE("message_box::get_title", "[message_box]")
{
  using namespace std::string_literals;

  cen::message_box mb;
  CHECK(mb.get_title() == "Message box"s);
}

TEST_CASE("message_box::get_message", "[message_box]")
{
  using namespace std::string_literals;

  cen::message_box mb;
  CHECK(mb.get_message() == "N/A"s);
}

TEST_CASE("message_box::get_type", "[message_box]")
{
  cen::message_box mb;
  CHECK(mb.get_type() == cen::message_box::type::information);
}

TEST_CASE("message_box::get_button_order", "[message_box]")
{
  cen::message_box mb;
  CHECK(mb.get_button_order() == cen::message_box::button_order::left_to_right);
}

TEST_CASE("message_box::color_scheme", "[message_box]")
{
  SECTION("Defaults")
  {
    using cen::colors::white;

    cen::message_box::color_scheme scheme;
    const auto sdlScheme = scheme.get();

    CHECK(sdlScheme->colors[SDL_MESSAGEBOX_COLOR_BACKGROUND] == white);
    CHECK(sdlScheme->colors[SDL_MESSAGEBOX_COLOR_TEXT] == white);
    CHECK(sdlScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] == white);
    CHECK(sdlScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] == white);
    CHECK(sdlScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] == white);
  }

  cen::message_box::color_scheme scheme;

  const auto testColor = [&](cen::message_box::color_id id,
                             const cen::color& color) {
    scheme.set_color(id, color);

    const auto sdlScheme = scheme.get();

    CHECK(sdlScheme->colors[static_cast<cen::u32>(id)] == color);
  };

  testColor(cen::message_box::color_id::background, cen::colors::pink);
  testColor(cen::message_box::color_id::text, cen::colors::salmon);
  testColor(cen::message_box::color_id::button_background, cen::colors::violet);
  testColor(cen::message_box::color_id::button_border, cen::colors::alice_blue);
  testColor(cen::message_box::color_id::button_selected, cen::colors::wheat);
}

TEST_CASE("message_box::button_flags enum values", "[message_box]")
{
  using flags = cen::message_box::default_button;

  CHECK(flags::return_key == SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT);
  CHECK(flags::escape_key == SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT);

  CHECK(SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT == flags::return_key);
  CHECK(SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT == flags::escape_key);

  CHECK(SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT != flags::escape_key);
}

TEST_CASE("message_box::color_id enum values", "[message_box]")
{
  using mb_cid = cen::message_box::color_id;

  CHECK(mb_cid::button_selected == SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED);
  CHECK(mb_cid::button_background == SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND);
  CHECK(mb_cid::button_border == SDL_MESSAGEBOX_COLOR_BUTTON_BORDER);
  CHECK(mb_cid::background == SDL_MESSAGEBOX_COLOR_BACKGROUND);

  CHECK(SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED == mb_cid::button_selected);
  CHECK(SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND == mb_cid::button_background);
  CHECK(SDL_MESSAGEBOX_COLOR_BUTTON_BORDER == mb_cid::button_border);
  CHECK(SDL_MESSAGEBOX_COLOR_BACKGROUND == mb_cid::background);

  CHECK(mb_cid::background != SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND);
  CHECK(SDL_MESSAGEBOX_COLOR_BUTTON_BORDER != mb_cid::button_selected);
}
