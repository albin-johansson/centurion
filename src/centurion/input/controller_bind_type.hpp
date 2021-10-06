#ifndef CENTURION_CONTROLLER_BIND_TYPE_HEADER
#define CENTURION_CONTROLLER_BIND_TYPE_HEADER

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../core/exception.hpp"

namespace cen {

/// \addtogroup input
/// \{

/**
 * \enum controller_bind_type
 *
 * \brief Represents different game controller bind types.
 *
 * \see `SDL_GameControllerBindType`
 *
 * \since 5.0.0
 */
enum class controller_bind_type
{
  none = SDL_CONTROLLER_BINDTYPE_NONE,
  button = SDL_CONTROLLER_BINDTYPE_BUTTON,
  axis = SDL_CONTROLLER_BINDTYPE_AXIS,
  hat = SDL_CONTROLLER_BINDTYPE_HAT
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied controller bind type.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(controller_bind_type::button) == "button"`.
 *
 * \param type the controller bind type that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const controller_bind_type type) -> std::string_view
{
  switch (type) {
    case controller_bind_type::none:
      return "none";

    case controller_bind_type::button:
      return "button";

    case controller_bind_type::axis:
      return "axis";

    case controller_bind_type::hat:
      return "hat";

    default:
      throw cen_error{"Did not recognzie controller bind type!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a controller bind type enumerator.
 *
 * \param stream the output stream that will be used.
 * \param type the controller bind type that will be printed.
 *
 * \see `to_string(controller_bind_type)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const controller_bind_type type) -> std::ostream&
{
  return stream << to_string(type);
}

/// \} End of streaming

/// \name Controller bind type comparison operators
/// \{

/**
 * \brief Indicates whether or not two controller bind type values are the same.
 *
 * \param lhs the left-hand-side controller bind type value.
 * \param rhs the right-hand-side controller bind type value.
 *
 * \return `true` if the values are the same; `false` otherwise.
 *
 * \since 5.0.0
 */
[[nodiscard]] constexpr auto operator==(const controller_bind_type lhs,
                                        const SDL_GameControllerBindType rhs) noexcept -> bool
{
  return static_cast<SDL_GameControllerBindType>(lhs) == rhs;
}

/// \copydoc operator==(controller_bind_type, SDL_GameControllerBindType)
[[nodiscard]] constexpr auto operator==(const SDL_GameControllerBindType lhs,
                                        const controller_bind_type rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not two controller bind type values aren't the
 * same.
 *
 * \param lhs the left-hand-side controller bind type value.
 * \param rhs the right-hand-side controller bind type value.
 *
 * \return `true` if the values aren't the same; `false` otherwise.
 *
 * \since 5.0.0
 */
[[nodiscard]] constexpr auto operator!=(const controller_bind_type lhs,
                                        const SDL_GameControllerBindType rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \copydoc operator!=(controller_bind_type, SDL_GameControllerBindType)
[[nodiscard]] constexpr auto operator!=(const SDL_GameControllerBindType lhs,
                                        const controller_bind_type rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \} End of controller bind type comparison operators

/// \} End of group input

}  // namespace cen

#endif  // CENTURION_CONTROLLER_BIND_TYPE_HEADER
