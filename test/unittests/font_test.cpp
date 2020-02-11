#include "catch.hpp"
#include <utility>
#include "font.h"
#include "centurion_exception.h"
#include "log.h"

using namespace centurion;
using namespace Catch;

static constexpr auto type_writer_path = "resources/type_writer.ttf";
static constexpr auto fira_code_path = "resources/fira_code.ttf";
static constexpr auto daniel_path = "resources/daniel.ttf";

TEST_CASE("Font(string&, int)", "[Font]") {
  CHECK_THROWS_AS(Font("", 1), CenturionException);
  CHECK_THROWS_AS(Font("", 0), std::invalid_argument);
}

TEST_CASE("Font(Font&&)", "[Font]") {
  Font font{type_writer_path, 12};
  Font other{std::move(font)};

  TTF_Font* sdlFont = font;
  CHECK(!sdlFont);
}

TEST_CASE("Font::operator=(Font&&)", "[Font]") {
  Font font{type_writer_path, 12};
  Font other{daniel_path, 16};

  font = std::move(other);

  CHECK(font.get_size() == 16);

  TTF_Font* sdlFont = other;
  CHECK(!sdlFont);
}

TEST_CASE("Font::unique", "[Font]") {
  CHECK_THROWS_AS(Font::unique("", 1), CenturionException);
  CHECK(Font::unique(type_writer_path, 12));
}

TEST_CASE("Font::shared", "[Font]") {
  CHECK_THROWS_AS(Font::shared("", 1), CenturionException);
  CHECK(Font::shared(type_writer_path, 12));
}

TEST_CASE("Font::reset", "[Font]") {
  Font font{type_writer_path, 12};

  font.set_bold(true);
  font.set_italic(true);
  font.set_underlined(true);
  font.set_strikethrough(true);

  font.reset();
  CHECK(!font.is_bold());
  CHECK(!font.is_italic());
  CHECK(!font.is_underlined());
  CHECK(!font.is_strikethrough());
}

TEST_CASE("Font::set_bold", "[Font]") {
  Font font{type_writer_path, 12};

  CHECK(!font.is_bold());

  font.set_bold(true);
  CHECK(font.is_bold());

  font.set_bold(false);
  CHECK(!font.is_bold());
}

TEST_CASE("Font::set_italic", "[Font]") {
  Font font{type_writer_path, 12};

  CHECK(!font.is_italic());

  font.set_italic(true);
  CHECK(font.is_italic());

  font.set_italic(false);
  CHECK(!font.is_italic());
}

TEST_CASE("Font::set_underlined", "[Font]") {
  Font font{type_writer_path, 12};

  CHECK(!font.is_underlined());

  font.set_underlined(true);
  CHECK(font.is_underlined());

  font.set_underlined(false);
  CHECK(!font.is_underlined());
}

TEST_CASE("Font::set_strikethrough", "[Font]") {
  Font font{type_writer_path, 12};

  CHECK(!font.is_strikethrough());

  font.set_strikethrough(true);
  CHECK(font.is_strikethrough());

  font.set_strikethrough(false);
  CHECK(!font.is_strikethrough());
}

TEST_CASE("Font::set_outlined", "[Font]") {
  Font font{type_writer_path, 12};

  CHECK(!font.is_outlined());

  font.set_outlined(true);
  CHECK(font.is_outlined());

  font.set_outlined(false);
  CHECK(!font.is_outlined());
}

TEST_CASE("Font::set_font_hinting", "[Font]") {
  Font font{type_writer_path, 12};

  SECTION("Mono") {
    font.set_font_hinting(FontHint::Mono);
    CHECK(font.get_font_hinting() == FontHint::Mono);
  }

  SECTION("None") {
    font.set_font_hinting(FontHint::None);
    CHECK(font.get_font_hinting() == FontHint::None);
  }

  SECTION("Light") {
    font.set_font_hinting(FontHint::Light);
    CHECK(font.get_font_hinting() == FontHint::Light);
  }

  SECTION("Normal") {
    font.set_font_hinting(FontHint::Normal);
    CHECK(font.get_font_hinting() == FontHint::Normal);
  }
}

TEST_CASE("Font::get_size", "[Font]") {
  const auto size = 12;
  Font font{type_writer_path, size};

  CHECK(size == font.get_size());
}

TEST_CASE("Font::get_height", "[Font]") {
  const auto size = 16;
  Font font{type_writer_path, size};
  CHECK(size == font.get_height()); // doesn't have to be equal, but should be close
}

TEST_CASE("Font::is_fixed_width", "[Font]") {
  Font fira_code{fira_code_path, 12}; // Fixed width
  Font daniel{daniel_path, 12};      // Not fixed width

  CHECK(fira_code.is_fixed_width());
  CHECK(!daniel.is_fixed_width());
}

TEST_CASE("Font::get_family_name", "[Font]") {
  Font font{type_writer_path, 12};
  CHECK(font.get_family_name() == "Type Writer");
}

#ifdef CENTURION_HAS_OPTIONAL

TEST_CASE("Font::get_style_name", "[Font]") {
  const Font font{type_writer_path, 12};
  CHECK_THAT(font.get_style_name()->c_str(), Equals("Regular"));
}

#endif

TEST_CASE("Font::get_string_width", "[Font]") {
  const Font font{type_writer_path, 12};
  CHECK(font.get_string_width("foo") > 0);
}

TEST_CASE("Font::get_string_height", "[Font]") {
  const Font font{type_writer_path, 12};
  CHECK(font.get_string_height("foo") > 0);
}

TEST_CASE("Font::get_font_faces", "[Font]") {
  const Font font{type_writer_path, 12};
  CHECK_NOTHROW(font.get_font_faces());
}

TEST_CASE("Font::get_font_hinting", "[Font]") {
  const Font font{type_writer_path, 12};
  CHECK(font.get_font_hinting() == FontHint::Normal);
}

TEST_CASE("Font::get_line_skip", "[Font]") {
  const Font font{type_writer_path, 12};
  CHECK(font.get_line_skip() > 0);
}

TEST_CASE("Font::get_ascent", "[Font]") {
  const Font font{type_writer_path, 12};
  CHECK(font.get_ascent() > 0);
}

TEST_CASE("Font::get_descent", "[Font]") {
  const Font font{type_writer_path, 12};
  CHECK(font.get_descent() < 0);
}

TEST_CASE("Font::to_string", "[Font]") {
  Font font{type_writer_path, 12};
  Log::msgf(Category::Test, "%s", font.to_string().c_str());
}

TEST_CASE("Font to TTF_Font*", "[Font]") {
  Font font{type_writer_path, 12};
  TTF_Font* sdlFont = font;
  CHECK(sdlFont);
}