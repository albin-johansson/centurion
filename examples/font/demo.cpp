#include <centurion.hpp>

int main(int, char**)
{
  /* The font API requires the SDL_ttf extension */
  const cen::sdl sdl;
  const cen::ttf ttf;

  cen::font font{RESOURCE_DIR "daniel.ttf", 12};

  cen::log_info("The font size is %i", font.size());

  if (const char* family = font.family_name()) {
    cen::log_info("The font family is '%s'", family);
  }

  if (const char* style = font.style_name()) {
    cen::log_info("The font style is '%s'", style);
  }

  /* Font queries */
  cen::log_info("Is the font fixed width? %s", font.is_fixed_width() ? "Yes" : "No");
  cen::log_info("Font height: %i", font.height());
  cen::log_info("Font ascent: %i", font.ascent());
  cen::log_info("Font descent: %i", font.descent());

  /* Font styling */
  font.set_italic(true);
  font.set_bold(false);
  font.set_strikethrough(false);
  font.set_kerning(true);
  font.set_underlined(false);

  cen::log_info("Is the font bold? %s", font.is_bold() ? "Yes" : "No");
  cen::log_info("Is the font italic? %s", font.is_italic() ? "Yes" : "No");
  cen::log_info("Is the font strikethrough? %s", font.is_strikethrough() ? "Yes" : "No");
  cen::log_info("Is the font underlined? %s", font.is_underlined() ? "Yes" : "No");
  cen::log_info("Is kerning enabled? %s", font.has_kerning() ? "Yes" : "No");

  /* Glyph availability checks */
  const cen::unicode_t glyph = 'A';
  cen::log_info("Is the glyph '%c' provided? %s",
                glyph,
                font.is_glyph_provided(glyph) ? "Yes" : "No");

  /* Glyph metrics */
  if (const auto metrics = font.get_metrics(glyph)) {
    cen::log_info("Metrics for glyph '%c'...", glyph);
    cen::log_info("  Glyph advance: %i", metrics->advance);
    cen::log_info("  Glyph maximum x-offset: %i", metrics->max_x);
    cen::log_info("  Glyph maximum y-offset: %i", metrics->max_y);
    cen::log_info("  Glyph minimum x-offset: %i", metrics->min_x);
    cen::log_info("  Glyph minimum y-offset: %i", metrics->min_y);
  }

  /* Calculate the size of a rendered string */
  const char* str = "foobar";
  if (const auto size = font.calc_size(str)) {
    cen::log_info("The size of '%s' is (%i, %i)", str, size->width, size->height);
  }

  /* Render text to surface */
  const cen::surface surface = font.render_blended(str, cen::colors::white);
  cen::log_info("Rendered surface size: (%i, %i)", surface.width(), surface.height());

  return 0;
}