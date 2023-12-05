// Copyright (C) 2019-2023 Albin Johansson (MIT License)

#include <fff.h>
#include <gtest/gtest.h>

DEFINE_FFF_GLOBALS

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
