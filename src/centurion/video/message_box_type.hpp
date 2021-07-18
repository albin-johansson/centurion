#ifndef CENTURION_MESSAGE_BOX_TYPE_HEADER
#define CENTURION_MESSAGE_BOX_TYPE_HEADER

#include <SDL.h>

#include "../core/integers.hpp"

namespace cen {

/// \addtogroup video
/// \{

/**
 * \enum message_box_type
 *
 * \brief Serves as a hint of the purpose of a message box.
 *
 * \details Message boxes can indicate errors, warnings and general information.
 *
 * \since 5.0.0
 */
enum class message_box_type : u32
{
  error = SDL_MESSAGEBOX_ERROR,
  warning = SDL_MESSAGEBOX_WARNING,
  information = SDL_MESSAGEBOX_INFORMATION
};

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_MESSAGE_BOX_TYPE_HEADER
