#ifndef CENTURION_BLEND_OP_HEADER
#define CENTURION_BLEND_OP_HEADER

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../core/exception.hpp"

namespace cen {

/// \addtogroup video
/// \{

/**
 * \enum blend_op
 *
 * \brief Represents different strategies used when combining pixel components.
 *
 * \see `blend_factor`
 * \see `compose_blend_mode()`
 *
 * \since 6.3.0
 */
enum class blend_op
{
  add = SDL_BLENDOPERATION_ADD,
  sub = SDL_BLENDOPERATION_SUBTRACT,
  reverse_sub = SDL_BLENDOPERATION_REV_SUBTRACT,
  min = SDL_BLENDOPERATION_MINIMUM,
  max = SDL_BLENDOPERATION_MAXIMUM
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied blend operation.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(blend_op::add) == "add"`.
 *
 * \param op the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.3.0
 */
[[nodiscard]] constexpr auto to_string(const blend_op op) -> std::string_view
{
  switch (op) {
    case blend_op::add:
      return "add";

    case blend_op::sub:
      return "sub";

    case blend_op::reverse_sub:
      return "reverse_sub";

    case blend_op::min:
      return "min";

    case blend_op::max:
      return "max";

    default:
      throw cen_error{"Did not recognize blend operation!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a blend operation enumerator.
 *
 * \param stream the output stream that will be used.
 * \param op the enumerator that will be printed.
 *
 * \see `to_string(blend_op)`
 *
 * \return the used stream.
 *
 * \since 6.3.0
 */
inline auto operator<<(std::ostream& stream, const blend_op op) -> std::ostream&
{
  return stream << to_string(op);
}

/// \} End of streaming

/// \name Blend operation comparison operators
/// \{

/**
 * \brief Indicates whether or not two blend operation values are the same;
 *
 * \param lhs the left-hand side blend operation value.
 * \param rhs the right-hand side blend operation value.
 *
 * \return `true` if the values are the same; `false` otherwise.
 *
 * \since 6.3.0
 */
[[nodiscard]] constexpr auto operator==(const blend_op lhs,
                                        const SDL_BlendOperation rhs) noexcept -> bool
{
  return static_cast<SDL_BlendOperation>(lhs) == rhs;
}

/// \copydoc operator==(blend_op, SDL_BlendOperation)
[[nodiscard]] constexpr auto operator==(const SDL_BlendOperation lhs,
                                        const blend_op rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not two blend operation values aren't the same;
 *
 * \param lhs the left-hand side blend operation value.
 * \param rhs the right-hand side blend operation value.
 *
 * \return `true` if the values aren't the same; `false` otherwise.
 *
 * \since 6.3.0
 */
[[nodiscard]] constexpr auto operator!=(const blend_op lhs,
                                        const SDL_BlendOperation rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \copydoc operator!=(blend_op, SDL_BlendOperation)
[[nodiscard]] constexpr auto operator!=(const SDL_BlendOperation lhs,
                                        const blend_op rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \} End of blend operation comparison operators

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_BLEND_OP_HEADER