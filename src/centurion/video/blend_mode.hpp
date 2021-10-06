#ifndef CENTURION_BLEND_MODE_HEADER
#define CENTURION_BLEND_MODE_HEADER

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../core/exception.hpp"
#include "blend_factor.hpp"
#include "blend_op.hpp"

namespace cen {

/// \addtogroup video
/// \{

/**
 * \enum blend_mode
 *
 * \brief Provides values that represent various rendering blend modes.
 *
 * \since 3.0.0
 *
 * \see `SDL_BlendMode`
 */
enum class blend_mode
{
  none = SDL_BLENDMODE_NONE,    ///< Represents no blending.
  blend = SDL_BLENDMODE_BLEND,  ///< Represents alpha blending.
  add = SDL_BLENDMODE_ADD,      ///< Represents additive blending.
  mod = SDL_BLENDMODE_MOD,      ///< Represents color modulation.

#if SDL_VERSION_ATLEAST(2, 0, 12)

  mul = SDL_BLENDMODE_MUL,  ///< Represents color multiplication.

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

  invalid = SDL_BLENDMODE_INVALID  ///< Represents an invalid blend mode.
};

/**
 * \struct blend_task
 *
 * \brief Describes how a pair of blend mode factors will be combined.
 *
 * \see `compose_blend_mode()`
 *
 * \since 6.3.0
 */
struct blend_task final
{
  blend_factor src;  ///< The blend factor applied to the source pixels.
  blend_factor dst;  ///< The blend factor applied to the destination pixels.
  blend_op op;       ///< The operation used to combine the source and destination pixels.
};

/**
 * \brief Composes a custom blend mode.
 *
 * \param color the blend task descriptor used for RGB components.
 * \param alpha the blend task descriptor used for alpha components.
 *
 * \return the composed blend mode.
 *
 * \see `blend_task`
 * \see `blend_factor`
 * \see `blend_op`
 *
 * \see `SDL_ComposeCustomBlendMode()`
 * \see `basic_renderer::set_blend_mode()`
 * \see `basic_texture::set_blend_mode()`
 *
 * \since 6.3.0
 */
[[nodiscard]] inline auto compose_blend_mode(const blend_task& color,
                                             const blend_task& alpha) noexcept -> blend_mode
{
  const auto res = SDL_ComposeCustomBlendMode(static_cast<SDL_BlendFactor>(color.src),
                                              static_cast<SDL_BlendFactor>(color.dst),
                                              static_cast<SDL_BlendOperation>(color.op),
                                              static_cast<SDL_BlendFactor>(alpha.src),
                                              static_cast<SDL_BlendFactor>(alpha.dst),
                                              static_cast<SDL_BlendOperation>(alpha.op));
  return static_cast<blend_mode>(res);
}

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied blend mode.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(blend_mode::blend) == "blend"`.
 *
 * \param mode the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const blend_mode mode) -> std::string_view
{
  switch (mode) {
    case blend_mode::none:
      return "none";

    case blend_mode::blend:
      return "blend";

    case blend_mode::add:
      return "add";

    case blend_mode::mod:
      return "mod";

    case blend_mode::invalid:
      return "invalid";

#if SDL_VERSION_ATLEAST(2, 0, 12)

    case blend_mode::mul:
      return "mul";

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

    default:
      throw cen_error{"Did not recognize blend mode!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a blend mode enumerator.
 *
 * \param stream the output stream that will be used.
 * \param mode the enumerator that will be printed.
 *
 * \see `to_string(blend_mode)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const blend_mode mode) -> std::ostream&
{
  return stream << to_string(mode);
}

/// \} End of streaming

/// \name Blend mode comparison operators
/// \{

/**
 * \brief Indicates whether or not two blend mode values are the same;
 *
 * \param lhs the left-hand side blend mode value.
 * \param rhs the right-hand side blend mode value.
 *
 * \return `true` if the values are the same; `false` otherwise.
 *
 * \since 3.0.0
 */
[[nodiscard]] constexpr auto operator==(const blend_mode lhs, const SDL_BlendMode rhs) noexcept
    -> bool
{
  return static_cast<SDL_BlendMode>(lhs) == rhs;
}

/// \copydoc operator==(blend_mode, SDL_BlendMode)
[[nodiscard]] constexpr auto operator==(const SDL_BlendMode lhs, const blend_mode rhs) noexcept
    -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not two blend mode values aren't the same;
 *
 * \param lhs the left-hand side blend mode value.
 * \param rhs the right-hand side blend mode value.
 *
 * \return `true` if the values aren't the same; `false` otherwise.
 *
 * \since 3.0.0
 */
[[nodiscard]] constexpr auto operator!=(const blend_mode lhs, const SDL_BlendMode rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/// \copydoc operator!=(blend_mode, SDL_BlendMode)
[[nodiscard]] constexpr auto operator!=(const SDL_BlendMode lhs, const blend_mode rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/// \} End of blend mode comparison operators

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_BLEND_MODE_HEADER
