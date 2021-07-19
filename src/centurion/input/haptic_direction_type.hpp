#ifndef CENTURION_HAPTIC_DIRECTION_TYPE_HEADER
#define CENTURION_HAPTIC_DIRECTION_TYPE_HEADER

#include <SDL.h>

namespace cen {

/// \addtogroup input
/// \{

/**
 * \enum haptic_direction_type
 *
 * \brief Represents the different types of haptic directions.
 *
 * \since 5.2.0
 */
enum class haptic_direction_type
{
  polar = SDL_HAPTIC_POLAR,
  cartesian = SDL_HAPTIC_CARTESIAN,
  spherical = SDL_HAPTIC_SPHERICAL
};

/// \} End of group input

}  // namespace cen

#endif  // CENTURION_HAPTIC_DIRECTION_TYPE_HEADER
