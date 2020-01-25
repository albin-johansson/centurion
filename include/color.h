/*
 * MIT License
 *
 * Copyright (c) 2019 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once
#include <cstdint>
#include <utility>
#include <string>
#include <SDL.h>
#include "centurion_api.h"

namespace centurion {

/**
 * The Color class represents an RGBA color with 8-bit components. Instances of the Color class
 * can easily be created and converted from/to SDL colors, such as SDL_Color and
 * SDL_MessageBoxColor.
 *
 * @since 3.0.0
 */
class CENTURION_API Color final {
 private:
  uint8_t red = 0;
  uint8_t green = 0;
  uint8_t blue = 0;
  uint8_t alpha = max;

 public:
  /**
   * The maximum possible value of a color component.
   *
   * @since 3.0.0
   */
  static const uint8_t max;

  /**
   * Creates a color. The created color will be equal to #000000FF.
   *
   * @since 3.0.0
   */
  constexpr Color() noexcept = default;

  /**
   * Creates a color.
   *
   * @param r the red component value, in the range [0, 255].
   * @param g the green component value, in the range [0, 255].
   * @param b the blue component value, in the range [0, 255].
   * @param a the alpha component value, in the rage [0, 255]. By default, the alpha value is set
   * to 255.
   * @since 3.0.0
   */
  constexpr Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xFF) noexcept
      : red{r}, green{g}, blue{b}, alpha{a} {}

  /**
   * Creates a color that is a copy of the supplied color.
   *
   * @param color the color that will be copied.
   * @since 3.0.0
   */
  Color(const Color& other) noexcept = default;

  /**
   * Move constructor.
   *
   * @param other the color that will be moved.
   * @since 3.0.0
   */
  CENTURION_API Color(Color&& other) noexcept;

  /**
   * Creates a color that is a copy of the supplied SDL_Color.
   *
   * @param color the SDL_Color that will be copied.
   * @since 3.0.0
   */
  CENTURION_API explicit Color(const SDL_Color& color) noexcept;

  /**
   * Creates a color by moving the supplied SDL_Color.
   *
   * @param color the color that will be moved.
   * @since 3.0.0
   */
  CENTURION_API explicit Color(SDL_Color&& color) noexcept;

  /**
   * Creates a color that is a copy of the supplied SDL_MessageBoxColor. Message box colors
   * don't have an alpha component so the created color will feature an alpha value of 255.
   *
   * @param color the message box color that will be copied.
   * @since 3.0.0
   */
  CENTURION_API explicit Color(const SDL_MessageBoxColor& color) noexcept;

  /**
   * Creates a color by moving the supplied SDL_MessageBoxColor. Message box colors don't have an
   * alpha component so the created color will feature an alpha value of 255.
   *
   * @param color the message box color that will be copied.
   * @since 3.0.0
   */
  CENTURION_API explicit Color(SDL_MessageBoxColor&& color) noexcept;

  /**
   * Copies the fields of the supplied color.
   *
   * @param other the color that will be copied.
   * @return the modified color.
   * @since 3.0.0
   */
  CENTURION_API Color& operator=(const Color& other) noexcept;

  /**
   * Moves the fields of the supplied color.
   *
   * @param other the color that will be moved.
   * @return the modified color.
   * @since 3.0.0
   */
  CENTURION_API Color& operator=(Color&& other) noexcept;

  /**
   * Sets the value of the red component.
   *
   * @param r the value of the red component.
   * @since 3.0.0
   */
  CENTURION_API void set_red(uint8_t r) noexcept;

  /**
   * Sets the value of the green component.
   *
   * @param g the value of the green component.
   * @since 3.0.0
   */
  CENTURION_API void set_green(uint8_t g) noexcept;

  /**
   * Sets the value of the blue component.
   *
   * @param b the value of the blue component.
   * @since 3.0.0
   */
  CENTURION_API void set_blue(uint8_t b) noexcept;

  /**
   * Sets the value of the alpha component.
   *
   * @param a the value of the alpha component.
   * @since 3.0.0
   */
  CENTURION_API void set_alpha(uint8_t a) noexcept;

  /**
   * Indicates whether or not the two colors are considered to be equal.
   *
   * @param color the lhs color.
   * @param other the rhs color.
   * @return true if the colors feature the same color component values; false otherwise.
   * @since 3.0.0
   */
  friend bool operator==(const Color& color, const Color& other) noexcept;

  /**
   * Indicates whether or not the two colors are considered to be equal.
   *
   * @param color the lhs color.
   * @param sdlColor the rhs color.
   * @return true if the colors feature the same color component values; false otherwise.
   * @since 3.0.0
   */
  friend bool operator==(const Color& color, const SDL_Color& sdlColor) noexcept;

  /**
   * Indicates whether or not the two colors are considered to be equal.
   *
   * @param sdlColor the lhs color.
   * @param other the rhs color.
   * @return true if the colors feature the same color component values; false otherwise.
   * @since 3.0.0
   */
  friend bool operator==(const SDL_Color& sdlColor, const Color& color) noexcept;

  /**
   * Indicates whether or not the two colors are considered to be equal. Note! The alpha
   * components are not taken into account.
   *
   * @param color the lhs color.
   * @param msgColor the rhs color.
   * @return true if the colors feature the same color component values; false otherwise.
   * @since 3.0.0
   */
  friend bool operator==(const Color& color,
                         const SDL_MessageBoxColor& msgColor) noexcept;

  /**
   * Indicates whether or not the two colors are considered to be equal. Note! The alpha
   * components are not taken into account.
   *
   * @param msgColor the lhs color.
   * @param color the rhs color.
   * @return true if the colors feature the same color component values; false otherwise.
   * @since 3.0.0
   */
  friend bool operator==(const SDL_MessageBoxColor& msgColor,
                         const Color& color) noexcept;

  /**
   * Indicates whether or not two colors aren't considered to be equal.
   *
   * @param color the lhs color.
   * @param other the rhs color.
   * @return true if the colors don't feature the same color components; false otherwise.
   * @since 3.0.0
   */
  friend bool operator!=(const Color& color, const Color& other) noexcept;

  /**
   * Indicates whether or not two colors aren't considered to be equal.
   *
   * @param color the lhs color.
   * @param sdlColor the rhs color.
   * @return true if the colors don't feature the same color components; false otherwise.
   * @since 3.0.0
   */
  friend bool operator!=(const Color& color, const SDL_Color& sdlColor) noexcept;

  /**
   * Indicates whether or not two colors aren't considered to be equal.
   *
   * @param sdlColor the lhs color.
   * @param other the rhs color.
   * @return true if the colors don't feature the same color components; false otherwise.
   * @since 3.0.0
   */
  friend bool operator!=(const SDL_Color& sdlColor, const Color& color) noexcept;

  /**
   * Indicates whether or not two colors aren't considered to be equal. Note! The alpha
   * components of the colors are not taken into account.
   *
   * @param color the lhs color.
   * @param msgColor the rhs color.
   * @return true if the colors don't feature the same color components; false otherwise.
   * @since 3.0.0
   */
  friend bool operator!=(const Color& color,
                         const SDL_MessageBoxColor& msgColor) noexcept;

  /**
   * Indicates whether or not two colors aren't considered to be equal. Note! The alpha
   * components of the colors are not taken into account.
   *
   * @param msgColor the lhs color.
   * @param color the rhs color.
   * @return true if the colors don't feature the same color components; false otherwise.
   * @since 3.0.0
   */
  friend bool operator!=(const SDL_MessageBoxColor& msgColor,
                         const Color& color) noexcept;

  /**
   * Returns the value of the red component.
   *
   * @return the value of the red component, in the range [0, 255].
   * @since 3.0.0
   */
  [[nodiscard]]
  uint8_t get_red() const noexcept {
    return red;
  }

  /**
   * Returns the value of the green component.
   *
   * @return the value of the green component, in the range [0, 255].
   * @since 3.0.0
   */
  [[nodiscard]]
  uint8_t get_green() const noexcept {
    return green;
  }

  /**
   * Returns the value of the blue component.
   *
   * @return the value of the blue component, in the range [0, 255].
   * @since 3.0.0
   */
  [[nodiscard]]
  uint8_t get_blue() const noexcept {
    return blue;
  }

  /**
   * Returns the value of the alpha component.
   *
   * @return the value of the alpha component, in the range [0, 255].
   * @since 3.0.0
   */
  [[nodiscard]]
  uint8_t get_alpha() const noexcept {
    return alpha;
  }

  /**
   * Returns a textual representation of the color.
   *
   * @return a textual representation of the color.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API std::string to_string() const;

  /**
   * Implicitly converts the the color into an SDL_Color.
   *
   * @return an SDL_Color that mirrors this color.
   * @since 3.0.0
   */
  [[nodiscard]]
  /*implicit*/ operator SDL_Color() const noexcept {
    return {red, green, blue, alpha};
  }

  /**
   * Implicitly converts the the color into an SDL_MessageBoxColor. Note that message box colors
   * don't feature an alpha value!
   *
   * @return an SDL_MessageBoxColor that this the color.
   * @since 3.0.0
   */
  [[nodiscard]]
  /*implicit*/ operator SDL_MessageBoxColor() const noexcept {
    return {red, green, blue};
  }
};

