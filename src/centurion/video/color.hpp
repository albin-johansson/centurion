#ifndef CENTURION_VIDEO_COLOR_HPP_
#define CENTURION_VIDEO_COLOR_HPP_

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

#include "../core/common.hpp"
#include "../core/exception.hpp"
#include "../core/features.hpp"
#include "../detail/stdlib.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

/// \addtogroup video
/// \{

class Color final {
 public:
  /* Creates a black color */
  constexpr Color() noexcept = default;

  constexpr Color(const Uint8 red,
                  const Uint8 green,
                  const Uint8 blue,
                  const Uint8 alpha = 0xFF) noexcept
      : mColor{red, green, blue, alpha}
  {}

  constexpr explicit Color(const SDL_Color& color) noexcept : mColor{color} {}

  constexpr explicit Color(const SDL_MessageBoxColor& color) noexcept
      : mColor{color.r, color.g, color.b, 0xFF}
  {}

  /**
   * \brief Creates a color from HSV-encoded values.
   *
   * \note The values will be clamped to be within their respective ranges.
   *
   * \param hue the hue of the color, in the range [0, 360].
   * \param saturation the saturation of the color, in the range [0, 100].
   * \param value the value of the color, in the range [0, 100].
   *
   * \return an RGBA color converted from the HSV values.
   */
  [[nodiscard]] static auto FromHSV(float hue, float saturation, float value) -> Color
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

    const auto r = static_cast<Uint8>(std::round((red + m) * 255.0f));
    const auto g = static_cast<Uint8>(std::round((green + m) * 255.0f));
    const auto b = static_cast<Uint8>(std::round((blue + m) * 255.0f));

