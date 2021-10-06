#ifndef CENTURION_RENDERER_INFO_HEADER
#define CENTURION_RENDERER_INFO_HEADER

#include <SDL.h>

#include <cassert>   // assert
#include <optional>  // optional
#include <ostream>   // ostream
#include <string>    // string, string_literals

#include "../compiler/features.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

#include "../core/exception.hpp"
#include "../core/integers.hpp"
#include "../core/str.hpp"
#include "../core/str_or_na.hpp"
#include "../math/area.hpp"
#include "pixel_format.hpp"
#include "renderer.hpp"

namespace cen {

/// \addtogroup video
/// \{

/**
 * \class renderer_info
 *
 * \brief Provides information about a renderer.
 *
 * \see `get_info()`
 *
 * \since 6.0.0
 */
class renderer_info final
{
  template <typename T>
  friend auto get_info(const basic_renderer<T>& renderer) noexcept
      -> std::optional<renderer_info>;

 public:
  /**
   * \brief Returns a mask of all of the supported renderer flags.
   *
   * \return a mask of the supported renderer flags.
   *
   * \see `basic_renderer::renderer_flags`
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto supported_flags() const noexcept -> u32
  {
    return m_info.flags;
  }

  /**
   * \brief Indicates whether or not the renderer supports VSync.
   *
   * \return `true` if the renderer has VSync support; `false` otherwise.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto has_vsync() const noexcept -> bool
  {
    return supported_flags() & SDL_RENDERER_PRESENTVSYNC;
  }

  /**
   * \brief Indicates whether or not the renderer supports target textures.
   *
   * \return `true` if the renderer has target texture support; `false` otherwise.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto has_target_textures() const noexcept -> bool
  {
    return supported_flags() & SDL_RENDERER_TARGETTEXTURE;
  }

  /**
   * \brief Indicates whether or not the renderer supports hardware acceleration.
   *
   * \return `true` if the renderer has hardware acceleration support; `false` otherwise.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto has_hardware_acceleration() const noexcept -> bool
  {
    return supported_flags() & SDL_RENDERER_ACCELERATED;
  }

  /**
   * \brief Indicates whether or not the renderer supports software rendering.
   *
   * \return `true` if the renderer has software rendering support; `false` otherwise.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto has_software_renderer() const noexcept -> bool
  {
    return supported_flags() & SDL_RENDERER_SOFTWARE;
  }

  /**
   * \brief Returns the name associated with the renderer.
   *
   * \return the name of the renderer.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto name() const noexcept -> str
  {
    return m_info.name;
  }

  /**
   * \brief Returns the number of supported pixel formats.
   *
   * \return the amount of available pixel formats.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto format_count() const noexcept -> u32
  {
    return m_info.num_texture_formats;
  }

  /**
   * \brief Returns the supported pixel format at the specified index.
   *
   * \pre `index` must be must be smaller than `pixel_format_count()`.
   *
   * \param index the index of the desired pixel format.
   *
   * \return the supported pixel format at the specified index.,
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto format(const usize index) const noexcept -> pixel_format
  {
    assert(index < format_count());
    return static_cast<pixel_format>(m_info.texture_formats[index]);
  }

  /**
   * \brief Returns the maximum supported width of textures.
   *
   * \return the maximum texture width.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto max_texture_width() const noexcept -> int
  {
    return m_info.max_texture_width;
  }

  /**
   * \brief Returns the maximum supported height of textures.
   *
   * \return the maximum texture height.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto max_texture_height() const noexcept -> int
  {
    return m_info.max_texture_height;
  }

  /**
   * \brief Returns the maximum supported size of textures.
   *
   * \return the maximum texture size.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto max_texture_size() const noexcept -> iarea
  {
    return {max_texture_width(), max_texture_height()};
  }

 private:
  SDL_RendererInfo m_info;

  /**
   * \brief Creates a `renderer_info` instance from an existing SDL info instance.
   *
   * \param info the information that will be copied.
   *
   * \since 6.0.0
   */
  explicit renderer_info(const SDL_RendererInfo info) noexcept : m_info{info}
  {}
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual representation of a `renderer_info` instance.
 *
 * \param info the renderer info instance that will be converted.
 *
 * \return a string that represents the `renderer_info` instance.
 *
 * \since 6.0.0
 */
[[nodiscard]] inline auto to_string(const renderer_info& info) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("renderer_info{{name: {}}}", str_or_na(info.name()));
#else
  using namespace std::string_literals;
  return "renderer_info{name: "s + str_or_na(info.name()) + "}";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a `renderer_info` instance.
 *
 * \param stream the stream that will be used.
 * \param info the `renderer_info` instance that will be printed.
 *
 * \return the used stream.
 *
 * \since 6.0.0
 */
inline auto operator<<(std::ostream& stream, const renderer_info& info) -> std::ostream&
{
  return stream << to_string(info);
}

/// \} End of streaming

/**
 * \brief Returns information about a renderer.
 *
 * \tparam T the ownership semantics of the renderer.
 *
 * \param renderer the renderer to obtain information about.
 *
 * \return information about the supplied renderer; `std::nullopt` if something goes
 * wrong.
 *
 * \since 6.0.0
 */
template <typename T>
[[nodiscard]] auto get_info(const basic_renderer<T>& renderer) noexcept
    -> std::optional<renderer_info>
{
  SDL_RendererInfo info;
  if (SDL_GetRendererInfo(renderer.get(), &info) == 0) {
    return renderer_info{info};
  }
  else {
    return std::nullopt;
  }
}

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_RENDERER_INFO_HEADER
