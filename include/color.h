/*
 * MIT License
 *
 * Copyright (c) 2019-2020 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @brief Provides the @link centurion::Color @endlink class.
 *
 * @file color.h
 * @author Albin Johansson
 * @date 2019-2020
 * @copyright MIT License
 */

#ifndef CENTURION_COLOR_HEADER
#define CENTURION_COLOR_HEADER

#include <SDL.h>

#include <string>
#include <type_traits>
#include <utility>

#include "centurion_api.h"

namespace centurion {

/**
 * @class Color
 * @brief An 8-bit accuracy RGBA color.
 * @details This class is designed to be easily be created and converted
 * from/to SDL colors, such as `SDL_Color` and `SDL_MessageBoxColor`.
 * @headerfile color.h
 * @since 3.0.0
 */
class Color final {
 public:
  /**
   * The maximum possible value of a color component.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Uint8 max;

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
   * @param a the alpha component value, in the rage [0, 255]. By default, the
   * alpha value is set to 255.
   * @since 3.0.0
   */
  constexpr Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xFF) noexcept
      : m_red{r}, m_green{g}, m_blue{b}, m_alpha{a}
  {}

  /**
   * Creates a color that is a copy of the supplied color.
   *
   * @param other the color that will be copied.
   * @since 3.0.0
   */
  constexpr Color(const Color& other) noexcept = default;

  /**
   * Move constructor.
   *
   * @param other the color that will be moved.
   * @since 3.0.0
   */
  constexpr Color(Color&& other) noexcept = default;

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
   * Creates a color that is a copy of the supplied SDL_MessageBoxColor. Message
   * box colors don't have an alpha component so the created color will feature
   * an alpha value of 255.
   *
   * @param color the message box color that will be copied.
   * @since 3.0.0
   */
  CENTURION_API explicit Color(const SDL_MessageBoxColor& color) noexcept;

  /**
   * Creates a color by moving the supplied SDL_MessageBoxColor. Message box
   * colors don't have an alpha component so the created color will feature an
   * alpha value of 255.
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
  Color& operator=(const Color& other) noexcept = default;

  /**
   * Moves the fields of the supplied color.
   *
   * @param other the color that will be moved.
   * @return the modified color.
   * @since 3.0.0
   */
  Color& operator=(Color&& other) noexcept = default;

  /**
   * Sets the value of the red component.
   *
   * @param r the value of the red component.
   * @since 3.0.0
   */
  CENTURION_API void set_red(Uint8 r) noexcept;

  /**
   * Sets the value of the green component.
   *
   * @param g the value of the green component.
   * @since 3.0.0
   */
  CENTURION_API void set_green(Uint8 g) noexcept;

  /**
   * Sets the value of the blue component.
   *
   * @param b the value of the blue component.
   * @since 3.0.0
   */
  CENTURION_API void set_blue(Uint8 b) noexcept;

  /**
   * Sets the value of the alpha component.
   *
   * @param a the value of the alpha component.
   * @since 3.0.0
   */
  CENTURION_API void set_alpha(Uint8 a) noexcept;

  /**
   * Returns the value of the red component.
   *
   * @return the value of the red component, in the range [0, 255].
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  Uint8 red() const noexcept { return m_red; }

  /**
   * Returns the value of the green component.
   *
   * @return the value of the green component, in the range [0, 255].
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  Uint8 green() const noexcept { return m_green; }

  /**
   * Returns the value of the blue component.
   *
   * @return the value of the blue component, in the range [0, 255].
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  Uint8 blue() const noexcept { return m_blue; }

  /**
   * Returns the value of the alpha component.
   *
   * @return the value of the alpha component, in the range [0, 255].
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  Uint8 alpha() const noexcept { return m_alpha; }

  /**
   * Returns a textual representation of the color.
   *
   * @return a textual representation of the color.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API std::string to_string() const;

  /**
   * Implicitly converts the the color into an SDL_Color.
   *
   * @return an SDL_Color that mirrors this color.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API operator SDL_Color() const noexcept;

  /**
   * Converts the color to a pointer to a SDL_Color instance.
   *
   * @return a pointer to the Color instance reinterpreted as a SDL_Color
   * instance.
   * @since 4.0,0
   */
  CENTURION_NODISCARD
  CENTURION_API explicit operator SDL_Color*() noexcept;

  /**
   * Converts the color to a pointer to a SDL_Color instance.
   *
   * @return a pointer to the Color instance reinterpreted as a SDL_Color
   * instance.
   * @since 4.0,0
   */
  CENTURION_NODISCARD
  CENTURION_API explicit operator const SDL_Color*() const noexcept;

