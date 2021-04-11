#include "math/vector3.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout

#include "log.hpp"
#include "serialization_utils.hpp"

using float3 = cen::vector3<float>;
using int3 = cen::vector3<int>;

TEST(Vector3, Defaults)
{
  const float3 vec;
  EXPECT_EQ(0, vec.x);
  EXPECT_EQ(0, vec.y);
  EXPECT_EQ(0, vec.z);
}

TEST(Vector3, CastOperator)
{
  {  // int -> float
    const int3 src{12, 34, 56};
    const auto result = static_cast<float3>(src);
    EXPECT_EQ(static_cast<float>(src.x), result.x);
    EXPECT_EQ(static_cast<float>(src.y), result.y);
    EXPECT_EQ(static_cast<float>(src.z), result.z);
  }

  {  // float -> int
    const float3 src{12.3f, 45.6f, 7.89f};
    const auto result = static_cast<int3>(src);
    EXPECT_EQ(static_cast<int>(src.x), result.x);
    EXPECT_EQ(static_cast<int>(src.y), result.y);
    EXPECT_EQ(static_cast<int>(src.z), result.z);
  }
}

TEST(Vector3, StreamOperator)
{
  const float3 vec{12.3f, 45.6f};
  std::cout << "COUT: " << vec << '\n';
}

TEST(Vector3, ToString)
{
  const float3 vec{12.3f, 45.6f};
  cen::log::put(cen::to_string(vec));
}

TEST(Vector3, EqualityOperator)
{
  {  // Reflexivity
    const float3 vec{12.3f, 45.6f};
    EXPECT_EQ(vec, vec);
  }

  {  // Identical vectors
    const float3 vec{12.3f, 45.6f};
    const float3 copy{vec};
    EXPECT_EQ(vec, copy);
    EXPECT_EQ(copy, vec);
  }

  {  // Different vectors
    const float3 fst{27.7f, 42.6f};
    const float3 snd{954.3f, 243.2f};
    EXPECT_FALSE(fst == snd);
    EXPECT_FALSE(snd == fst);
  }
}

TEST(Vector3, InequalityOperator)
{
  {  // Self
    const float3 vec{12.3f, 45.6f};
    EXPECT_FALSE(vec != vec);
  }

  {  // Identical vectors
    const float3 vec{12.3f, 45.6f};
    const float3 copy{vec};
    EXPECT_FALSE(vec != copy);
    EXPECT_FALSE(copy != vec);
  }

  {  // Different vectors
    const float3 fst{27.7f, 42.6f};
    const float3 snd{954.3f, 243.2f};
    EXPECT_NE(fst, snd);
    EXPECT_NE(snd, fst);
  }
}

TEST(Vector3, Serialization)
{
  const auto x = 7842;
  const auto y = 3234;
  const auto z = -1295;
  serialize_to("vector3.binary", int3{x, y, z});

  const auto vector = serialize_from<int3>("vector3.binary");
  EXPECT_EQ(x, vector.x);
  EXPECT_EQ(y, vector.y);
  EXPECT_EQ(z, vector.z);
}