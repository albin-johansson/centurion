#ifndef CENTURION_PREF_PATH_HEADER
#define CENTURION_PREF_PATH_HEADER

#include <SDL.h>

#include <cassert>  // assert

#include "../centurion_cfg.hpp"
#include "../czstring.hpp"
#include "../not_null.hpp"
#include "../sdl_string.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/// \addtogroup system
/// \{

/**
 * \brief Returns the preferred path for storing application related files.
 *
 * \details This function returns the path to the directory to which
 * applications are meant to write files such as preferences and save data, etc.
 * This directory will be unique per user and application. The returned path
 * will end with a path separator (e.g. "\\" or "/").
 *
 * \note Only use letters, numbers, and spaces in the supplied names!
 *
 * \param org the name of the organization, cannot be null.
 * \param app the name of the application, cannot be null.
 *
 * \todo std::string overload
 *
 * \return an absolute path to the preferred path for storing application files;
 * a null string is returned if something goes wrong.
 *
 * \since 5.2.0
 */
[[nodiscard]] inline auto get_pref_path(const not_null<czstring> org,
                                        const not_null<czstring> app)
    -> sdl_string
{
  assert(org);
  assert(app);
  return sdl_string{SDL_GetPrefPath(org, app)};
}

/// \}

}  // namespace cen

#endif  // CENTURION_PREF_PATH_HEADER