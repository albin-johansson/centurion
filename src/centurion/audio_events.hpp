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

#ifndef CENTURION_AUDIO_EVENTS_HPP_
#define CENTURION_AUDIO_EVENTS_HPP_

#include <SDL.h>

#include "common.hpp"
#include "event_base.hpp"

namespace cen {

class audio_device_event final : public event_base<SDL_AudioDeviceEvent>
{
 public:
  audio_device_event() : event_base{event_type::audio_device_added} {}

  explicit audio_device_event(const SDL_AudioDeviceEvent& event) noexcept : event_base{event}
  {}

  void set_which(const uint32 which) noexcept { mEvent.which = which; }

  void set_capture(const bool capture) noexcept { mEvent.iscapture = capture; }

  [[nodiscard]] auto which() const noexcept -> uint32 { return mEvent.which; }

  [[nodiscard]] auto is_capture() const noexcept -> bool { return mEvent.iscapture; }

  [[nodiscard]] auto is_output() const noexcept -> bool { return !is_capture(); }
};

template <>
inline auto as_sdl_event(const event_base<SDL_AudioDeviceEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.adevice = event.get();
  return e;
}

}  // namespace cen

#endif  // CENTURION_AUDIO_EVENTS_HPP_
