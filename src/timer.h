#pragma once
#include <cstdint>

namespace centurion {

/**
 * The Timer class provides utilities related to the system clock.
 *
 * @since 3.0.0
 */
class Timer final {
 public:
  Timer() = delete;

  /**
   * Forces the currently executing thread to halt for at least the specified amount of
   * milliseconds. However, the actual time spent sleeping may be longer, depending on the
   * scheduling of the operating system.
   *
   * @param ms the minimum amount of time to sleep for, in milliseconds.
   * @since 3.0.0
   */
  static void sleep(uint32_t ms) noexcept;

  /**
   * Returns the current value of the system high-performance counter.
   *
   * @return the current value of the system high-performance counter.
   * @since 3.0.0
   */
  [[nodiscard]]
  static uint64_t high_res() noexcept;

  /**
   * Returns the frequency of the system high-performance counter.
   *
   * @return the frequency of the system high-performance counter.
   * @since 3.0.0
   */
  [[nodiscard]]
  static uint64_t high_res_freq() noexcept;

  /**
   * Returns the amount of milliseconds since the library was initialized.
   *
   * @return the amount of milliseconds since the library was initialized.
   * @since 3.0.0
   */
  [[nodiscard]]
  static uint32_t millis() noexcept;

};

}
