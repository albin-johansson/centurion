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

#ifndef CENTURION_SYSTEM_TIME_HPP_
#define CENTURION_SYSTEM_TIME_HPP_

#include <chrono>  // duration
#include <ratio>   // milli, micro, nano

#include <SDL3/SDL.h>

#include <centurion/common/chrono.hpp>
#include <centurion/common/macros.hpp>
#include <centurion/common/primitives.hpp>

namespace cen {

class Time final {
  inline static constexpr double one_thousand = 1'000;
  inline static constexpr double one_million = 1'000'000;
  inline static constexpr double one_billion = 1'000'000'000;

 public:
  using value_type = uint64;
  using s_type = std::chrono::duration<value_type>;
  using ms_type = std::chrono::duration<value_type, std::milli>;
  using us_type = std::chrono::duration<value_type, std::micro>;
  using ns_type = std::chrono::duration<value_type, std::nano>;

  CEN_CANNOT_COPY(Time);
  CEN_CANNOT_MOVE(Time);

  Time() = delete;
  ~Time() = delete;

  [[nodiscard]] static auto since_init_ms() noexcept -> ms_type
  {
    return ms_type {SDL_GetTicks()};
  }

  [[nodiscard]] static auto since_init_us() noexcept -> us_type
  {
    return us_type {since_init_ns().count() / value_type {1'000}};
  }

  [[nodiscard]] static auto since_init_ns() noexcept -> ns_type
  {
    return ns_type {SDL_GetTicksNS()};
  }

  [[nodiscard]] static auto frequency() noexcept -> uint64
  {
    return SDL_GetPerformanceFrequency();
  }

  [[nodiscard]] static auto now() noexcept -> uint64
  {
    return SDL_GetPerformanceCounter();
  }

  [[nodiscard]] static auto now_s() noexcept -> s_type
  {
    return s_type {static_cast<value_type>(_now_seconds())};
  }

  [[nodiscard]] static auto now_ms() noexcept -> ms_type
  {
    return ms_type {static_cast<value_type>(_now_seconds() * one_thousand)};
  }

  [[nodiscard]] static auto now_us() noexcept -> us_type
  {
    return us_type {static_cast<value_type>(_now_seconds() * one_million)};
  }

  [[nodiscard]] static auto now_ns() noexcept -> ns_type
  {
    return ns_type {static_cast<value_type>(_now_seconds() * one_billion)};
  }

 private:
  [[nodiscard]] static auto _now_seconds() noexcept -> double
  {
    const auto counter = static_cast<double>(SDL_GetPerformanceCounter());
    const auto freq = static_cast<double>(SDL_GetPerformanceFrequency());
    return counter / freq;
  }
};

}  // namespace cen

#endif  // CENTURION_SYSTEM_TIME_HPP_
