#pragma once
#include <SDL_pixels.h>
#include <SDL_stdinc.h>
#include <memory>

namespace centurion {
namespace visuals {

class Color;
using Color_sptr = std::shared_ptr<Color>;
using Color_uptr = std::unique_ptr<Color>;
using Color_wptr = std::weak_ptr<Color>;

/**
\brief The Color class simply represents a color.
\since 1.0.0
*/
class Color {
 private:
  SDL_Color color = {0, 0, 0, 0};

 public:
  /**
  \brief The highest possible value for the red, green, blue and alpha
  components.
  \since 1.0.0
  */
  const static Uint8 MAX_VAL = 255;

  /**
  \brief The lowest possible value for the red, green, blue and alpha
  components.
  \since 1.0.0
  */
  const static Uint8 MIN_VAL = 0;

  /**
  \brief A constant that represents the color red.
  \since 1.0.0
  */
  const static Color RED;

  /**
  \brief A constant that represents the color green.
  \since 1.0.0
  */
  const static Color GREEN;

  /**
  \brief A constant that represents the color blue.
  \since 1.0.0
  */
  const static Color BLUE;

  /**
  \brief A constant that represents the color white.
  \since 1.0.0
  */
  const static Color WHITE;

  /**
  \brief A constant that represents the color black.
  \since 1.0.0
  */
  const static Color BLACK;

  /**
  \brief A constant that represents the color gray.
  \since 1.0.0
  */
  const static Color GRAY;

  /**
  \param r - the red component of the color in the range [MIN_VAL, MAX_VAL].
  \param g - the green component of the color in the range [MIN_VAL, MAX_VAL].
  \param b - the blue component of the color in the range [MIN_VAL, MAX_VAL].
  \param a - the alpha component of the color in the range [MIN_VAL, MAX_VAL].
  */
  Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

  /**
  \param r - the red component of the color in the range [MIN_VAL, MAX_VAL].
  \param g - the green component of the color in the range [MIN_VAL, MAX_VAL].
  \param b - the blue component of the color in the range [MIN_VAL, MAX_VAL].
  \since 2.0.0
  */
  Color(Uint8 r, Uint8 g, Uint8 b);

  Color();

  ~Color();

  /**
  \brief Returns the red component of this color.
  \since 1.0.0
  */
  inline Uint8 GetRed() const noexcept { return color.r; }

  /**
  \brief Returns the green component of this color.
  \since 1.0.0
  */
  inline Uint8 GetGreen() const noexcept { return color.g; }

  /**
  \brief Returns the blue component of this color.
  \since 1.0.0
  */
  inline Uint8 GetBlue() const noexcept { return color.b; }

  /**
  \brief Returns the alpha component of this color.
  \since 1.0.0
  */
  inline Uint8 GetAlpha() const noexcept { return color.a; }

  /**
  \brief Returns an SDL_Color instance that represents this Color.
  \since 1.0.0
  */
  inline SDL_Color GetSDLVersion() const noexcept { return color; }

  /**
  \brief Returns a shared pointer that points to a Color instance.
  \param r - the red component of the color in the range [MIN_VAL, MAX_VAL].
  \param g - the green component of the color in the range [MIN_VAL, MAX_VAL].
  \param b - the blue component of the color in the range [MIN_VAL, MAX_VAL].
  \param a - the alpha component of the color in the range [MIN_VAL, MAX_VAL].
  \since 1.1.0
  */
  static Color_sptr CreateShared(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

  /**
  \brief Returns a unique pointer that points to a Color instance.
  \param r - the red component of the color in the range [MIN_VAL, MAX_VAL].
  \param g - the green component of the color in the range [MIN_VAL, MAX_VAL].
  \param b - the blue component of the color in the range [MIN_VAL, MAX_VAL].
  \param a - the alpha component of the color in the range [MIN_VAL, MAX_VAL].
  \since 1.1.0
  */
  static Color_uptr CreateUnique(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

};

}  // namespace visuals
}  // namespace centurion