inline bool operator==(const Color& color, const Color& other) noexcept {
  return color.red == other.red
      && color.green == other.green
      && color.blue == other.blue
      && color.alpha == other.alpha;
}

inline bool operator==(const Color& color, const SDL_Color& sdlColor) noexcept {
  return color.red == sdlColor.r
      && color.green == sdlColor.g
      && color.blue == sdlColor.b
      && color.alpha == sdlColor.a;
}

inline bool operator==(const SDL_Color& sdlColor, const Color& color) noexcept {
  return color == sdlColor;
}

inline bool operator==(const Color& color, const SDL_MessageBoxColor& msgColor) noexcept {
  return color.red == msgColor.r
      && color.green == msgColor.g
      && color.blue == msgColor.b;
}

inline bool operator==(const SDL_MessageBoxColor& msgColor, const Color& color) noexcept {
  return color == msgColor;
}

inline bool operator!=(const Color& color, const Color& other) noexcept {
  return !(color == other);
}

inline bool operator!=(const Color& color, const SDL_Color& sdlColor) noexcept {
  return !(color == sdlColor);
}

inline bool operator!=(const SDL_Color& sdlColor, const Color& color) noexcept {
  return !(sdlColor == color);
}

inline bool operator!=(const Color& color, const SDL_MessageBoxColor& msgColor) noexcept {
  return !(color == msgColor);
}

inline bool operator!=(const SDL_MessageBoxColor& msgColor, const Color& color) noexcept {
  return !(msgColor == color);
}

}
