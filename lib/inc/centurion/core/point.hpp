// Copyright (C) 2019-2024 Albin Johansson (MIT License)

#pragma once

namespace cen::inline v8_0_0 {

template <typename T>
struct basic_point final
{
  T x;
  T y;
};

using ipoint = basic_point<int>;
using fpoint = basic_point<float>;

}  // namespace cen::inline v8_0_0
