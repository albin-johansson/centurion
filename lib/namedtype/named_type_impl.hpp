/**
 * MIT License
 *
 * Copyright (c) 2017 Jonathan Boccara
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef named_type_impl_h
#define named_type_impl_h

#include <type_traits>
#include <utility>

// Enable empty base class optimization with multiple inheritance on Visual
// Studio.
#if defined(_MSC_VER) && _MSC_VER >= 1910
#define FLUENT_EBCO __declspec(empty_bases)
#else
#define FLUENT_EBCO
#endif

namespace fluent {

template <typename T>
using IsNotReference =
    typename std::enable_if<!std::is_reference<T>::value, void>::type;

template <typename T, typename Parameter, template <typename> class... Skills>
class FLUENT_EBCO NamedType
    : public Skills<NamedType<T, Parameter, Skills...>>... {
 public:
  using UnderlyingType = T;

  // constructor
  explicit constexpr NamedType(T const& value) : value_(value) {}
  template <typename T_ = T, typename = IsNotReference<T_>>
  explicit constexpr NamedType(T&& value) : value_(std::move(value))
  {}

  // get
  constexpr T& get() { return value_; }
  constexpr std::remove_reference_t<T> const& get() const { return value_; }

  // conversions
  using ref = NamedType<T&, Parameter, Skills...>;
  operator ref() { return ref(value_); }

  struct argument {
    template <typename U>
    NamedType operator=(U&& value) const
    {
      return NamedType(std::forward<U>(value));
    }
    argument() = default;
    argument(argument const&) = delete;
    argument(argument&&) = delete;
    argument& operator=(argument const&) = delete;
    argument& operator=(argument&&) = delete;
  };

 private:
  T value_;
};

template <template <typename T> class StrongType, typename T>
constexpr StrongType<T> make_named(T const& value)
{
  return StrongType<T>(value);
}

}  // namespace fluent

#endif /* named_type_impl_h */
