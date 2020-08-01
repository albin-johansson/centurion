#include "font.hpp"

#include <catch.hpp>
#include <iostream>

#include "centurion_as_ctn.hpp"
#include "log.hpp"

using namespace Catch;

static constexpr auto type_writer_path = "resources/type_writer.ttf";
static constexpr auto fira_code_path = "resources/fira_code.ttf";
static constexpr auto daniel_path = "resources/daniel.ttf";

TEST_CASE("font(nn_czstring, int)", "[font]")
{
  CHECK_THROWS_AS(ctn::font("", 1), ctn::ttf_error);
  CHECK_THROWS_AS(ctn::font(daniel_path, 0), ctn::centurion_exception);
}

TEST_CASE("font(font&&)", "[font]")
{
  ctn::font font{type_writer_path, 12};
  ctn::font other{std::move(font)};

  CHECK(!font.get());
  CHECK(other.get());
}

TEST_CASE("font::operator=(font&&)", "[font]")
{
  SECTION("Self-assignment")
  {
    ctn::font font{type_writer_path, 12};
    font = std::move(font);
    CHECK(font.get());
  }

  SECTION("Normal usage")
  {
    ctn::font font{type_writer_path, 12};
    ctn::font other{daniel_path, 16};

    other = std::move(font);

    CHECK(!font.get());
    CHECK(other.get());
  }
}

TEST_CASE("font::unique", "[font]")
{
  CHECK_THROWS_AS(ctn::font::unique("", 1), ctn::ttf_error);
  CHECK_THROWS_AS(ctn::font::unique(daniel_path, 0), ctn::centurion_exception);
  CHECK(ctn::font::unique(type_writer_path, 12));
}

TEST_CASE("font::shared", "[font]")
{
  CHECK_THROWS_AS(ctn::font::shared("", 1), ctn::ttf_error);
  CHECK_THROWS_AS(ctn::font::shared(daniel_path, 0), ctn::centurion_exception);
  CHECK(ctn::font::shared(type_writer_path, 12));
}

