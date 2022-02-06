#ifndef CENTURION_COLOR_HPP_
#define CENTURION_COLOR_HPP_

#include <SDL.h>

#include <cassert>      // assert
#include <cmath>        // round, abs, fmod, lerp
#include <iomanip>      // setfill, setw
#include <ios>          // uppercase, hex
#include <optional>     // optional
#include <ostream>      // ostream
#include <sstream>      // stringstream
#include <string>       // string, to_string
#include <string_view>  // string_view

#include "common.hpp"
#include "detail/stdlib.hpp"
#include "features.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

/// \addtogroup video
/// \{

/**
 * \brief A representation of an 8-bit RGBA color.
 *
 * \details This class supports construction and conversion from various formats such as the
 * SDL color types, HSV, HSL, normalized components, and hexadecimal RGB/RGBA/ARGB color codes.
 *
 * \details A large collection of named color constants for commonly used HTML colors is
 * provided in the `cen::colors` namespace.
 *
 * \serializable
 *
 * \see `blend(const color&, const color&, float)`
 * \see `cen::colors`
 */
class color final
{
 public:
  /// \name Construction
  /// \{

  /**
   * \brief Creates an opaque black color.
   */
  constexpr color() noexcept = default;

  /**
   * \brief Creates a color.
   *
   * \param red the red component value.
   * \param green the green component value.
   * \param blue the blue component value.
   * \param alpha the alpha component value.
   */
  constexpr color(const uint8 red,
                  const uint8 green,
                  const uint8 blue,
                  const uint8 alpha = 0xFF) noexcept
      : mColor{red, green, blue, alpha}
  {}

  /**
   * \brief Copies a plain SDL color.
   *
   * \param color the color that will be copied.
   */
  constexpr explicit color(const SDL_Color& color) noexcept : mColor{color} {}

  /**
   * \brief Copies an SDL message box color.
   *
   * \details The created color is fully opaque.
   *
   * \param color the color that will be copied.
   */
  constexpr explicit color(const SDL_MessageBoxColor& color) noexcept
      : mColor{color.r, color.g, color.b, 0xFF}
  {}

  /**
   * \brief Creates a color from HSV-encoded values.
   *
   * \details The values will be clamped to be within their respective ranges.
   *
   * \param hue the hue of the color, in the range [0, 360].
   * \param saturation the saturation of the color, in the range [0, 100].
   * \param value the value of the color, in the range [0, 100].
   *
   * \return an RGBA color converted from the HSV values.
   */
  [[nodiscard]] static auto from_hsv(float hue, float saturation, float value) -> color
  {
    hue = detail::clamp(hue, 0.0f, 360.0f);
    saturation = detail::clamp(saturation, 0.0f, 100.0f);
    value = detail::clamp(value, 0.0f, 100.0f);

    const auto v = (value / 100.0f);
    const auto chroma = v * (saturation / 100.0f);
    const auto hp = hue / 60.0f;

    const auto x = chroma * (1.0f - std::abs(std::fmod(hp, 2.0f) - 1.0f));

    float red{};
    float green{};
    float blue{};

    if (0 <= hp && hp <= 1) {
      red = chroma;
      green = x;
      blue = 0;
    }
    else if (1 < hp && hp <= 2) {
      red = x;
      green = chroma;
      blue = 0;
    }
    else if (2 < hp && hp <= 3) {
      red = 0;
      green = chroma;
      blue = x;
    }
    else if (3 < hp && hp <= 4) {
      red = 0;
      green = x;
      blue = chroma;
    }
    else if (4 < hp && hp <= 5) {
      red = x;
      green = 0;
      blue = chroma;
    }
    else if (5 < hp && hp <= 6) {
      red = chroma;
      green = 0;
      blue = x;
    }

    const auto m = v - chroma;

    const auto r = static_cast<uint8>(std::round((red + m) * 255.0f));
    const auto g = static_cast<uint8>(std::round((green + m) * 255.0f));
    const auto b = static_cast<uint8>(std::round((blue + m) * 255.0f));

    return {r, g, b};
  }

