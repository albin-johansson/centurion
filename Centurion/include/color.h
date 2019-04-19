#pragma once
#include <SDL_config.h>
#include <SDL_pixels.h>
#include <memory>

namespace centurion {
namespace visuals {

class Color;
typedef std::shared_ptr<Color> Color_sptr;
typedef std::unique_ptr<Color> Color_uptr;
typedef std::weak_ptr<Color> Color_wptr;

/**
\brief The Color class simply represents a color.
\since 1.0.0
*/
class Color {
 private:
  SDL_Color color;

 public:
  /**
  \brief The highest possible value for the red, green, blue and alpha
  components.
  \since 1.0.0
  */
  const static uint8_t MAX_VAL = 255;

  /**
  \brief The lowest possible value for the red, green, blue and alpha
  components.
  \since 1.0.0
  */
  const static uint8_t MIN_VAL = 0;

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
  Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

  ~Color();

  /**
  \brief Returns the red component of this color.
  \since 1.0.0
  */
  inline uint8_t GetRed() const noexcept { return color.r; }

  /**
  \brief Returns the green component of this color.
  \since 1.0.0
  */
  inline uint8_t GetGreen() const noexcept { return color.g; }

  /**
  \brief Returns the blue component of this color.
  \since 1.0.0
  */
  inline uint8_t GetBlue() const noexcept { return color.b; }

  /**
  \brief Returns the alpha component of this color.
  \since 1.0.0
  */
  inline uint8_t GetAlpha() const noexcept { return color.a; }

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
  static Color_sptr CreateShared(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

  /**
  \brief Returns a unique pointer that points to a Color instance.
  \param r - the red component of the color in the range [MIN_VAL, MAX_VAL].
  \param g - the green component of the color in the range [MIN_VAL, MAX_VAL].
  \param b - the blue component of the color in the range [MIN_VAL, MAX_VAL].
  \param a - the alpha component of the color in the range [MIN_VAL, MAX_VAL].
  \since 1.1.0
  */
  static Color_uptr CreateUnique(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

  /**
  \brief Returns a weak pointer that points to a Color instance.
  \param r - the red component of the color in the range [MIN_VAL, MAX_VAL].
  \param g - the green component of the color in the range [MIN_VAL, MAX_VAL].
  \param b - the blue component of the color in the range [MIN_VAL, MAX_VAL].
  \param a - the alpha component of the color in the range [MIN_VAL, MAX_VAL].
  \since 1.1.0
  */
  static Color_wptr CreateWeak(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
};

}  // namespace visuals
}  // namespace centurion