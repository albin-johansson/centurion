#ifndef CENTURION_GRAPHICS_DRIVERS_HEADER
#define CENTURION_GRAPHICS_DRIVERS_HEADER

#include <SDL.h>

#include <optional>  // optional

namespace cen {

/// \addtogroup video
/// \{

/**
 * \brief Returns the number of available rendering drivers.
 *
 * \note Usually there is only one available rendering driver.
 *
 * \return the number of available rendering drivers.
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto render_driver_count() noexcept -> int
{
  return SDL_GetNumRenderDrivers();
}

/**
 * \brief Returns the number of available video drivers compiled into SDL.
 *
 * \return the number of available video drivers compiled into SDL.
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto video_driver_count() noexcept -> int
{
  return SDL_GetNumVideoDrivers();
}

/**
 * \brief Returns the information associated with a rendering driver.
 *
 * \param index the index of the rendering driver to query.
 *
 * \return information about the specified rendering driver; `std::nullopt` if something
 * went wrong.
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto get_render_driver_info(const int index) noexcept
    -> std::optional<SDL_RendererInfo>
{
  SDL_RendererInfo info{};
  if (SDL_GetRenderDriverInfo(index, &info) == 0) {
    return info;
  }
  else {
    return std::nullopt;
  }
}

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_GRAPHICS_DRIVERS_HEADER
