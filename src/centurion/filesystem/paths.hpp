#ifndef CENTURION_FILESYSTEM_PATHS_HPP_
#define CENTURION_FILESYSTEM_PATHS_HPP_

#include <SDL.h>

#include <cassert>  // assert
#include <string>   // string

#include "../core/common.hpp"
#include "../core/sdl_string.hpp"

namespace cen {

/// \addtogroup filesystem
/// \{

/**
 * \brief Returns the "base" path associated with the application.
 *
 * \details The returned string represents the path to the directory from which
 * application was run from, and will end with a path separator (e.g. "\\" or "/").
 *
 * \note This might be an expensive operation, so it's recommended to only call this
 * function once and cache the returned path.
 *
 * \return the base path of the application; a null string is returned if the path cannot
 * be obtained.
 *
 * \since 5.2.0
 */
[[nodiscard]] inline auto base_path() -> sdl_string
{
  return sdl_string{SDL_GetBasePath()};
}

/**
 * \brief Returns the preferred path for storing application related files.
 *
 * \details This function returns the path to the directory to which applications are
 * meant to write files such as preferences and save data, etc. This directory will be
 * unique per user and application. The returned path will end with a path separator (e.g.
 * "\\" or "/").
 *
 * \note Only use letters, numbers, and spaces in the supplied names!
 *
 * \param org the name of the organization, cannot be null.
 * \param app the name of the application, cannot be null.
 *
 * \return an absolute path to the preferred path for storing application files; a null
 * string is returned if something goes wrong.
 *
 * \since 5.2.0
 */
[[nodiscard]] inline auto preferred_path(const char* org, const char* app) -> sdl_string
{
  /* Looking at the SDL source code, it actually seems fine to supply a null
     string for the organization name. However, I haven't been able to find any
     documentation providing this guarantee, so we simply disallow null
     organization names. */
  assert(org);
  assert(app);
  return sdl_string{SDL_GetPrefPath(org, app)};
}

/**
 * \brief Returns the preferred path for storing application related files.
 *
 * \details This function returns the path to the directory to which applications are
 * meant to write files such as preferences and save data, etc. This directory will be
 * unique per user and application. The returned path will end with a path separator (e.g.
 * "\\" or "/").
 *
 * \note Only use letters, numbers, and spaces in the supplied names!
 *
 * \param org the name of the organization.
 * \param app the name of the application.
 *
 * \return an absolute path to the preferred path for storing application files; a null
 * string is returned if something goes wrong.
 *
 * \since 6.0.0
 */
[[nodiscard]] inline auto preferred_path(const std::string& org, const std::string& app)
    -> sdl_string
{
  return preferred_path(org.c_str(), app.c_str());
}

/// \} End of group filesystem

}  // namespace cen

#endif  // CENTURION_FILESYSTEM_PATHS_HPP_
