/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CENTURION_VIDEO_BLEND_HPP_
#define CENTURION_VIDEO_BLEND_HPP_

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../common.hpp"

namespace cen {

enum class blend_mode {
  none = SDL_BLENDMODE_NONE,    ///< No blending.
  blend = SDL_BLENDMODE_BLEND,  ///< Alpha blending.
  add = SDL_BLENDMODE_ADD,      ///< Additive blending.
  mod = SDL_BLENDMODE_MOD,      ///< Color modulation.

#if SDL_VERSION_ATLEAST(2, 0, 12)

  mul = SDL_BLENDMODE_MUL,  ///< Color multiplication.

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

  invalid = SDL_BLENDMODE_INVALID
};

enum class blend_factor {
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

enum class blend_op {
  add = SDL_BLENDOPERATION_ADD,
  sub = SDL_BLENDOPERATION_SUBTRACT,
  reverse_sub = SDL_BLENDOPERATION_REV_SUBTRACT,
  min = SDL_BLENDOPERATION_MINIMUM,
  max = SDL_BLENDOPERATION_MAXIMUM
};

/// Describes how a blend mode factors should be combined.
struct blend_task final {
  blend_factor src;  ///< The blend factor applied to the source pixels.
  blend_factor dst;  ///< The blend factor applied to the destination pixels.
  blend_op op;       ///< The operation used to combine the source and destination pixels.
};

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
      throw exception {"Did not recognize blend mode!"};
  }
}

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
      throw exception {"Did not recognize blend operation!"};
  }
}

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
      throw exception {"Did not recognize blend factor!"};
  }
}

inline auto operator<<(std::ostream& stream, const blend_mode mode) -> std::ostream&
{
  return stream << to_string(mode);
}

inline auto operator<<(std::ostream& stream, const blend_factor factor) -> std::ostream&
{
  return stream << to_string(factor);
}

inline auto operator<<(std::ostream& stream, const blend_op op) -> std::ostream&
{
  return stream << to_string(op);
}

}  // namespace cen

#endif  // CENTURION_VIDEO_BLEND_HPP_
