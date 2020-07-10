#include "font.hpp"

#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "log.hpp"

using namespace centurion;
using namespace Catch;

static constexpr auto type_writer_path = "resources/type_writer.ttf";
static constexpr auto fira_code_path = "resources/fira_code.ttf";
static constexpr auto daniel_path = "resources/daniel.ttf";

TEST_CASE("Font(CZString, int)", "[Font]")
{
  CHECK_THROWS_AS(font(nullptr, 1), centurion_exception);
  CHECK_THROWS_AS(font("", 1), centurion_exception);
  CHECK_THROWS_AS(font("", 0), centurion_exception);
}

TEST_CASE("Font(Font&&)", "[Font]")
{
  ctn::font font{type_writer_path, 12};
  ctn::font other{std::move(font)};

  CHECK(!font.get());
  CHECK(other.get());
}

TEST_CASE("Font::operator=(Font&&)", "[Font]")
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

TEST_CASE("Font::unique", "[Font]")
{
  CHECK_THROWS_AS(font::unique("", 1), centurion_exception);
  CHECK(font::unique(type_writer_path, 12));
}

TEST_CASE("Font::shared", "[Font]")
{
  CHECK_THROWS_AS(font::shared("", 1), centurion_exception);
  CHECK(font::shared(type_writer_path, 12));
}

TEST_CASE("Font::reset", "[Font]")
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

TEST_CASE("Font::set_bold", "[Font]")
{
  ctn::font font{type_writer_path, 12};

  CHECK(!font.bold());

  font.set_bold(true);
  CHECK(font.bold());

  font.set_bold(false);
  CHECK(!font.bold());
}

TEST_CASE("Font::set_italic", "[Font]")
{
  ctn::font font{type_writer_path, 12};

  CHECK(!font.italic());

  font.set_italic(true);
  CHECK(font.italic());

  font.set_italic(false);
  CHECK(!font.italic());
}

TEST_CASE("Font::set_underlined", "[Font]")
{
  ctn::font font{type_writer_path, 12};

  CHECK(!font.underlined());

  font.set_underlined(true);
  CHECK(font.underlined());

  font.set_underlined(false);
  CHECK(!font.underlined());
}

TEST_CASE("Font::set_strikethrough", "[Font]")
{
  ctn::font font{type_writer_path, 12};

  CHECK(!font.strikethrough());

  font.set_strikethrough(true);
  CHECK(font.strikethrough());

  font.set_strikethrough(false);
  CHECK(!font.strikethrough());
}

TEST_CASE("Font::set_outlined", "[Font]")
{
  ctn::font font{type_writer_path, 12};

  CHECK(!font.outlined());

  font.set_outlined(true);
  CHECK(font.outlined());

  font.set_outlined(false);
  CHECK(!font.outlined());
}

TEST_CASE("Font::set_font_hinting", "[Font]")
{
  ctn::font font{type_writer_path, 12};

  SECTION("Mono")
  {
    font.set_font_hinting(font::Hint::Mono);
    CHECK(font.font_hinting() == font::Hint::Mono);
  }

  SECTION("None")
  {
    font.set_font_hinting(font::Hint::None);
    CHECK(font.font_hinting() == font::Hint::None);
  }

  SECTION("Light")
  {
    font.set_font_hinting(font::Hint::Light);
    CHECK(font.font_hinting() == font::Hint::Light);
  }

  SECTION("Normal")
  {
    font.set_font_hinting(font::Hint::Normal);
    CHECK(font.font_hinting() == font::Hint::Normal);
  }
}

TEST_CASE("Font::set_kerning", "[Font]")
{
  ctn::font font{daniel_path, 12};

  font.set_kerning(true);
  CHECK(font.kerning());

  font.set_kerning(false);
  CHECK(!font.kerning());
}

TEST_CASE("Font::size", "[Font]")
{
  const auto size = 12;
  ctn::font font{type_writer_path, size};

  CHECK(size == font.size());
}

TEST_CASE("Font::height", "[Font]")
{
  const auto size = 16;
  ctn::font font{type_writer_path, size};
  CHECK(size ==
        font.height());  // doesn't have to be equal, but should be close
}