  /**
   * \brief Creates a color from HSL-encoded values.
   *
   * \details The values will be clamped to be within their respective ranges.
   *
   * \param hue the hue of the color, in the range [0, 360].
   * \param saturation the saturation of the color, in the range [0, 100].
   * \param lightness the lightness of the color, in the range [0, 100].
   *
   * \return an RGBA color converted from the HSL values.
   */
  [[nodiscard]] static auto from_hsl(float hue, float saturation, float lightness) -> color
  {
    hue = detail::clamp(hue, 0.0f, 360.0f);
    saturation = detail::clamp(saturation, 0.0f, 100.0f);
    lightness = detail::clamp(lightness, 0.0f, 100.0f);

    const auto s = saturation / 100.0f;
    const auto l = lightness / 100.0f;

    const auto chroma = (1.0f - std::abs(2.0f * l - 1.0f)) * s;
    const auto hp = hue / 60.0f;

    const auto x = chroma * (1.0f - std::abs(std::fmod(hp, 2.0f) - 1.0f));

    float red{};
    float green{};
    float blue{};

    if (0 <= hp && hp < 1) {
      red = chroma;
      green = x;
      blue = 0;
    }
    else if (1 <= hp && hp < 2) {
      red = x;
      green = chroma;
      blue = 0;
    }
    else if (2 <= hp && hp < 3) {
      red = 0;
      green = chroma;
      blue = x;
    }
    else if (3 <= hp && hp < 4) {
      red = 0;
      green = x;
      blue = chroma;
    }
    else if (4 <= hp && hp < 5) {
      red = x;
      green = 0;
      blue = chroma;
    }
    else if (5 <= hp && hp < 6) {
      red = chroma;
      green = 0;
      blue = x;
    }

    const auto m = l - (chroma / 2.0f);

    const auto r = static_cast<uint8>(std::round((red + m) * 255.0f));
    const auto g = static_cast<uint8>(std::round((green + m) * 255.0f));
    const auto b = static_cast<uint8>(std::round((blue + m) * 255.0f));

    return {r, g, b};
  }

