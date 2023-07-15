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

namespace cen {

class Result final {
 public:
  constexpr Result(const bool success) noexcept
      : mSuccess {success}
  {
  }

  [[nodiscard]] constexpr auto succeeded() const noexcept -> bool
  {
    return mSuccess;
  }

  [[nodiscard]] constexpr auto failed() const noexcept -> bool
  {
    return !mSuccess;
  }

 private:
  bool mSuccess {};
};

[[nodiscard]] constexpr auto operator==(const Result a, const Result b) noexcept -> bool
{
  return a.succeeded() == b.succeeded();
}

[[nodiscard]] constexpr auto operator!=(const Result a, const Result b) noexcept -> bool
{
  return !(a == b);
}

inline constexpr Result success {true};
inline constexpr Result failure {false};

}  // namespace cen

#endif  // CENTURION_COMMON_RESULT_HPP_
