// Copyright (C) 2019-2024 Albin Johansson (MIT License)

#pragma once

namespace cen::inline v8_0_0 {

template <typename T>
struct basic_extent final
{
  T width;
  T height;
};

using iextent = basic_extent<int>;
using fextent = basic_extent<float>;

}  // namespace cen::inline v8_0_0
