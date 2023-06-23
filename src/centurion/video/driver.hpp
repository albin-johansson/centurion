/*
 * MIT License
 *
 * Copyright (c) 2019-2023 Albin Johansson
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

#ifndef CENTURION_VIDEO_DRIVER_HPP_
#define CENTURION_VIDEO_DRIVER_HPP_

#include <SDL.h>

#include <array>          // array
#include <cstddef>        // size_t
#include <optional>       // optional, nullopt
#include <string>         // string
#include <unordered_map>  // unordered_map
#include <vector>         // vector

#include "../common/errors.hpp"
#include "../common/primitives.hpp"

namespace cen {

enum class video_driver {
  cocoa,
  x11,
  directfb,
  windows,
  winrt,
  haiku,
  wiz,
  pandora,
  uikit,
  android,
  ps2,
  psp,
  vita,
  riscos,
  n3ds,
  rpi,
  kmsdrm,
  dummy,
  evdev,
  wayland,
  nacl,
  vivante,
  emscripten,
  qnx,
  offscreen,
  ngage,
  os2dive,
  os2vman,
  unknown,
};

namespace detail {

constexpr usize CEN_VIDEO_DRIVER_MAX {static_cast<usize>(video_driver::unknown) + 1};

inline const std::unordered_map<std::string, video_driver> video_enum_lookup {
    {"cocoa", video_driver::cocoa},
    {"x11", video_driver::x11},
    {"directfb", video_driver::directfb},
    {"windows", video_driver::windows},
    {"winrt", video_driver::winrt},
    {"haiku", video_driver::haiku},
    {"wiz", video_driver::wiz},
    {"pandora", video_driver::pandora},
    {"uikit", video_driver::uikit},
    {"Android", video_driver::android},
    {"PS2", video_driver::ps2},
    {"PSP", video_driver::psp},
    {"VITA", video_driver::vita},
    {"riscos", video_driver::riscos},
    {"n3ds", video_driver::n3ds},
    {"RPI", video_driver::rpi},
    {"KMSDRM", video_driver::kmsdrm},
    {"dummy", video_driver::dummy},
    {"evdev", video_driver::evdev},
    {"wayland", video_driver::wayland},
    {"nacl", video_driver::nacl},
    {"vivante", video_driver::vivante},
    {"emscripten", video_driver::emscripten},
    {"qnx", video_driver::qnx},
    {"offscreen", video_driver::offscreen},
    {"ngage", video_driver::ngage},
    {"DIVE", video_driver::os2dive},
    {"VMAN", video_driver::os2vman},
};

inline const std::array<std::string, CEN_VIDEO_DRIVER_MAX> enum_video_lookup {
    "cocoa",     "x11",     "directfb", "windows", "winrt",      "haiku",
    "wiz",       "pandora", "uikit",    "Android", "PS2",        "PSP",
    "VITA",      "riscos",  "n3ds",     "RPI",     "KMSDRM",     "dummy",
    "evdev",     "wayland", "nacl",     "vivante", "emscripten", "qnx",
    "offscreen", "ngage",   "DIVE",     "VMAN",    "unknown",
};

}  // namespace detail

inline auto video_drivers() -> std::vector<video_driver>
{
  int count {SDL_GetNumVideoDrivers()};
  if (count < 0) {
    throw sdl_error {};
  }

  std::vector<video_driver> drivers(static_cast<usize>(count));

  for (int i {0}; i < count; ++i) {
    const char* driver {SDL_GetVideoDriver(i)};

    if (auto it {detail::video_enum_lookup.find(driver)};
        it != detail::video_enum_lookup.end()) {
      drivers[static_cast<usize>(i)] = it->second;
    }
    else {
      drivers[static_cast<usize>(i)] = video_driver::unknown;
    }
  }

  return drivers;
}

inline auto current_video_driver() -> maybe<video_driver>
{
  const char* driver {SDL_GetCurrentVideoDriver()};

  if (driver == nullptr)
    return nothing;

  if (auto it {detail::video_enum_lookup.find(driver)};
      it != detail::video_enum_lookup.end()) {
    return it->second;
  }

  return video_driver::unknown;
}

inline void init_video(video_driver driver)
{
  const char* driver_string {detail::enum_video_lookup[static_cast<usize>(driver)].data()};

  if (SDL_VideoInit(driver_string) < 0) {
    throw sdl_error {};
  }
}

}  // namespace cen

#endif  // CENTURION_VIDEO_DRIVER_HPP_
