#ifndef CENTURION_BLEND_FACTOR_HEADER
#define CENTURION_BLEND_FACTOR_HEADER

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../core/exception.hpp"

namespace cen {

/// \addtogroup video
/// \{

/**
 * \enum blend_factor
 *
 * \brief Represents normalized factors used when multiplying pixel components.
 *
 * \see `blend_op`
 * \see `compose_blend_mode()`
 *
 * \since 6.3.0
 */
enum class blend_factor
{
  zero = SDL_BLENDFACTOR_ZERO,
  one = SDL_BLENDFACTOR_ONE,

  src_color = SDL_BLENDFACTOR_SRC_COLOR,
  one_minus_src_color = SDL_BLENDFACTOR_ONE_MINUS_SRC_COLOR,

  src_alpha = SDL_BLENDFACTOR_SRC_ALPHA,
  one_minus_src_alpha = SDL_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,

  dst_color = SDL_BLENDFACTOR_DST_COLOR,
  one_minus_dst_color = SDL_BLENDFACTOR_ONE_MINUS_DST_COLOR,

  dst_alpha = SDL_BLENDFACTOR_DST_ALPHA,
  one_minus_dst_alpha = SDL_BLENDFACTOR_ONE_MINUS_DST_ALPHA
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied blend factor.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(blend_factor::zero) == "zero"`.
 *
 * \param factor the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.3.0
 */
[[nodiscard]] constexpr auto to_string(const blend_factor factor) -> std::string_view
{
  switch (factor) {
    case blend_factor::zero:
      return "zero";

    case blend_factor::one:
      return "one";

    case blend_factor::src_color:
      return "src_color";

    case blend_factor::one_minus_src_color:
      return "one_minus_src_color";

    case blend_factor::src_alpha:
      return "src_alpha";

    case blend_factor::one_minus_src_alpha:
      return "one_minus_src_alpha";

    case blend_factor::dst_color:
      return "dst_color";

    case blend_factor::one_minus_dst_color:
      return "one_minus_dst_color";

    case blend_factor::dst_alpha:
      return "dst_alpha";

    case blend_factor::one_minus_dst_alpha:
      return "one_minus_dst_alpha";

    default:
      throw cen_error{"Did not recognize blend factor!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a blend factor enumerator.
 *
 * \param stream the output stream that will be used.
 * \param factor the enumerator that will be printed.
 *
 * \see `to_string(blend_factor)`
 *
 * \return the used stream.
 *
 * \since 6.3.0
 */
inline auto operator<<(std::ostream& stream, const blend_factor factor) -> std::ostream&
{
  return stream << to_string(factor);
}

/// \} End of streaming

/// \name Blend factor comparison operators
/// \{

/**
 * \brief Indicates whether or not two blend factor values are the same;
 *
 * \param lhs the left-hand side blend factor value.
 * \param rhs the right-hand side blend factor value.
 *
 * \return `true` if the values are the same; `false` otherwise.
 *
 * \since 6.3.0
 */
[[nodiscard]] constexpr auto operator==(const blend_factor lhs,
                                        const SDL_BlendFactor rhs) noexcept -> bool
{
  return static_cast<SDL_BlendFactor>(lhs) == rhs;
}

/// \copydoc operator==(blend_factor, SDL_BlendFactor)
[[nodiscard]] constexpr auto operator==(const SDL_BlendFactor lhs,
                                        const blend_factor rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not two blend factor values aren't the same;
 *
 * \param lhs the left-hand side blend factor value.
 * \param rhs the right-hand side blend factor value.
 *
 * \return `true` if the values aren't the same; `false` otherwise.
 *
 * \since 6.3.0
 */
[[nodiscard]] constexpr auto operator!=(const blend_factor lhs,
                                        const SDL_BlendFactor rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \copydoc operator!=(blend_factor, SDL_BlendFactor)
[[nodiscard]] constexpr auto operator!=(const SDL_BlendFactor lhs,
                                        const blend_factor rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \} End of blend factor comparison operators

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_BLEND_FACTOR_HEADER
