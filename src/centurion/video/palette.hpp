#ifndef CENTURION_PALETTE_HEADER
#define CENTURION_PALETTE_HEADER

#include <SDL.h>

#include <cassert>  // assert
#include <memory>   // unique_ptr
#include <ostream>  // ostream
#include <string>   // string, to_string

#include "../compiler/features.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

#include "../core/exception.hpp"
#include "../core/integers.hpp"
#include "../core/result.hpp"
#include "../detail/address_of.hpp"
#include "color.hpp"

namespace cen {

/// \addtogroup video
/// \{

/**
 * \class palette
 *
 * \brief Represents a palette of colors.
 *
 * \details This class features an interface similar to a container type, with support for
 * the subscript operator and iteration.
 *
 * \see `SDL_Palette`
 *
 * \since 6.0.0
 */
class palette final
{
 public:
  using iterator = SDL_Color*;
  using const_iterator = const SDL_Color*;

  /// \name Construction
  /// \{

  /**
   * \brief Creates a palette with the specified amount of colors.
   *
   * \param nColors the number of colors in the palette.
   *
   * \throws sdl_error if the palette couldn't be created.
   *
   * \since 6.0.0
   */
  explicit palette(const int nColors) : m_palette{SDL_AllocPalette(nColors)}
  {
    if (!m_palette) {
      throw sdl_error{};
    }
  }

  /// \} End of construction

  /**
   * \brief Sets a color in the palette.
   *
   * \pre `index` must not be negative.
   * \pre `index` must be less than the size of the palette.
   *
   * \param index the index of the color slot that will be changed.
   * \param color the new color that will be used.
   *
   * \since 6.0.0
   */
  auto set_color(const int index, const cen::color& color) noexcept -> result
  {
    assert(index >= 0);
    assert(index < size());
    return SDL_SetPaletteColors(m_palette.get(), color.data(), index, 1) == 0;
  }

  /**
   * \brief Returns the color in the palette at the specified index.
   *
   * \note This function returns a copy of the color, not a reference!
   *
   * \param index the index of color in the palette.
   *
   * \throws cen_error if the supplied index is out of bounds.
   *
   * \return a copy of the color at the specified index in the palette.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto at(const int index) const -> cen::color
  {
    if (index >= 0 && index < size()) {
      return cen::color{m_palette->colors[index]};
    }
    else {
      throw cen_error{"Palette index out of bounds!"};
    }
  }

  /**
   * \brief Returns the color in the palette at the specified index.
   *
   * \warning This function performs no bounds checking, see `at()` for a bounds checked
   * version of this function.
   *
   * \pre `index` must not be negative.
   * \pre `index` must be less than the size of the palette.
   *
   * \note This function returns a copy of the color, not a reference!
   *
   * \param index the index of color in the palette.
   *
   * \return a copy of the color at the specified index in the palette.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto operator[](const int index) const noexcept -> cen::color
  {
    assert(index >= 0);
    assert(index < size());
    return cen::color{m_palette->colors[index]};
  }

  /**
   * \brief Returns the amount of colors in the palette.
   *
   * \return the amount of colors in the palette.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto size() const noexcept -> int
  {
    return m_palette->ncolors;
  }

  /**
   * \brief Returns the version of the palette.
   *
   * \note This value can be incremented by `set_color()`.
   *
   * \return the current version of the palette.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto version() const noexcept -> u32
  {
    return m_palette->version;
  }

  /**
   * \brief Returns a pointer to the associated SDL palette.
   *
   * \warning Do not claim ownership of the returned pointer!
   *
   * \return a pointer to the associated SDL palette
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto get() const noexcept -> SDL_Palette*
  {
    return m_palette.get();
  }

  /// \name Iteration
  /// \{

  [[nodiscard]] auto begin() noexcept -> iterator
  {
    return m_palette->colors;
  }

  [[nodiscard]] auto begin() const noexcept -> const_iterator
  {
    return m_palette->colors;
  }

  [[nodiscard]] auto end() noexcept -> iterator
  {
    return m_palette->colors + size();
  }

  [[nodiscard]] auto end() const noexcept -> const_iterator
  {
    return m_palette->colors + size();
  }

  /// \} End of iteration

 private:
  struct deleter final
  {
    void operator()(SDL_Palette* palette) noexcept
    {
      SDL_FreePalette(palette);
    }
  };

  std::unique_ptr<SDL_Palette, deleter> m_palette;
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual representation of a palette.
 *
 * \param palette the palette that will be converted.
 *
 * \return a textual representation of the palette.
 *
 * \since 6.0.0
 */
[[nodiscard]] inline auto to_string(const palette& palette) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("palette{{data: {}, size: {}}}",
                     detail::address_of(palette.get()),
                     palette.size());
#else
  return "palette{data: " + detail::address_of(palette.get()) +
         ", size: " + std::to_string(palette.size()) + "}";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a palette using a stream.
 *
 * \param stream the stream that will be used.
 * \param palette the palette that will be printed.
 *
 * \return the used stream.
 *
 * \since 6.0.0
 */
inline auto operator<<(std::ostream& stream, const palette& palette) -> std::ostream&
{
  return stream << to_string(palette);
}

/// \} End of streaming

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_PALETTE_HEADER