    return Color{r, g, b};
  }

  /**
   * \brief Creates a color from HSL-encoded values.
   *
   * \note The values will be clamped to be within their respective ranges.
   *
   * \param hue the hue of the color, in the range [0, 360].
   * \param saturation the saturation of the color, in the range [0, 100].
   * \param lightness the lightness of the color, in the range [0, 100].
   *
   * \return an RGBA color converted from the HSL values.
   */
  [[nodiscard]] static auto FromHSL(float hue, float saturation, float lightness) -> Color
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

    const auto r = static_cast<Uint8>(std::round((red + m) * 255.0f));
    const auto g = static_cast<Uint8>(std::round((green + m) * 255.0f));
    const auto b = static_cast<Uint8>(std::round((blue + m) * 255.0f));

    return Color{r, g, b};
  }

  /**
   * \brief Creates a color from a hexadecimal RGB color string.
   *
   * \details The supplied string must feature a leading '#' character, and be 7
   * characters long.
   *
   * \param rgb the hexadecimal RGB color string, using the format "#RRGGBB".
   *
   * \return a corresponding color; `std::nullopt` if something goes wrong.
   *
   * \see `FromRGBA()`
   * \see `FromARGB()`
   */
  [[nodiscard]] static auto FromRGB(const std::string_view rgb) -> std::optional<Color>
  {
    if (rgb.length() != 7 || rgb.at(0) != '#') {
      return std::nullopt;
    }

    const auto noHash = rgb.substr(1);

    const auto rr = noHash.substr(0, 2);
    const auto gg = noHash.substr(2, 2);
    const auto bb = noHash.substr(4, 2);

    const auto red = detail::stoi<Uint8>(rr, 16);
    const auto green = detail::stoi<Uint8>(gg, 16);
    const auto blue = detail::stoi<Uint8>(bb, 16);

    if (red && green && blue) {
      return Color{*red, *green, *blue};
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Creates a color from a hexadecimal RGBA color string.
   *
   * \details The supplied string must feature a leading '#' character, and be 9
   * characters long.
   *
   * \param rgba the hexadecimal RGBA color string, using the format "#RRGGBBAA".
   *
   * \return a corresponding color; `std::nullopt` if something goes wrong.
   *
   * \see `FromRGB()`
   * \see `FromARGB()`
   */
  [[nodiscard]] static auto FromRGBA(const std::string_view rgba) -> std::optional<Color>
  {
    if (rgba.length() != 9 || rgba.at(0) != '#') {
      return std::nullopt;
    }

    const auto noHash = rgba.substr(1);

    const auto rr = noHash.substr(0, 2);
    const auto gg = noHash.substr(2, 2);
    const auto bb = noHash.substr(4, 2);
    const auto aa = noHash.substr(6, 2);

    const auto red = detail::stoi<Uint8>(rr, 16);
    const auto green = detail::stoi<Uint8>(gg, 16);
    const auto blue = detail::stoi<Uint8>(bb, 16);
    const auto alpha = detail::stoi<Uint8>(aa, 16);

    if (red && green && blue && alpha) {
      return Color{*red, *green, *blue, *alpha};
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Creates a color from a hexadecimal ARGB color string.
   *
   * \details The supplied string must feature a leading '#' character, and be 9
   * characters long.
   *
   * \param argb the hexadecimal ARGB color string, using the format "#AARRGGBB".
   *
   * \return a corresponding color; `std::nullopt` if something goes wrong.
   *
   * \see `FromRGB()`
   * \see `FromRGBA()`
   */
  [[nodiscard]] static auto FromARGB(const std::string_view argb) -> std::optional<Color>
  {
    if (argb.length() != 9 || argb.at(0) != '#') {
      return std::nullopt;
    }

    const auto noHash = argb.substr(1);

    const auto aa = noHash.substr(0, 2);
    const auto rr = noHash.substr(2, 2);
    const auto gg = noHash.substr(4, 2);
    const auto bb = noHash.substr(6, 2);

    const auto alpha = detail::stoi<Uint8>(aa, 16);
    const auto red = detail::stoi<Uint8>(rr, 16);
    const auto green = detail::stoi<Uint8>(gg, 16);
    const auto blue = detail::stoi<Uint8>(bb, 16);

    if (alpha && red && green && blue) {
      return Color{*red, *green, *blue, *alpha};
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Creates a color from normalized color component values.
   *
   * \note The color components will be clamped to the range [0, 1].
   *
   * \param red the red component value, in the range [0, 1].
   * \param green the green component value, in the range [0, 1].
   * \param blue the blue component value, in the range [0, 1].
   * \param alpha the alpha component value, in the range [0, 1].
   *
   * \return a color with the supplied color components.
   */
  [[nodiscard]] static auto FromNorm(float red,
                                     float green,
                                     float blue,
                                     float alpha = 1.0f) noexcept(on_msvc) -> Color
  {
    red = detail::clamp(red, 0.0f, 1.0f);
    green = detail::clamp(green, 0.0f, 1.0f);
    blue = detail::clamp(blue, 0.0f, 1.0f);
    alpha = detail::clamp(alpha, 0.0f, 1.0f);

    const auto r = static_cast<Uint8>(std::round(red * 255.0f));
    const auto g = static_cast<Uint8>(std::round(green * 255.0f));
    const auto b = static_cast<Uint8>(std::round(blue * 255.0f));
    const auto a = static_cast<Uint8>(std::round(alpha * 255.0f));

    return Color{r, g, b, a};
  }

  /**
   * \brief Returns a copy of the color with the specified alpha value.
   *
   * \param alpha the alpha component value that will be used by the new color.
   *
   * \return a color that is identical to the color except for the alpha component.
   */
  [[nodiscard]] constexpr auto WithAlpha(const Uint8 alpha) const noexcept -> Color
  {
    return {GetRed(), GetGreen(), GetBlue(), alpha};
  }

  constexpr void SetRed(const Uint8 red) noexcept { mColor.r = red; }

  constexpr void SetGreen(const Uint8 green) noexcept { mColor.g = green; }

  constexpr void SetBlue(const Uint8 blue) noexcept { mColor.b = blue; }

  constexpr void SetAlpha(const Uint8 alpha) noexcept { mColor.a = alpha; }

  [[nodiscard]] constexpr auto GetRed() const noexcept -> Uint8 { return mColor.r; }

  [[nodiscard]] constexpr auto GetGreen() const noexcept -> Uint8 { return mColor.g; }

  [[nodiscard]] constexpr auto GetBlue() const noexcept -> Uint8 { return mColor.b; }

  [[nodiscard]] constexpr auto GetAlpha() const noexcept -> Uint8 { return mColor.a; }

  [[nodiscard]] constexpr auto GetRedNorm() const noexcept -> float
  {
    return static_cast<float>(mColor.r) / 255.0f;
  }

  [[nodiscard]] constexpr auto GetGreenNorm() const noexcept -> float
  {
    return static_cast<float>(mColor.g) / 255.0f;
  }

  [[nodiscard]] constexpr auto GetBlueNorm() const noexcept -> float
  {
    return static_cast<float>(mColor.b) / 255.0f;
  }

  [[nodiscard]] constexpr auto GetAlphaNorm() const noexcept -> float
  {
    return static_cast<float>(mColor.a) / 255.0f;
  }

  /**
   * \brief Returns a hexadecimal RGB color string that represents the color.
   *
   * \details The returned string is guaranteed to use uppercase hexadecimal digits (A-F).
   *
   * \return a hexadecimal color string representation, on the format "#RRGGBB".
   *
   * \see `AsRGBA()`
   * \see `AsARGB()`
   *
   * \since 6.1.0
   */
  [[nodiscard]] auto AsRGB() const -> std::string
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
   * \brief Returns a hexadecimal RGBA color string that represents the color.
   *
   * \details The returned string is guaranteed to use uppercase hexadecimal digits (A-F).
   *
   * \return a hexadecimal color string representation, on the format "#RRGGBBAA".
   *
   * \see `AsRGB()`
   * \see `AsARGB()`
   *
   * \since 6.1.0
   */
  [[nodiscard]] auto AsRGBA() const -> std::string
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
   * \brief Returns a hexadecimal ARGB color string that represents the color.
   *
   * \details The returned string is guaranteed to use uppercase hexadecimal digits (A-F).
   *
   * \return a hexadecimal color string representation, on the format "#AARRGGBB".
   *
   * \see `AsRGB()`
   * \see `AsRGBA()`
   *
   * \since 6.1.0
   */
  [[nodiscard]] auto AsARGB() const -> std::string
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

  [[nodiscard]] auto AsMessageBoxColor() const noexcept -> SDL_MessageBoxColor
  {
    return {mColor.r, mColor.g, mColor.b};
  }

  [[nodiscard]] auto data() noexcept -> SDL_Color* { return &mColor; }

  [[nodiscard]] auto data() const noexcept -> const SDL_Color* { return &mColor; }

  [[nodiscard]] auto get() const noexcept -> const SDL_Color& { return mColor; }

  /**
   * \brief Serializes the color.
   *
   * \details This function expects that the archive provides an overloaded `operator()`,
   * used for serializing data. This API is based on the Cereal serialization library.
   *
   * \tparam Archive the type of the archive.
   *
   * \param archive the archive used to serialize the color.
   */
  template <typename Archive>
  void serialize(Archive& archive)
  {
    archive(mColor.r, mColor.g, mColor.b, mColor.a);
  }

 private:
  SDL_Color mColor{0, 0, 0, 0xFF};
};

[[nodiscard]] inline auto to_string(const Color& color) -> std::string
{
  return color.AsRGBA();
}

inline auto operator<<(std::ostream& stream, const Color& color) -> std::ostream&
{
  return stream << to_string(color);
}

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
[[nodiscard]] inline auto Blend(const Color& a, const Color& b, const float bias = 0.5f)
    -> Color
{
  assert(bias >= 0);
  assert(bias <= 1.0f);

  const auto red = detail::lerp(a.GetRedNorm(), b.GetRedNorm(), bias);
  const auto green = detail::lerp(a.GetGreenNorm(), b.GetGreenNorm(), bias);
  const auto blue = detail::lerp(a.GetBlueNorm(), b.GetBlueNorm(), bias);
  const auto alpha = detail::lerp(a.GetAlphaNorm(), b.GetAlphaNorm(), bias);

  return Color::FromNorm(red, green, blue, alpha);
}

[[nodiscard]] constexpr auto operator==(const Color& lhs, const Color& rhs) noexcept -> bool
{
  return (lhs.GetRed() == rhs.GetRed()) && (lhs.GetGreen() == rhs.GetGreen()) &&
         (lhs.GetBlue() == rhs.GetBlue()) && (lhs.GetAlpha() == rhs.GetAlpha());
}

[[nodiscard]] constexpr auto operator!=(const Color& lhs, const Color& rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_VIDEO_COLOR_HPP_