TEST_CASE("Font::is_fixed_width", "[Font]")
{
  ctn::font firaCode{fira_code_path, 12};  // Fixed width
  ctn::font daniel{daniel_path, 12};       // Not fixed width

  CHECK(firaCode.is_fixed_width());
  CHECK(!daniel.is_fixed_width());
}

TEST_CASE("Font::kerning_amount", "[Font]")
{
  ctn::font font{daniel_path, 36};
  font.set_kerning(true);

  const auto a = font.kerning_amount('A', 'A');
  CHECK(a == 0);

  // TODO test font with heavier kerning
}

TEST_CASE("Font::glyph_metrics", "[Font]")
{
  ctn::font font{daniel_path, 12};
  const auto metrics = font.glyph_metrics('A');
  CHECK(metrics);
}

TEST_CASE("Font::is_glyph_available", "[Font]")
{
  ctn::font firaCode{fira_code_path, 12};

  CHECK(firaCode.is_glyph_provided('A'));
  CHECK(firaCode.is_glyph_provided(0x003D));  // U+003D is an equal sign
}

TEST_CASE("Font::family_name", "[Font]")
{
  ctn::font font{type_writer_path, 12};
  CHECK_THAT(font.family_name(), Catch::Equals("Type Writer"));
}

TEST_CASE("Font::style_name", "[Font]")
{
  const ctn::font font{type_writer_path, 12};
  CHECK_THAT(font.style_name(), Equals("Regular"));
}

TEST_CASE("Font::string_width", "[Font]")
{
  const ctn::font font{type_writer_path, 12};
  CHECK(font.string_width("foo") > 0);
  CHECK(font.string_width(nullptr) == 0);
}

TEST_CASE("Font::string_height", "[Font]")
{
  const ctn::font font{type_writer_path, 12};
  CHECK(font.string_height("foo") > 0);
  CHECK(font.string_height(nullptr) == 0);
}

TEST_CASE("Font::string_size", "[Font]")
{
  const ctn::font font{type_writer_path, 12};

  SECTION("Normal string")
  {
    const auto size = font.string_size("bar");
    CHECK(size.width > 0);
    CHECK(size.height > 0);
  }

  SECTION("Null string")
  {
    const auto size = font.string_size(nullptr);
    CHECK(size.width == 0);
    CHECK(size.height == 0);
  }
}

TEST_CASE("Font::font_faces", "[Font]")
{
  const ctn::font font{type_writer_path, 12};
  CHECK_NOTHROW(font.font_faces());
}

TEST_CASE("Font::font_hinting", "[Font]")
{
  const ctn::font font{type_writer_path, 12};
  CHECK(font.font_hinting() == font::Hint::Normal);
}

TEST_CASE("Font::kerning", "[Font]")
{
  const ctn::font font{daniel_path, 12};
  CHECK(font.kerning());
}

TEST_CASE("Font::line_skip", "[Font]")
{
  const ctn::font font{type_writer_path, 12};
  CHECK(font.line_skip() > 0);
}

TEST_CASE("Font::ascent", "[Font]")
{
  const ctn::font font{type_writer_path, 12};
  CHECK(font.ascent() > 0);
}

TEST_CASE("Font::descent", "[Font]")
{
  const ctn::font font{type_writer_path, 12};
  CHECK(font.descent() < 0);
}

TEST_CASE("Font::ttf_version", "[Font]")
{
  SDL_version sdl;
  SDL_TTF_VERSION(&sdl);

  const SDL_version v = font::ttf_version();

  CHECK(sdl.major == v.major);
  CHECK(sdl.minor == v.minor);
  CHECK(sdl.patch == v.patch);
}

TEST_CASE("Font::to_string", "[Font]")
{
  ctn::font font{type_writer_path, 12};
  log::info(log::category::test, "%s", font.to_string().c_str());
}

TEST_CASE("Font::get", "[Font]")
{
  ctn::font font{type_writer_path, 12};
  CHECK(font.get());
}

TEST_CASE("Font to TTF_Font*", "[Font]")
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