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
#include "features.hpp"
#include "detail/stdlib.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

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

  /* Returns a hexadecimal RGB code representation, on the format "#RRGGBB". */
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

  /* Returns a hexadecimal RGBA code representation, on the format "#RRGGBBAA". */
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

  /* Returns a hexadecimal ARGB code representation, on the format "#AARRGGBB". */
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

namespace colors {

inline constexpr Color transparent{0, 0, 0, 0};
inline constexpr Color white{0xFF, 0xFF, 0xFF};
inline constexpr Color black{0, 0, 0};

inline constexpr Color alice_blue{0xF0, 0xF8, 0xFF};
inline constexpr Color antique_white{0xFA, 0xEB, 0xD7};
inline constexpr Color aqua{0, 0xFF, 0xFF};
inline constexpr Color aquamarine{0x7F, 0xFF, 0xD4};
inline constexpr Color azure{0xF0, 0xFF, 0xFF};
inline constexpr Color beige{0xF5, 0xF5, 0xDC};
inline constexpr Color bisque{0xFF, 0xE4, 0xC4};
inline constexpr Color blanched_almond{0xFF, 0xEB, 0xCD};
inline constexpr Color blue{0, 0, 0xFF};
inline constexpr Color blue_violet{0x8A, 0x2B, 0xE2};
inline constexpr Color brown{0xA5, 0x2A, 0x2A};
inline constexpr Color burly_wood{0xDE, 0xB8, 0x87};
inline constexpr Color cadet_blue{0x5F, 0x9E, 0xA0};
inline constexpr Color chartreuse{0x7F, 0xFF, 0};
inline constexpr Color chocolate{0xD2, 0x69, 0x1E};
inline constexpr Color coral{0xFF, 0x7F, 0x50};
inline constexpr Color cornflower_blue{0x64, 0x95, 0xED};
inline constexpr Color cornsilk{0xFF, 0xF8, 0xDC};
inline constexpr Color crimson{0xDC, 0x14, 0x3C};
inline constexpr Color cyan{0, 0xFF, 0xFF};
inline constexpr Color deep_pink{0xFF, 0x14, 0x93};
inline constexpr Color deep_sky_blue{0, 0xBF, 0xFF};
inline constexpr Color dim_gray{0x69, 0x69, 0x69};
inline constexpr Color dim_grey{dim_gray};
inline constexpr Color dodger_blue{0x1E, 0x90, 0xFF};
inline constexpr Color fire_brick{0xB2, 0x22, 0x22};
inline constexpr Color floral_white{0xFF, 0xFA, 0xF0};
inline constexpr Color forest_green{0x22, 0x8B, 0x22};
inline constexpr Color fuchsia{0xFF, 0, 0xFF};
inline constexpr Color gainsboro{0xDC, 0xDC, 0xDC};
inline constexpr Color ghost_white{0xF8, 0xF8, 0xFF};
inline constexpr Color gold{0xFF, 0xD7, 0};
inline constexpr Color golden_rod{0xDA, 0xA5, 0x20};
inline constexpr Color gray{0x80, 0x80, 0x80};
inline constexpr Color grey{gray};
inline constexpr Color green{0, 0x80, 0};
inline constexpr Color green_yellow{0xAD, 0xFF, 0x2F};
inline constexpr Color honey_dew{0xF0, 0xFF, 0xF0};
inline constexpr Color hot_pink{0xFF, 0x69, 0xB4};
inline constexpr Color indian_red{0xCD, 0x5C, 0x5C};
inline constexpr Color indigo{0x4B, 0, 0x82};
inline constexpr Color ivory{0xFF, 0xFF, 0xF0};
inline constexpr Color khaki{0xF0, 0xE6, 0x8C};
inline constexpr Color lavender{0xE6, 0xE6, 0xFA};
inline constexpr Color lavender_blush{0xFF, 0xF0, 0xF5};
inline constexpr Color lawn_green{0x7C, 0xFC, 0};
inline constexpr Color lemon_chiffon{0xFF, 0xFA, 0xCD};
inline constexpr Color lime{0, 0xFF, 0};
inline constexpr Color lime_green{0x32, 0xCD, 0x32};
inline constexpr Color linen{0xFA, 0xF0, 0xE6};
inline constexpr Color magenta{0xFF, 0, 0xFF};
inline constexpr Color maroon{0x80, 0, 0};
inline constexpr Color midnight_blue{0x19, 0x19, 0x70};
inline constexpr Color mint_cream{0xF5, 0xFF, 0xFA};
inline constexpr Color misty_rose{0xFF, 0xE4, 0xE1};
inline constexpr Color moccasin{0xFF, 0xE4, 0xB5};
inline constexpr Color navajo_white{0xFF, 0xDE, 0xAD};
inline constexpr Color navy{0, 0, 0x80};
inline constexpr Color old_lace{0xFD, 0xF5, 0xE6};
inline constexpr Color olive{0x80, 0x80, 0};
inline constexpr Color olive_drab{0x6B, 0x8E, 0x23};
inline constexpr Color orange{0xFF, 0xA5, 0};
inline constexpr Color orange_red{0xFF, 0x45, 0};
inline constexpr Color orchid{0xDA, 0x70, 0xD6};
inline constexpr Color pale_golden_rod{0xEE, 0xE8, 0xAA};
inline constexpr Color pale_green{0x98, 0xFB, 0x98};
inline constexpr Color pale_turquoise{0xAF, 0xEE, 0xEE};
inline constexpr Color pale_violet_red{0xDB, 0x70, 0x93};
inline constexpr Color papaya_whip{0xFF, 0xEF, 0xD5};
inline constexpr Color peach_puff{0xFF, 0xDA, 0xB9};
inline constexpr Color peru{0xCD, 0x85, 0x3F};
inline constexpr Color pink{0xFF, 0xC0, 0xCB};
inline constexpr Color plum{0xDD, 0xA0, 0xDD};
inline constexpr Color powder_blue{0xB0, 0xE0, 0xE6};
inline constexpr Color purple{0x80, 0, 0x80};
inline constexpr Color rebecca_purple{0x66, 0x33, 0x99};
inline constexpr Color red{0xFF, 0, 0};
inline constexpr Color rosy_brown{0xBC, 0x8F, 0x8F};
inline constexpr Color royal_blue{0x41, 0x69, 0xE1};
inline constexpr Color saddle_brown{0x8B, 0x45, 0x13};
inline constexpr Color salmon{0xFA, 0x80, 0x72};
inline constexpr Color sandy_brown{0xF4, 0xA4, 0x60};
inline constexpr Color sea_green{0x2E, 0x8B, 0x57};
inline constexpr Color sea_shell{0xFF, 0xF5, 0xEE};
inline constexpr Color sienna{0xA0, 0x52, 0x2D};
inline constexpr Color silver{0xC0, 0xC0, 0xC0};
inline constexpr Color sky_blue{0x87, 0xCE, 0xEB};
inline constexpr Color slate_blue{0x6A, 0x5A, 0xCD};
inline constexpr Color slate_gray{0x70, 0x80, 0x90};
inline constexpr Color slate_grey{slate_gray};
inline constexpr Color snow{0xFF, 0xFA, 0xFA};
inline constexpr Color spring_green{0, 0xFF, 0x7F};
inline constexpr Color steel_blue{0x46, 0x82, 0xB4};
inline constexpr Color tan{0xD2, 0xB4, 0x8C};
inline constexpr Color teal{0, 0x80, 0x80};
inline constexpr Color thistle{0xD8, 0xBF, 0xD8};
inline constexpr Color tomato{0xFF, 0x63, 0x47};
inline constexpr Color turquoise{0x40, 0xE0, 0xD0};
inline constexpr Color violet{0xEE, 0x82, 0xEE};
inline constexpr Color wheat{0xF5, 0xDE, 0xB3};
inline constexpr Color white_smoke{0xF5, 0xF5, 0xF5};
inline constexpr Color yellow{0xFF, 0xFF, 0};
inline constexpr Color yellow_green{0x9A, 0xCD, 0x32};

inline constexpr Color light_blue{0xAD, 0xD8, 0xE6};
inline constexpr Color light_coral{0xF0, 0x80, 0x80};
inline constexpr Color light_cyan{0xE0, 0xFF, 0xFF};
inline constexpr Color light_golden_rod_yellow{0xFA, 0xFA, 0xD2};
inline constexpr Color light_gray{0xD3, 0xD3, 0xD3};
inline constexpr Color light_grey{light_gray};
inline constexpr Color light_green{0x90, 0xEE, 0x90};
inline constexpr Color light_pink{0xFF, 0xB6, 0xC1};
inline constexpr Color light_salmon{0xFF, 0xA0, 0x7A};
inline constexpr Color light_sea_green{0x20, 0xB2, 0xAA};
inline constexpr Color light_sky_blue{0x87, 0xCE, 0xFA};
inline constexpr Color light_slate_gray{0x77, 0x88, 0x99};
inline constexpr Color light_slate_grey{light_slate_gray};
inline constexpr Color light_steel_blue{0xB0, 0xC4, 0xDE};
inline constexpr Color light_yellow{0xFF, 0xFF, 0xE0};

inline constexpr Color medium_aqua_marine{0x66, 0xCD, 0xAA};
inline constexpr Color medium_blue{0, 0, 0xCD};
inline constexpr Color medium_orchid{0xBA, 0x55, 0xD3};
inline constexpr Color medium_purple{0x93, 0x70, 0xDB};
inline constexpr Color medium_sea_green{0x3C, 0xB3, 0x71};
inline constexpr Color medium_slate_blue{0x7B, 0x68, 0xEE};
inline constexpr Color medium_spring_green{0, 0xFA, 0x9A};
inline constexpr Color medium_turquoise{0x48, 0xD1, 0xCC};
inline constexpr Color medium_violet_red{0xC7, 0x15, 0x85};

inline constexpr Color dark_blue{0, 0, 0x8B};
inline constexpr Color dark_cyan{0, 0x8B, 0x8B};
inline constexpr Color dark_golden_rod{0xB8, 0x86, 0x0B};
inline constexpr Color dark_gray{0xA9, 0xA9, 0xA9};
inline constexpr Color dark_grey{dark_gray};
inline constexpr Color dark_green{0, 0x64, 0};
inline constexpr Color dark_khaki{0xBD, 0xB7, 0x6B};
inline constexpr Color dark_magenta{0x8B, 0, 0x8B};
inline constexpr Color dark_olive_green{0x55, 0x6B, 0x2F};
inline constexpr Color dark_orange{0xFF, 0x8C, 0};
inline constexpr Color dark_orchid{0x99, 0x32, 0xCC};
inline constexpr Color dark_red{0x8B, 0, 0};
inline constexpr Color dark_salmon{0xE9, 0x96, 0x7A};
inline constexpr Color dark_sea_green{0x8F, 0xBC, 0x8F};
inline constexpr Color dark_slate_blue{0x48, 0x3D, 0x8B};
inline constexpr Color dark_slate_gray{0x2F, 0x4F, 0x4F};
inline constexpr Color dark_slate_grey{dark_slate_gray};
inline constexpr Color dark_turquoise{0, 0xCE, 0xD1};
inline constexpr Color dark_violet{0x94, 0, 0xD3};

}  // namespace colors
}  // namespace cen

#endif  // CENTURION_COLOR_HPP_
