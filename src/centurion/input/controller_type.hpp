#ifndef CENTURION_CONTROLLER_TYPE_HEADER
#define CENTURION_CONTROLLER_TYPE_HEADER

#include <SDL.h>

#include <ostream>  // ostream
#include <string>   // string

#include "../core/exception.hpp"

namespace cen {

/// \addtogroup input
/// \{

#if SDL_VERSION_ATLEAST(2, 0, 12)

/**
 * \enum controller_type
 *
 * \brief Represents different game controller types.
 *
 * \see `SDL_GameControllerType`
 *
 * \since 5.0.0
 */
enum class controller_type
{
  unknown = SDL_CONTROLLER_TYPE_UNKNOWN,   ///< An unknown controller.
  xbox_360 = SDL_CONTROLLER_TYPE_XBOX360,  ///< An Xbox 360 controller.
  xbox_one = SDL_CONTROLLER_TYPE_XBOXONE,  ///< An Xbox One controller.
  ps3 = SDL_CONTROLLER_TYPE_PS3,           ///< A PS3 controller.
  ps4 = SDL_CONTROLLER_TYPE_PS4,           ///< A PS4 controller.

#if SDL_VERSION_ATLEAST(2, 0, 14)

  ps5 = SDL_CONTROLLER_TYPE_PS5,       ///< A PS5 controller.
  virt = SDL_CONTROLLER_TYPE_VIRTUAL,  ///< A virtual controller.

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  nintendo_switch_pro = SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_PRO  ///< A Nintendo Switch
  ///< Pro controller.
};

/**
 * \brief Returns a textual version of the supplied controller type.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(controller_type::ps4) == "ps4"`.
 *
 * \param type the controller type that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] inline auto to_string(const controller_type type) -> std::string
{
  switch (type)
  {
    case controller_type::unknown:
      return "unknown";

    case controller_type::nintendo_switch_pro:
      return "nintendo_switch_pro";

    case controller_type::xbox_360:
      return "xbox_360";

    case controller_type::xbox_one:
      return "xbox_one";

    case controller_type::ps3:
      return "ps3";

    case controller_type::ps4:
      return "ps4";

#if SDL_VERSION_ATLEAST(2, 0, 14)

    case controller_type::ps5:
      return "ps5";

    case controller_type::virt:
      return "virt";

#endif  //  SDL_VERSION_ATLEAST(2, 0, 14)

    default:
      throw cen_error{"Did not recognize controller type!"};
  }
}

/**
 * \brief Prints a textual representation of a controller type enumerator.
 *
 * \param stream the output stream that will be used.
 * \param type the controller type that will be printed.
 *
 * \see `to_string(controller_type)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const controller_type type) -> std::ostream&
{
  return stream << to_string(type);
}

/// \name Controller type comparison operators
/// \{

/**
 * \brief Indicates whether or not to controller type values are the same.
 *
 * \param lhs the left-hand side controller type value.
 * \param rhs the right-hand side controller type value.
 *
 * \return `true` if the controller type values are the same; `false` otherwise.
 *
 * \since 5.0.0
 */
[[nodiscard]] constexpr auto operator==(const controller_type lhs,
                                        const SDL_GameControllerType rhs) noexcept -> bool
{
  return static_cast<SDL_GameControllerType>(lhs) == rhs;
}

/// \copydoc operator==(controller_type, SDL_GameControllerType)
[[nodiscard]] constexpr auto operator==(const SDL_GameControllerType lhs,
                                        const controller_type rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not to controller type values aren't the same.
 *
 * \param lhs the left-hand side controller type value.
 * \param rhs the right-hand side controller type value.
 *
 * \return `true` if the controller type values aren't the same; `false`
 * otherwise.
 *
 * \since 5.0.0
 */
[[nodiscard]] constexpr auto operator!=(const controller_type lhs,
                                        const SDL_GameControllerType rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \copydoc operator!=(controller_type, SDL_GameControllerType)
[[nodiscard]] constexpr auto operator!=(const SDL_GameControllerType lhs,
                                        const controller_type rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \} End of controller type comparison operators

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

/// \} End of group input

}  // namespace cen

#endif  // CENTURION_CONTROLLER_TYPE_HEADER