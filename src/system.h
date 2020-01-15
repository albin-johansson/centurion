/*
 * MIT License
 *
 * Copyright (c) 2019 Albin Johansson
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

#pragma once
#include <optional>

namespace centurion {

/**
 * An enum class that provides values that represent various different operating systems.
 *
 * @since 3.0.0
 */
enum class Platform {
  Unknown,
  Windows,
  MacOSX,
  Linux,
  Ios,
  Android
};

/**
 * The System class is a general utility class that provides information about the operating system.
 *
 * @since 3.0.0
 */
class System final {
 public:
  System() = delete;

  /**
   * Returns a value that represents the current platform.
   *
   * @return a value that represents the current platform.
   * @since 3.0.0
   */
  [[nodiscard]]
  static Platform get_platform() noexcept;

  /**
   * Returns the name of the current platform.
   *
   * @return the name of the current platform; std::nullopt if the name cannot be deduced.
   * @since 3.0.0
   */
  [[nodiscard]]
  static std::optional<std::string> get_platform_name() noexcept;
};

/**
 * The CPU class is a utility class that provides information related to, unsurprisingly, the CPU.
 *
 * @since 3.0.0
 */
class CPU final {
 public:
  CPU() = delete;

  /**
   * Returns the CPU L1 cache line size.
   *
   * @return the CPU L1 cache line size, in bytes.
   * @since 3.0.0
   */
  [[nodiscard]]
  static int get_cache_line_size() noexcept;

  /**
   * Returns the amount of cores that the CPU has.
   *
   * @return the amount of cores that the CPU has.
   * @since 3.0.0
   */
  [[nodiscard]]
  static int get_cores() noexcept;
};

/**
 * The RAM class is a utility class that provides information related to, unsurprisingly, the
 * system RAM.
 *
 * @since 3.0.0
 */
class RAM final {
 public:
  RAM() = delete;

  /**
   * Returns the total amount of system RAM in megabytes.
   *
   * @return the total amount of system RAM in megabytes.
   * @since 3.0.0
   */
  [[nodiscard]]
  static int get_size_mb() noexcept;

  /**
   * Returns the total amount of system RAM in gigabytes.
   *
   * @return the total amount of system RAM in gigabytes.
   * @since 3.0.0
   */
  [[nodiscard]]
  static int get_size_gb() noexcept;
};

}
