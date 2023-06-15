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

#ifndef CENTURION_COMMON_RESULT_HPP_
#define CENTURION_COMMON_RESULT_HPP_

#include <ostream>  // ostream
#include <string>   // string

namespace cen {

/**
 * A simple indicator for the result of different operations.
 *
 * \details The idea behind this class is to make results of various operations unambiguous.
 *          Quite an amount of functions in the library may fail, and earlier versions of
 *          Centurion would usually return a `bool` in those cases, where `true` and `false`
 *          would indicate success and failure, respectively. This class is a development of
 *          that practice. For instance, this class is contextually convertible to `bool`,
 *          where a successful result is still converted to `true`, and vice versa. However,
 *          this class also enables explicit checks against `success` and `failure` constants,
 *          which makes code very easy to read and unambiguous.
 *
 * \code{cpp}
 * cen::window window;
 *
 * if (window.set_opacity(0.4f)) {
 *   // Success!
 * }
 *
 * if (window.set_opacity(0.4f) == cen::success) {
 *   // Success!
 * }
 *
 * if (window.set_opacity(0.4f) == cen::failure) {
 *   // Failure!
 * }
 * \endcode
 *
 * \see success
 * \see failure
 */
class result final {
 public:
  constexpr result(const bool success) noexcept  // NOLINT implicit
      : mSuccess {success}
  {
  }

  /// Indicates whether the result was a success.
  [[nodiscard]] constexpr explicit operator bool() const noexcept { return mSuccess; }

 private:
  bool mSuccess {};
};

inline constexpr result success {true};   ///< A successful result.
inline constexpr result failure {false};  ///< A failure.

[[nodiscard]] constexpr auto operator==(const result a, const result b) noexcept -> bool
{
  return a.operator bool() == b.operator bool();
}

[[nodiscard]] constexpr auto operator!=(const result a, const result b) noexcept -> bool
{
  return !(a == b);
}

[[nodiscard]] inline auto to_string(const result result) -> std::string
{
  return result ? "success" : "failure";
}

inline auto operator<<(std::ostream& stream, const result result) -> std::ostream&
{
  return stream << to_string(result);
}

}  // namespace cen

#endif  // CENTURION_COMMON_RESULT_HPP_