  /**
   * Implicitly converts the the color into an SDL_MessageBoxColor. Note that
   * message box colors don't feature an alpha value!
   *
   * @return an SDL_MessageBoxColor that this the color.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API operator SDL_MessageBoxColor() const noexcept;

 private:
  Uint8 m_red = 0;
  Uint8 m_green = 0;
  Uint8 m_blue = 0;
  Uint8 m_alpha = max;
};

/**
 * An alias for the British spelling of color.
 *
 * @since 3.1.0
 */
using Colour = Color;

/**
 * Indicates whether or not the two colors are considered to be equal.
 *
 * @param color the lhs color.
 * @param other the rhs color.
 * @return true if the colors feature the same color component values; false
 * otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(const Color& color, const Color& other) noexcept;

/**
 * Indicates whether or not the two colors are considered to be equal.
 *
 * @param color the lhs color.
 * @param sdlColor the rhs color.
 * @return true if the colors feature the same color component values; false
 * otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(const Color& color,
                              const SDL_Color& sdlColor) noexcept;

/**
 * Indicates whether or not the two colors are considered to be equal.
 *
 * @param sdlColor the lhs color.
 * @param color the rhs color.
 * @return true if the colors feature the same color component values; false
 * otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(const SDL_Color& sdlColor,
                              const Color& color) noexcept;

/**
 * Indicates whether or not the two colors are considered to be equal. Note!
 * The alpha components are not taken into account.
 *
 * @param color the lhs color.
 * @param msgColor the rhs color.
 * @return true if the colors feature the same color component values; false
 * otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(const Color& color,
                              const SDL_MessageBoxColor& msgColor) noexcept;

/**
 * Indicates whether or not the two colors are considered to be equal. Note!
 * The alpha components are not taken into account.
 *
 * @param msgColor the lhs color.
 * @param color the rhs color.
 * @return true if the colors feature the same color component values; false
 * otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(const SDL_MessageBoxColor& msgColor,
                              const Color& color) noexcept;

/**
 * Indicates whether or not two colors aren't considered to be equal.
 *
 * @param color the lhs color.
 * @param other the rhs color.
 * @return true if the colors don't feature the same color components; false
 * otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator!=(const Color& color, const Color& other) noexcept;

/**
 * Indicates whether or not two colors aren't considered to be equal.
 *
 * @param color the lhs color.
 * @param sdlColor the rhs color.
 * @return true if the colors don't feature the same color components; false
 * otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator!=(const Color& color,
                              const SDL_Color& sdlColor) noexcept;

/**
 * Indicates whether or not two colors aren't considered to be equal.
 *
 * @param sdlColor the lhs color.
 * @param color the rhs color.
 * @return true if the colors don't feature the same color components; false
 * otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator!=(const SDL_Color& sdlColor,
                              const Color& color) noexcept;

/**
 * Indicates whether or not two colors aren't considered to be equal. Note!
 * The alpha components of the colors are not taken into account.
 *
 * @param color the lhs color.
 * @param msgColor the rhs color.
 * @return true if the colors don't feature the same color components; false
 * otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator!=(const Color& color,
                              const SDL_MessageBoxColor& msgColor) noexcept;

/**
 * Indicates whether or not two colors aren't considered to be equal. Note!
 * The alpha components of the colors are not taken into account.
 *
 * @param msgColor the lhs color.
 * @param color the rhs color.
 * @return true if the colors don't feature the same color components; false
 * otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator!=(const SDL_MessageBoxColor& msgColor,
                              const Color& color) noexcept;

#ifdef CENTURION_HAS_IS_FINAL_TYPE_TRAIT
static_assert(std::is_final<Color>::value, "Color isn't final!");
#endif

static_assert(std::is_convertible<Color, SDL_Color>::value,
              "Color isn't convertible to SDL_Color!");

static_assert(std::is_convertible<Color, SDL_MessageBoxColor>::value,
              "Color isn't convertible to SDL_MessageBoxColor!");

static_assert(std::is_default_constructible<Color>::value,
              "Color isn't default constructible!");

static_assert(std::is_nothrow_copy_constructible<Color>::value,
              "Color isn't copy constructible!");

static_assert(std::is_nothrow_copy_assignable<Color>::value,
              "Color isn't nothrow copy assignable!");

static_assert(std::is_nothrow_move_constructible<Color>::value,
              "Color isn't nothrow move constructible!");

static_assert(std::is_nothrow_move_assignable<Color>::value,
              "Color isn't nothrow move assignable!");

}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "color.cpp"
#endif

#endif  // CENTURION_COLOR_HEADER
