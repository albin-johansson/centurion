#include "vector3.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout

#include "log.hpp"

using fvector3 = cen::vector3<float>;
using ivector3 = cen::vector3<int>;

TEST(Vector3, Defaults)
{
  const fvector3 vec;
  EXPECT_EQ(0, vec.x);
  EXPECT_EQ(0, vec.y);
  EXPECT_EQ(0, vec.z);
}

TEST(Vector3, CastOperator)
{
  {  // int -> float
    const ivector3 src{12, 34, 56};
    const auto result = static_cast<fvector3>(src);
    EXPECT_EQ(static_cast<float>(src.x), result.x);
    EXPECT_EQ(static_cast<float>(src.y), result.y);
    EXPECT_EQ(static_cast<float>(src.z), result.z);
  }

  {  // float -> int
    const fvector3 src{12.3f, 45.6f, 7.89f};
    const auto result = static_cast<ivector3>(src);
    EXPECT_EQ(static_cast<int>(src.x), result.x);
    EXPECT_EQ(static_cast<int>(src.y), result.y);
    EXPECT_EQ(static_cast<int>(src.z), result.z);
  }
}

TEST(Vector3, StreamOperator)
{
  const fvector3 vec{12.3f, 45.6f};
  std::cout << "COUT: " << vec << '\n';
}

TEST(Vector3, ToString)
{
  const fvector3 vec{12.3f, 45.6f};
  cen::log::put(cen::to_string(vec));
}

TEST(Vector3, EqualityOperator)
{
  {  // Reflexivity
    const fvector3 vec{12.3f, 45.6f};
    EXPECT_EQ(vec, vec);
  }

  {  // Identical vectors
    const fvector3 vec{12.3f, 45.6f};
    const fvector3 copy{vec};
    EXPECT_EQ(vec, copy);
    EXPECT_EQ(copy, vec);
  }

  {  // Different vectors
    const fvector3 fst{27.7f, 42.6f};
    const fvector3 snd{954.3f, 243.2f};
    EXPECT_FALSE(fst == snd);
    EXPECT_FALSE(snd == fst);
  }
}

TEST(Vector3, InequalityOperator)
{
  {  // Self
    const fvector3 vec{12.3f, 45.6f};
    EXPECT_FALSE(vec != vec);
  }

  {  // Identical vectors
    const fvector3 vec{12.3f, 45.6f};
    const fvector3 copy{vec};
    EXPECT_FALSE(vec != copy);
    EXPECT_FALSE(copy != vec);
  }

  {  // Different vectors
    const fvector3 fst{27.7f, 42.6f};
    const fvector3 snd{954.3f, 243.2f};
    EXPECT_NE(fst, snd);
    EXPECT_NE(snd, fst);
  }
}
