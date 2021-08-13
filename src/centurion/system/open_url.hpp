#ifndef CENTURION_OPEN_URL_HEADER
#define CENTURION_OPEN_URL_HEADER

#include <SDL.h>

#include <cassert>  // assert
#include <string>   // string

#include "../core/not_null.hpp"
#include "../core/result.hpp"
#include "../core/str.hpp"

namespace cen {

/// \addtogroup system
/// \{

#if SDL_VERSION_ATLEAST(2, 0, 14)

/**
 * \brief Attempts to open a URL using a web browser or even a file manager for local
 * files.
 *
 * \note This function will return `success` if there was at least an "attempt" to open
 * the specified URL, but it doesn't mean that the URL was successfully loaded.
 *
 * \remarks This function will differ greatly in its effects depending on the current
 * platform.
 *
 * \param url the URL that should be opened, cannot be null.
 *
 * \return `success` if there was an attempt to open the URL; `failure` otherwise.
 *
 * \since 5.2.0
 */
inline auto open_url(const not_null<str> url) noexcept -> result
{
  assert(url);
  return SDL_OpenURL(url) == 0;
}

/**
 * \see open_url()
 * \since 5.3.0
 */
inline auto open_url(const std::string& url) noexcept -> result
{
  return open_url(url.c_str());
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

/// \} End of group system

}  // namespace cen

#endif  // CENTURION_OPEN_URL_HEADER