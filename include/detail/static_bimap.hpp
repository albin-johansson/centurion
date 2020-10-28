/*
 * MIT License
 *
 * Copyright (c) 2019-2020 Albin Johansson
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

#ifndef CENTURION_DETAIL_STATIC_BIMAP_HEADER
#define CENTURION_DETAIL_STATIC_BIMAP_HEADER

#include <array>    // array
#include <utility>  // pair

#include "centurion_api.hpp"
#include "detail/algorithm.hpp"
#include "exception.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen::detail {

/**
 * \class static_bimap
 *
 * \brief A bidirectional associative container for when keys and values are
 * known at compile-time.
 *
 * \note This class is only meant to be used in constexpr contexts.
 *
 * \remarks This class was inspired by Jason Turners C++ Weekly video on
 * constexpr maps!
 *
 * \tparam Key the type of the keys, must provide an overloaded `operator==`.
 * \tparam Value the type of the values.
 * \tparam ValueCmp the predicate used to lookup values from keys.
 * \tparam size the amount of key-value pairs.
 *
 * \since 5.0.0
 *
 * \headerfile static_bimap.hpp
 */
template <typename Key, typename Value, typename ValueCmp, std::size_t size>
class static_bimap final
{
  using pair_type = std::pair<Key, Value>;
  using storage_type = std::array<pair_type, size>;

 public:
  storage_type data;

  constexpr auto find(const Key& key) const -> const Value&
  {
    for (const pair_type& pair : data) {
      if (pair.first == key) {
        return pair.second;
      }
    }
    throw exception{"Failed to find element in static map!"};
  }

  constexpr auto key_from(const Value& value) const -> const Key&
  {
    ValueCmp compare{};
    for (const pair_type& pair : data) {
      if (compare(pair.second, value)) {
        return pair.first;
      }
    }
    throw exception{"Failed to find key in static map!"};
  }
};

}  // namespace cen::detail

#endif  // CENTURION_DETAIL_STATIC_BIMAP_HEADER