TEST_CASE("font::reset", "[font]")
{
  ctn::font font{type_writer_path, 12};

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

TEST_CASE("font::set_bold", "[font]")
{
  ctn::font font{type_writer_path, 12};

  CHECK(!font.bold());

  font.set_bold(true);
  CHECK(font.bold());

  font.set_bold(false);
  CHECK(!font.bold());
}

TEST_CASE("font::set_italic", "[font]")
{
  ctn::font font{type_writer_path, 12};

  CHECK(!font.italic());

  font.set_italic(true);
  CHECK(font.italic());

  font.set_italic(false);
  CHECK(!font.italic());
}

TEST_CASE("font::set_underlined", "[font]")
{
  ctn::font font{type_writer_path, 12};

  CHECK(!font.underlined());

  font.set_underlined(true);
  CHECK(font.underlined());

  font.set_underlined(false);
  CHECK(!font.underlined());
}

TEST_CASE("font::set_strikethrough", "[font]")
{
  ctn::font font{type_writer_path, 12};

  CHECK(!font.strikethrough());

  font.set_strikethrough(true);
  CHECK(font.strikethrough());

  font.set_strikethrough(false);
  CHECK(!font.strikethrough());
}

TEST_CASE("font::set_outline", "[font]")
{
  ctn::font font{type_writer_path, 12};

  CHECK(!font.outlined());

  font.set_outline(2);
  CHECK(font.outline() == 2);
  CHECK(font.outlined());

  font.set_outline(0);
  CHECK(font.outline() == 0);
  CHECK(!font.outlined());
}

TEST_CASE("font::set_font_hinting", "[font]")
{
  ctn::font font{type_writer_path, 12};

  SECTION("Mono")
  {
    font.set_font_hinting(ctn::font::hint::mono);
    CHECK(font.font_hinting() == ctn::font::hint::mono);
  }

  SECTION("None")
  {
    font.set_font_hinting(ctn::font::hint::none);
    CHECK(font.font_hinting() == ctn::font::hint::none);
  }

  SECTION("Light")
  {
    font.set_font_hinting(ctn::font::hint::light);
    CHECK(font.font_hinting() == ctn::font::hint::light);
  }

  SECTION("Normal")
  {
    font.set_font_hinting(ctn::font::hint::normal);
    CHECK(font.font_hinting() == ctn::font::hint::normal);
  }
}

TEST_CASE("font::set_kerning", "[font]")
{
  ctn::font font{daniel_path, 12};

  font.set_kerning(true);
  CHECK(font.kerning());

  font.set_kerning(false);
  CHECK(!font.kerning());
}

TEST_CASE("font::size", "[font]")
{
  const auto size = 12;
  ctn::font font{type_writer_path, size};

  CHECK(size == font.size());
}

TEST_CASE("font::height", "[font]")
{
  const auto size = 16;
  ctn::font font{type_writer_path, size};
  CHECK(size ==
        font.height());  // doesn't have to be equal, but should be close
}

TEST_CASE("font::is_fixed_width", "[font]")
{
  ctn::font firaCode{fira_code_path, 12};  // Fixed width
  ctn::font daniel{daniel_path, 12};       // Not fixed width

  CHECK(firaCode.is_fixed_width());
  CHECK(!daniel.is_fixed_width());
}

TEST_CASE("font::kerning_amount", "[font]")
{
  ctn::font font{daniel_path, 36};
  font.set_kerning(true);

  const auto a = font.kerning_amount('A', 'A');
  CHECK(a == 0);

  // TODO test font with heavier kerning
}

TEST_CASE("font::glyph_metrics", "[font]")
{
  ctn::font font{daniel_path, 12};
  const auto metrics = font.get_metrics('A');
  CHECK(metrics);
}

TEST_CASE("font::is_glyph_available", "[font]")
{
  ctn::font firaCode{fira_code_path, 12};

  CHECK(firaCode.is_glyph_provided('A'));
  CHECK(firaCode.is_glyph_provided(0x003D));  // U+003D is an equal sign
}

TEST_CASE("font::family_name", "[font]")
{
  ctn::font font{type_writer_path, 12};
  CHECK_THAT(font.family_name(), Catch::Equals("Type Writer"));
}

TEST_CASE("font::style_name", "[font]")
{
  const ctn::font font{type_writer_path, 12};
  CHECK_THAT(font.style_name(), Equals("Regular"));
}

TEST_CASE("font::string_width", "[font]")
{
  const ctn::font font{type_writer_path, 12};
  CHECK(font.string_width("foo") > 0);
}

TEST_CASE("font::string_height", "[font]")
{
  const ctn::font font{type_writer_path, 12};
  CHECK(font.string_height("foo") > 0);
}

TEST_CASE("font::string_size", "[font]")
{
  const ctn::font font{type_writer_path, 12};

  const auto [width, height] = font.string_size("bar");
  CHECK(width > 0);
  CHECK(height > 0);
}

TEST_CASE("font::font_faces", "[font]")
{
  const ctn::font font{type_writer_path, 12};
  CHECK_NOTHROW(font.font_faces());
}

TEST_CASE("font::font_hinting", "[font]")
{
  const ctn::font font{type_writer_path, 12};
  CHECK(font.font_hinting() == ctn::font::hint::normal);
}

TEST_CASE("font::kerning", "[font]")
{
  const ctn::font font{daniel_path, 12};
  CHECK(font.kerning());
}

TEST_CASE("font::line_skip", "[font]")
{
  const ctn::font font{type_writer_path, 12};
  CHECK(font.line_skip() > 0);
}

TEST_CASE("font::ascent", "[font]")
{
  const ctn::font font{type_writer_path, 12};
  CHECK(font.ascent() > 0);
}

TEST_CASE("font::descent", "[font]")
{
  const ctn::font font{type_writer_path, 12};
  CHECK(font.descent() < 0);
}

TEST_CASE("font::get", "[font]")
{
  ctn::font font{type_writer_path, 12};
  CHECK(font.get());
}

TEST_CASE("font to TTF_Font*", "[font]")
{
  SECTION("Non-const")
  {
    ctn::font font{type_writer_path, 12};
    auto* sdlFont = static_cast<TTF_Font*>(font);
    CHECK(sdlFont);
  }

  SECTION("Const")
  {
    const ctn::font font{type_writer_path, 12};
    const auto* sdlFont = static_cast<const TTF_Font*>(font);
    CHECK(sdlFont);
  }
}

TEST_CASE("font to_string", "[font]")
{
  ctn::font font{type_writer_path, 12};
  ctn::log::put(ctn::to_string(font));
}

TEST_CASE("font stream operator", "[font]")
{
  ctn::font font{type_writer_path, 12};
  std::cout << "COUT: " << font << '\n';
}

TEST_CASE("ttf_version", "[font]")  // Not actually in the font header
{
  SDL_version ttf;
  SDL_TTF_VERSION(&ttf);

  const auto version = ctn::ttf_version();

  CHECK(ttf.major == version.major);
  CHECK(ttf.minor == version.minor);
  CHECK(ttf.patch == version.patch);
}