  /**
   * \brief Attempts to create a color based on a hexadecimal RGB color code.
   *
   * \details The color code string must feature a `#` prefix, and be 7 characters long.
   *
   * \param rgb the RGB color code, using the format "#RRGGBB".
   *
   * \return a color corresponding to the hex code; an empty optional upon failure.
   *
   * \see `from_rgba()`
   * \see `from_argb()`
   */
  [[nodiscard]] static auto from_rgb(const std::string_view rgb) -> std::optional<color>
  {
    if (rgb.length() != 7 || rgb.at(0) != '#') {
      return std::nullopt;
    }

    const auto noHash = rgb.substr(1);

    const auto rr = noHash.substr(0, 2);
    const auto gg = noHash.substr(2, 2);
    const auto bb = noHash.substr(4, 2);

    const auto red = detail::stoi<uint8>(rr, 16);
    const auto green = detail::stoi<uint8>(gg, 16);
    const auto blue = detail::stoi<uint8>(bb, 16);

    if (red && green && blue) {
      return color{*red, *green, *blue};
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Attempts to create a color based on a hexadecimal RGBA color code.
   *
   * \details The color code string must feature a `#` prefix, and be 9 characters long.
   *
   * \param rgba the RGBA color code, using the format "#RRGGBBAA".
   *
   * \return a color corresponding to the hex code; an empty optional upon failure.
   *
   * \see `from_rgb()`
   * \see `from_argb()`
   */
  [[nodiscard]] static auto from_rgba(const std::string_view rgba) -> std::optional<color>
  {
    if (rgba.length() != 9 || rgba.at(0) != '#') {
      return std::nullopt;
    }

    const auto noHash = rgba.substr(1);

    const auto rr = noHash.substr(0, 2);
    const auto gg = noHash.substr(2, 2);
    const auto bb = noHash.substr(4, 2);
    const auto aa = noHash.substr(6, 2);

    const auto red = detail::stoi<uint8>(rr, 16);
    const auto green = detail::stoi<uint8>(gg, 16);
    const auto blue = detail::stoi<uint8>(bb, 16);
    const auto alpha = detail::stoi<uint8>(aa, 16);

    if (red && green && blue && alpha) {
      return color{*red, *green, *blue, *alpha};
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Attempts to create a color based on a hexadecimal ARGB color code.
   *
   * \details The color code string must feature a `#` prefix, and be 9 characters long.
   *
   * \param argb the ARGB color code, using the format "#AARRGGBB".
   *
   * \return a color corresponding to the hex code; an empty optional upon failure.
   *
   * \see `from_rgb()`
   * \see `from_rgba()`
   */
  [[nodiscard]] static auto from_argb(const std::string_view argb) -> std::optional<color>
  {
    if (argb.length() != 9 || argb.at(0) != '#') {
      return std::nullopt;
    }

    const auto noHash = argb.substr(1);

    const auto aa = noHash.substr(0, 2);
    const auto rr = noHash.substr(2, 2);
    const auto gg = noHash.substr(4, 2);
    const auto bb = noHash.substr(6, 2);

    const auto alpha = detail::stoi<uint8>(aa, 16);
    const auto red = detail::stoi<uint8>(rr, 16);
    const auto green = detail::stoi<uint8>(gg, 16);
    const auto blue = detail::stoi<uint8>(bb, 16);

    if (alpha && red && green && blue) {
      return color{*red, *green, *blue, *alpha};
    }
    else {
      return std::nullopt;
    }
  }

  [[nodiscard]] static auto from_norm(float red,
                                      float green,
                                      float blue,
                                      float alpha = 1.0f) noexcept(on_msvc) -> color
  {
    red = detail::clamp(red, 0.0f, 1.0f);
    green = detail::clamp(green, 0.0f, 1.0f);
    blue = detail::clamp(blue, 0.0f, 1.0f);
    alpha = detail::clamp(alpha, 0.0f, 1.0f);

    const auto r = static_cast<uint8>(std::round(red * 255.0f));
    const auto g = static_cast<uint8>(std::round(green * 255.0f));
    const auto b = static_cast<uint8>(std::round(blue * 255.0f));
    const auto a = static_cast<uint8>(std::round(alpha * 255.0f));

    return color{r, g, b, a};
  }

  /**
   * \brief Returns a copy of the color with the specified alpha value.
   *
   * \param alpha the alpha component value that will be used by the new color.
   *
   * \return a color that is identical to the color except for the alpha component.
   */
  [[nodiscard]] constexpr auto with_alpha(const uint8 alpha) const noexcept -> color
  {
    return {red(), green(), blue(), alpha};
  }

  /// \} End of construction

  /// \name Setters
  /// \{

  /**
   * \brief Sets the red component value.
   *
   * \param red the new red component.
   */
  constexpr void set_red(const uint8 red) noexcept { mColor.r = red; }

  /**
   * \brief Sets the green component value.
   *
   * \param green the new green component.
   */
  constexpr void set_green(const uint8 green) noexcept { mColor.g = green; }

  /**
   * \brief Sets the blue component value.
   *
   * \param blue the new blue component.
   */
  constexpr void set_blue(const uint8 blue) noexcept { mColor.b = blue; }

  /**
   * \brief Sets the alpha component value.
   *
   * \param alpha the new alpha component.
   */
  constexpr void set_alpha(const uint8 alpha) noexcept { mColor.a = alpha; }

  /// \} End of setters

  /// \name Getters
  /// \{

  /**
   * \brief Returns the value of the red component.
   *
   * \return the red component value, in the range [0, 255].
   */
  [[nodiscard]] constexpr auto red() const noexcept -> uint8 { return mColor.r; }

  /**
   * \brief Returns the value of the green component.
   *
   * \return the green component value, in the range [0, 255].
   */
  [[nodiscard]] constexpr auto green() const noexcept -> uint8 { return mColor.g; }

  /**
   * \brief Returns the value of the blue component.
   *
   * \return the blue component value, in the range [0, 255].
   */
  [[nodiscard]] constexpr auto blue() const noexcept -> uint8 { return mColor.b; }

  /**
   * \brief Returns the value of the alpha component.
   *
   * \return the alpha component value, in the range [0, 255].
   */
  [[nodiscard]] constexpr auto alpha() const noexcept -> uint8 { return mColor.a; }

  /**
   * \brief Returns the normalized red component of the color.
   *
   * \return the red component value, in the range [0, 1].
   */
  [[nodiscard]] constexpr auto norm_red() const noexcept -> float
  {
    return static_cast<float>(mColor.r) / 255.0f;
  }

  /**
   * \brief Returns the normalized green component of the color.
   *
   * \return the green component value, in the range [0, 1].
   */
  [[nodiscard]] constexpr auto norm_green() const noexcept -> float
  {
    return static_cast<float>(mColor.g) / 255.0f;
  }

  /**
   * \brief Returns the normalized blue component of the color.
   *
   * \return the blue component value, in the range [0, 1].
   */
  [[nodiscard]] constexpr auto norm_blue() const noexcept -> float
  {
    return static_cast<float>(mColor.b) / 255.0f;
  }

  /**
   * \brief Returns the normalized alpha component of the color.
   *
   * \return the alpha component value, in the range [0, 1].
   */
  [[nodiscard]] constexpr auto norm_alpha() const noexcept -> float
  {
    return static_cast<float>(mColor.a) / 255.0f;
  }

  /// \} End of getters

  /// \name Conversions
  /// \{

  /**
   * \brief Returns a hexadecimal RGB color code, representing the color.
   *
   * \details The returned string is guaranteed to use uppercase hexadecimal digits (A-F).
   *
   * \return a string encoding the color according to the format "#RRGGBB".
   *
   * \see `as_rgba()`
   * \see `as_argb()`
   */
  [[nodiscard]] auto as_rgb() const -> std::string
  {
#if CENTURION_HAS_FEATURE_FORMAT
    return std::format("#{:0<2X}{:0<2X}{:0<2X}", +mColor.r, +mColor.g, +mColor.b);
#else
    std::stringstream stream;
    stream << std::setfill('0') << std::hex << std::uppercase;

    stream << '#';
    stream << std::setw(2) << +mColor.r;
    stream << std::setw(2) << +mColor.g;
    stream << std::setw(2) << +mColor.b;

    return stream.str();
#endif  // CENTURION_HAS_FEATURE_FORMAT
  }

  /**
   * \brief Returns a hexadecimal RGBA color code, representing the color.
   *
   * \details The returned string is guaranteed to use uppercase hexadecimal digits (A-F).
   *
   * \return a string encoding the color according to the format "#RRGGBBAA".
   *
   * \see `as_rgb()`
   * \see `as_argb()`
   */
  [[nodiscard]] auto as_rgba() const -> std::string
  {
#if CENTURION_HAS_FEATURE_FORMAT
    return std::format("#{:0<2X}{:0<2X}{:0<2X}{:0<2X}",
                       +mColor.r,
                       +mColor.g,
                       +mColor.b,
                       +mColor.a);
#else
    std::stringstream stream;
    stream << std::setfill('0') << std::hex << std::uppercase;

    stream << '#';
    stream << std::setw(2) << +mColor.r;
    stream << std::setw(2) << +mColor.g;
    stream << std::setw(2) << +mColor.b;
    stream << std::setw(2) << +mColor.a;

    return stream.str();
#endif  // CENTURION_HAS_FEATURE_FORMAT
  }

  /**
   * \brief Returns a hexadecimal ARGB color code, representing the color.
   *
   * \details The returned string is guaranteed to use uppercase hexadecimal digits (A-F).
   *
   * \return a string encoding the color according to the format "#AARRGGBB".
   *
   * \see `as_rgb()`
   * \see `as_rgba()`
   */
  [[nodiscard]] auto as_argb() const -> std::string
  {
#if CENTURION_HAS_FEATURE_FORMAT
    return std::format("#{:0<2X}{:0<2X}{:0<2X}{:0<2X}",
                       +mColor.a,
                       +mColor.r,
                       +mColor.g,
                       +mColor.b);
#else
    std::stringstream stream;
    stream << std::setfill('0') << std::hex << std::uppercase;

    stream << '#';
    stream << std::setw(2) << +mColor.a;
    stream << std::setw(2) << +mColor.r;
    stream << std::setw(2) << +mColor.g;
    stream << std::setw(2) << +mColor.b;

    return stream.str();
#endif  // CENTURION_HAS_FEATURE_FORMAT
  }

  /**
   * \brief Converts the color into a message box color.
   *
   * \note Message box colors do not feature an alpha component.
   *
   * \return a message box color with the same component values as the color.
   */
  [[nodiscard]] auto as_message_box_color() const noexcept -> SDL_MessageBoxColor
  {
    return {mColor.r, mColor.g, mColor.b};
  }

  /// \} End of conversions

  /// \name Misc functions
  /// \{

  template <typename Archive>
  void serialize(Archive& archive)
  {
    archive(mColor.r, mColor.g, mColor.b, mColor.a);
  }

  [[nodiscard]] auto data() noexcept -> SDL_Color* { return &mColor; }

  [[nodiscard]] auto data() const noexcept -> const SDL_Color* { return &mColor; }

  [[nodiscard]] auto get() const noexcept -> const SDL_Color& { return mColor; }

  /// \} End of misc functions

 private:
  SDL_Color mColor{0, 0, 0, 0xFF};
};

/// \name Color functions
/// \{

/**
 * \brief Blends two colors according to the specified bias.
 *
 * \pre `bias` should be in the range [0, 1].
 *
 * \details This function applies a linear interpolation for each color component to
 * obtain the blended color. The bias parameter is the "alpha" for the interpolation,
 * which determines how the input colors are blended. For example, a bias of 0 or 1 will
 * simply result in the first or second color being returned, respectively.
 * Subsequently, a bias of 0.5 will blend the two colors evenly.
 *
 * \param a the first color.
 * \param b the second color.
 * \param bias the bias that determines how the colors are blended, in the range [0, 1].
 *
 * \return a color obtained by blending the two supplied colors.
 */
[[nodiscard]] inline auto blend(const color& a, const color& b, const float bias = 0.5f)
    -> color
{
  assert(bias >= 0);
  assert(bias <= 1.0f);

  const auto red = detail::lerp(a.norm_red(), b.norm_red(), bias);
  const auto green = detail::lerp(a.norm_green(), b.norm_green(), bias);
  const auto blue = detail::lerp(a.norm_blue(), b.norm_blue(), bias);
  const auto alpha = detail::lerp(a.norm_alpha(), b.norm_alpha(), bias);

  return color::from_norm(red, green, blue, alpha);
}

[[nodiscard]] inline auto to_string(const color& color) -> std::string
{
  return color.as_rgba();
}

inline auto operator<<(std::ostream& stream, const color& color) -> std::ostream&
{
  return stream << to_string(color);
}

[[nodiscard]] constexpr auto operator==(const color& a, const color& b) noexcept -> bool
{
  return (a.red() == b.red()) && (a.green() == b.green()) && (a.blue() == b.blue()) &&
         (a.alpha() == b.alpha());
}

[[nodiscard]] constexpr auto operator!=(const color& a, const color& b) noexcept -> bool
{
  return !(a == b);
}

/// \} End of color functions

/// \} End of group video

/// \ingroup video
namespace colors {

/// \name Color constants
/// \{

inline constexpr color transparent{0, 0, 0, 0};
inline constexpr color white{0xFF, 0xFF, 0xFF};
inline constexpr color black{0, 0, 0};

inline constexpr color alice_blue{0xF0, 0xF8, 0xFF};
inline constexpr color antique_white{0xFA, 0xEB, 0xD7};
inline constexpr color aqua{0, 0xFF, 0xFF};
inline constexpr color aquamarine{0x7F, 0xFF, 0xD4};
inline constexpr color azure{0xF0, 0xFF, 0xFF};
inline constexpr color beige{0xF5, 0xF5, 0xDC};
inline constexpr color bisque{0xFF, 0xE4, 0xC4};
inline constexpr color blanched_almond{0xFF, 0xEB, 0xCD};
inline constexpr color blue{0, 0, 0xFF};
inline constexpr color blue_violet{0x8A, 0x2B, 0xE2};
inline constexpr color brown{0xA5, 0x2A, 0x2A};
inline constexpr color burly_wood{0xDE, 0xB8, 0x87};
inline constexpr color cadet_blue{0x5F, 0x9E, 0xA0};
inline constexpr color chartreuse{0x7F, 0xFF, 0};
inline constexpr color chocolate{0xD2, 0x69, 0x1E};
inline constexpr color coral{0xFF, 0x7F, 0x50};
inline constexpr color cornflower_blue{0x64, 0x95, 0xED};
inline constexpr color cornsilk{0xFF, 0xF8, 0xDC};
inline constexpr color crimson{0xDC, 0x14, 0x3C};
inline constexpr color cyan{0, 0xFF, 0xFF};
inline constexpr color deep_pink{0xFF, 0x14, 0x93};
inline constexpr color deep_sky_blue{0, 0xBF, 0xFF};
inline constexpr color dim_gray{0x69, 0x69, 0x69};
inline constexpr color dim_grey{dim_gray};
inline constexpr color dodger_blue{0x1E, 0x90, 0xFF};
inline constexpr color fire_brick{0xB2, 0x22, 0x22};
inline constexpr color floral_white{0xFF, 0xFA, 0xF0};
inline constexpr color forest_green{0x22, 0x8B, 0x22};
inline constexpr color fuchsia{0xFF, 0, 0xFF};
inline constexpr color gainsboro{0xDC, 0xDC, 0xDC};
inline constexpr color ghost_white{0xF8, 0xF8, 0xFF};
inline constexpr color gold{0xFF, 0xD7, 0};
inline constexpr color golden_rod{0xDA, 0xA5, 0x20};
inline constexpr color gray{0x80, 0x80, 0x80};
inline constexpr color grey{gray};
inline constexpr color green{0, 0x80, 0};
inline constexpr color green_yellow{0xAD, 0xFF, 0x2F};
inline constexpr color honey_dew{0xF0, 0xFF, 0xF0};
inline constexpr color hot_pink{0xFF, 0x69, 0xB4};
inline constexpr color indian_red{0xCD, 0x5C, 0x5C};
inline constexpr color indigo{0x4B, 0, 0x82};
inline constexpr color ivory{0xFF, 0xFF, 0xF0};
inline constexpr color khaki{0xF0, 0xE6, 0x8C};
inline constexpr color lavender{0xE6, 0xE6, 0xFA};
inline constexpr color lavender_blush{0xFF, 0xF0, 0xF5};
inline constexpr color lawn_green{0x7C, 0xFC, 0};
inline constexpr color lemon_chiffon{0xFF, 0xFA, 0xCD};
inline constexpr color lime{0, 0xFF, 0};
inline constexpr color lime_green{0x32, 0xCD, 0x32};
inline constexpr color linen{0xFA, 0xF0, 0xE6};
inline constexpr color magenta{0xFF, 0, 0xFF};
inline constexpr color maroon{0x80, 0, 0};
inline constexpr color midnight_blue{0x19, 0x19, 0x70};
inline constexpr color mint_cream{0xF5, 0xFF, 0xFA};
inline constexpr color misty_rose{0xFF, 0xE4, 0xE1};
inline constexpr color moccasin{0xFF, 0xE4, 0xB5};
inline constexpr color navajo_white{0xFF, 0xDE, 0xAD};
inline constexpr color navy{0, 0, 0x80};
inline constexpr color old_lace{0xFD, 0xF5, 0xE6};
inline constexpr color olive{0x80, 0x80, 0};
inline constexpr color olive_drab{0x6B, 0x8E, 0x23};
inline constexpr color orange{0xFF, 0xA5, 0};
inline constexpr color orange_red{0xFF, 0x45, 0};
inline constexpr color orchid{0xDA, 0x70, 0xD6};
inline constexpr color pale_golden_rod{0xEE, 0xE8, 0xAA};
inline constexpr color pale_green{0x98, 0xFB, 0x98};
inline constexpr color pale_turquoise{0xAF, 0xEE, 0xEE};
inline constexpr color pale_violet_red{0xDB, 0x70, 0x93};
inline constexpr color papaya_whip{0xFF, 0xEF, 0xD5};
inline constexpr color peach_puff{0xFF, 0xDA, 0xB9};
inline constexpr color peru{0xCD, 0x85, 0x3F};
inline constexpr color pink{0xFF, 0xC0, 0xCB};
inline constexpr color plum{0xDD, 0xA0, 0xDD};
inline constexpr color powder_blue{0xB0, 0xE0, 0xE6};
inline constexpr color purple{0x80, 0, 0x80};
inline constexpr color rebecca_purple{0x66, 0x33, 0x99};
inline constexpr color red{0xFF, 0, 0};
inline constexpr color rosy_brown{0xBC, 0x8F, 0x8F};
inline constexpr color royal_blue{0x41, 0x69, 0xE1};
inline constexpr color saddle_brown{0x8B, 0x45, 0x13};
inline constexpr color salmon{0xFA, 0x80, 0x72};
inline constexpr color sandy_brown{0xF4, 0xA4, 0x60};
inline constexpr color sea_green{0x2E, 0x8B, 0x57};
inline constexpr color sea_shell{0xFF, 0xF5, 0xEE};
inline constexpr color sienna{0xA0, 0x52, 0x2D};
inline constexpr color silver{0xC0, 0xC0, 0xC0};
inline constexpr color sky_blue{0x87, 0xCE, 0xEB};
inline constexpr color slate_blue{0x6A, 0x5A, 0xCD};
inline constexpr color slate_gray{0x70, 0x80, 0x90};
inline constexpr color slate_grey{slate_gray};
inline constexpr color snow{0xFF, 0xFA, 0xFA};
inline constexpr color spring_green{0, 0xFF, 0x7F};
inline constexpr color steel_blue{0x46, 0x82, 0xB4};
inline constexpr color tan{0xD2, 0xB4, 0x8C};
inline constexpr color teal{0, 0x80, 0x80};
inline constexpr color thistle{0xD8, 0xBF, 0xD8};
inline constexpr color tomato{0xFF, 0x63, 0x47};
inline constexpr color turquoise{0x40, 0xE0, 0xD0};
inline constexpr color violet{0xEE, 0x82, 0xEE};
inline constexpr color wheat{0xF5, 0xDE, 0xB3};
inline constexpr color white_smoke{0xF5, 0xF5, 0xF5};
inline constexpr color yellow{0xFF, 0xFF, 0};
inline constexpr color yellow_green{0x9A, 0xCD, 0x32};

inline constexpr color light_blue{0xAD, 0xD8, 0xE6};
inline constexpr color light_coral{0xF0, 0x80, 0x80};
inline constexpr color light_cyan{0xE0, 0xFF, 0xFF};
inline constexpr color light_golden_rod_yellow{0xFA, 0xFA, 0xD2};
inline constexpr color light_gray{0xD3, 0xD3, 0xD3};
inline constexpr color light_grey{light_gray};
inline constexpr color light_green{0x90, 0xEE, 0x90};
inline constexpr color light_pink{0xFF, 0xB6, 0xC1};
inline constexpr color light_salmon{0xFF, 0xA0, 0x7A};
inline constexpr color light_sea_green{0x20, 0xB2, 0xAA};
inline constexpr color light_sky_blue{0x87, 0xCE, 0xFA};
inline constexpr color light_slate_gray{0x77, 0x88, 0x99};
inline constexpr color light_slate_grey{light_slate_gray};
inline constexpr color light_steel_blue{0xB0, 0xC4, 0xDE};
inline constexpr color light_yellow{0xFF, 0xFF, 0xE0};

inline constexpr color medium_aqua_marine{0x66, 0xCD, 0xAA};
inline constexpr color medium_blue{0, 0, 0xCD};
inline constexpr color medium_orchid{0xBA, 0x55, 0xD3};
inline constexpr color medium_purple{0x93, 0x70, 0xDB};
inline constexpr color medium_sea_green{0x3C, 0xB3, 0x71};
inline constexpr color medium_slate_blue{0x7B, 0x68, 0xEE};
inline constexpr color medium_spring_green{0, 0xFA, 0x9A};
inline constexpr color medium_turquoise{0x48, 0xD1, 0xCC};
inline constexpr color medium_violet_red{0xC7, 0x15, 0x85};

inline constexpr color dark_blue{0, 0, 0x8B};
inline constexpr color dark_cyan{0, 0x8B, 0x8B};
inline constexpr color dark_golden_rod{0xB8, 0x86, 0x0B};
inline constexpr color dark_gray{0xA9, 0xA9, 0xA9};
inline constexpr color dark_grey{dark_gray};
inline constexpr color dark_green{0, 0x64, 0};
inline constexpr color dark_khaki{0xBD, 0xB7, 0x6B};
inline constexpr color dark_magenta{0x8B, 0, 0x8B};
inline constexpr color dark_olive_green{0x55, 0x6B, 0x2F};
inline constexpr color dark_orange{0xFF, 0x8C, 0};
inline constexpr color dark_orchid{0x99, 0x32, 0xCC};
inline constexpr color dark_red{0x8B, 0, 0};
inline constexpr color dark_salmon{0xE9, 0x96, 0x7A};
inline constexpr color dark_sea_green{0x8F, 0xBC, 0x8F};
inline constexpr color dark_slate_blue{0x48, 0x3D, 0x8B};
inline constexpr color dark_slate_gray{0x2F, 0x4F, 0x4F};
inline constexpr color dark_slate_grey{dark_slate_gray};
inline constexpr color dark_turquoise{0, 0xCE, 0xD1};
inline constexpr color dark_violet{0x94, 0, 0xD3};

/// \} End of color constants

}  // namespace colors
}  // namespace cen

#endif  // CENTURION_COLOR_HPP_
