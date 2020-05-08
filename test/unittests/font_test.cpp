#include "font.h"

#include <catch.hpp>
#include <utility>

#include "centurion_exception.h"
#include "log.h"

using namespace centurion;
using namespace Catch;

static constexpr auto type_writer_path = "resources/type_writer.ttf";
static constexpr auto fira_code_path = "resources/fira_code.ttf";
static constexpr auto daniel_path = "resources/daniel.ttf";

TEST_CASE("Font(string&, int)", "[Font]")
{
  CHECK_THROWS_AS(Font("", 1), CenturionException);
  CHECK_THROWS_AS(Font("", 0), CenturionException);
}

TEST_CASE("Font(Font&&)", "[Font]")
{
  Font font{type_writer_path, 12};
  Font other{std::move(font)};

  TTF_Font* sdlFont = font;
  CHECK(!sdlFont);
}

TEST_CASE("Font::operator=(Font&&)", "[Font]")
{
  Font font{type_writer_path, 12};
  Font other{daniel_path, 16};

  font = std::move(other);

  CHECK(font.size() == 16);

  TTF_Font* sdlFont = other;
  CHECK(!sdlFont);
}

TEST_CASE("Font::unique", "[Font]")
{
  CHECK_THROWS_AS(Font::unique("", 1), CenturionException);
  CHECK(Font::unique(type_writer_path, 12));
}

TEST_CASE("Font::shared", "[Font]")
{
  CHECK_THROWS_AS(Font::shared("", 1), CenturionException);
  CHECK(Font::shared(type_writer_path, 12));
}

TEST_CASE("Font::reset", "[Font]")
{
  Font font{type_writer_path, 12};

  font.set_bold(true);
  font.set_italic(true);
  font.set_underlined(true);
  font.set_strikethrough(true);

  font.reset();
  CHECK(!font.bold());
  CHECK(!font.italic());
  CHECK(!font.underlined());
  CHECK(!font.strikethrough());
}

TEST_CASE("Font::set_bold", "[Font]")
{
  Font font{type_writer_path, 12};

  CHECK(!font.bold());

  font.set_bold(true);
  CHECK(font.bold());

  font.set_bold(false);
  CHECK(!font.bold());
}

TEST_CASE("Font::set_italic", "[Font]")
{
  Font font{type_writer_path, 12};

  CHECK(!font.italic());

  font.set_italic(true);
  CHECK(font.italic());

  font.set_italic(false);
  CHECK(!font.italic());
}

TEST_CASE("Font::set_underlined", "[Font]")
{
  Font font{type_writer_path, 12};

  CHECK(!font.underlined());

  font.set_underlined(true);
  CHECK(font.underlined());

  font.set_underlined(false);
  CHECK(!font.underlined());
}

TEST_CASE("Font::set_strikethrough", "[Font]")
{
  Font font{type_writer_path, 12};

  CHECK(!font.strikethrough());

  font.set_strikethrough(true);
  CHECK(font.strikethrough());

  font.set_strikethrough(false);
  CHECK(!font.strikethrough());
}

TEST_CASE("Font::set_outlined", "[Font]")
{
  Font font{type_writer_path, 12};

  CHECK(!font.outlined());

  font.set_outlined(true);
  CHECK(font.outlined());

  font.set_outlined(false);
  CHECK(!font.outlined());
}

TEST_CASE("Font::set_font_hinting", "[Font]")
{
  Font font{type_writer_path, 12};

  SECTION("Mono")
  {
    font.set_font_hinting(FontHint::Mono);
    CHECK(font.font_hinting() == FontHint::Mono);
  }

  SECTION("None")
  {
    font.set_font_hinting(FontHint::None);
    CHECK(font.font_hinting() == FontHint::None);
  }

  SECTION("Light")
  {
    font.set_font_hinting(FontHint::Light);
    CHECK(font.font_hinting() == FontHint::Light);
  }

  SECTION("Normal")
  {
    font.set_font_hinting(FontHint::Normal);
    CHECK(font.font_hinting() == FontHint::Normal);
  }
}

TEST_CASE("Font::size", "[Font]")
{
  const auto size = 12;
  Font font{type_writer_path, size};

  CHECK(size == font.size());
}

TEST_CASE("Font::height", "[Font]")
{
  const auto size = 16;
  Font font{type_writer_path, size};
  CHECK(size ==
        font.height());  // doesn't have to be equal, but should be close
}

TEST_CASE("Font::is_fixed_width", "[Font]")
{
  Font fira_code{fira_code_path, 12};  // Fixed width
  Font daniel{daniel_path, 12};        // Not fixed width

  CHECK(fira_code.is_fixed_width());
  CHECK(!daniel.is_fixed_width());
}

TEST_CASE("Font::family_name", "[Font]")
{
  Font font{type_writer_path, 12};
  CHECK(font.family_name() == "Type Writer");
}

TEST_CASE("Font::style_name", "[Font]")
{
  const Font font{type_writer_path, 12};
  CHECK_THAT(font.style_name()->c_str(), Equals("Regular"));
}

TEST_CASE("Font::string_width", "[Font]")
{
  const Font font{type_writer_path, 12};
  CHECK(font.string_width("foo") > 0);
}

TEST_CASE("Font::string_height", "[Font]")
{
  const Font font{type_writer_path, 12};
  CHECK(font.string_height("foo") > 0);
}

TEST_CASE("Font::font_faces", "[Font]")
{
  const Font font{type_writer_path, 12};
  CHECK_NOTHROW(font.font_faces());
}

TEST_CASE("Font::font_hinting", "[Font]")
{
  const Font font{type_writer_path, 12};
  CHECK(font.font_hinting() == FontHint::Normal);
}

TEST_CASE("Font::line_skip", "[Font]")
{
  const Font font{type_writer_path, 12};
  CHECK(font.line_skip() > 0);
}

TEST_CASE("Font::ascent", "[Font]")
{
  const Font font{type_writer_path, 12};
  CHECK(font.ascent() > 0);
}

TEST_CASE("Font::descent", "[Font]")
{
  const Font font{type_writer_path, 12};
  CHECK(font.descent() < 0);
}

TEST_CASE("Font::to_string", "[Font]")
{
  Font font{type_writer_path, 12};
  Log::msgf(Category::Test, "%s", font.to_string().c_str());
}

TEST_CASE("Font to TTF_Font*", "[Font]")
{
  Font font{type_writer_path, 12};
  TTF_Font* sdlFont = font;
  CHECK(sdlFont);
}