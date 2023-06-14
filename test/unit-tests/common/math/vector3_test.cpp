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

#include <gtest/gtest.h>

#include <iostream>  // cout

#include "centurion/math.hpp"
#include "serialization_utils.hpp"

using float3 = cen::basic_vector3<float>;
using int3 = cen::basic_vector3<int>;

TEST(Vector3, Defaults)
{
  const float3 vec;
  ASSERT_EQ(0, vec.x);
  ASSERT_EQ(0, vec.y);
  ASSERT_EQ(0, vec.z);
}

TEST(Vector3, CastOperator)
{
  {  // int -> float
    const int3 src {12, 34, 56};
    const auto result = static_cast<float3>(src);
    ASSERT_EQ(static_cast<float>(src.x), result.x);
    ASSERT_EQ(static_cast<float>(src.y), result.y);
    ASSERT_EQ(static_cast<float>(src.z), result.z);
  }

  {  // float -> int
    const float3 src {12.3f, 45.6f, 7.89f};
    const auto result = static_cast<int3>(src);
    ASSERT_EQ(static_cast<int>(src.x), result.x);
    ASSERT_EQ(static_cast<int>(src.y), result.y);
    ASSERT_EQ(static_cast<int>(src.z), result.z);
  }
}

TEST(Vector3, StreamOperator)
{
  std::cout << float3 {12.3f, 45.6f} << '\n';
}

TEST(Vector3, EqualityOperator)
{
  {  // Reflexivity
    const float3 vec {12.3f, 45.6f};
    ASSERT_EQ(vec, vec);
  }

  {  // Identical vectors
    const float3 vec {12.3f, 45.6f};
    const float3 copy {vec};
    ASSERT_EQ(vec, copy);
    ASSERT_EQ(copy, vec);
  }

  {  // Different vectors
    const float3 fst {27.7f, 42.6f};
    const float3 snd {954.3f, 243.2f};
    ASSERT_FALSE(fst == snd);
    ASSERT_FALSE(snd == fst);
  }
}

TEST(Vector3, InequalityOperator)
{
  {  // Self
    const float3 vec {12.3f, 45.6f};
    ASSERT_FALSE(vec != vec);
  }

  {  // Identical vectors
    const float3 vec {12.3f, 45.6f};
    const float3 copy {vec};
    ASSERT_FALSE(vec != copy);
    ASSERT_FALSE(copy != vec);
  }

  {  // Different vectors
    const float3 fst {27.7f, 42.6f};
    const float3 snd {954.3f, 243.2f};
    ASSERT_NE(fst, snd);
    ASSERT_NE(snd, fst);
  }
}

TEST(Vector3, Serialization)
{
  const auto x = 7842;
  const auto y = 3234;
  const auto z = -1295;
  serialize_save("basic_vector3.binary", int3 {x, y, z});

  const auto vector = serialize_create<int3>("basic_vector3.binary");
  ASSERT_EQ(x, vector.x);
  ASSERT_EQ(y, vector.y);
  ASSERT_EQ(z, vector.z);
}