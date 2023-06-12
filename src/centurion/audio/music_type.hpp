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

#ifndef CENTURION_AUDIO_MUSIC_TYPE_HPP_
#define CENTURION_AUDIO_MUSIC_TYPE_HPP_

#ifndef CENTURION_NO_SDL_MIXER

#include <SDL_mixer.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../common.hpp"

namespace cen {

enum class music_type
{
  none = MUS_NONE,
  mp3 = MUS_MP3,
  wav = MUS_WAV,
  ogg = MUS_OGG,
  mod = MUS_MOD,
  midi = MUS_MID,
  cmd = MUS_CMD,
  flac = MUS_FLAC,
  opus = MUS_OPUS
};

[[nodiscard]] constexpr auto to_string(const music_type type) -> std::string_view
{
  switch (type) {
    case music_type::none:
      return "none";

    case music_type::mp3:
      return "mp3";

    case music_type::wav:
      return "wav";

    case music_type::ogg:
      return "ogg";

    case music_type::mod:
      return "mod";

    case music_type::midi:
      return "midi";

    case music_type::cmd:
      return "cmd";

    case music_type::flac:
      return "flac";

    case music_type::opus:
      return "opus";

    default:
      throw exception{"Did not recognize music type!"};
  }
}

inline auto operator<<(std::ostream& stream, const music_type type) -> std::ostream&
{
  return stream << to_string(type);
}

}  // namespace cen

#endif  // CENTURION_NO_SDL_MIXER
#endif  // CENTURION_AUDIO_MUSIC_TYPE_HPP_
