#include <SDL.h>
#undef main  // SDL is unhappy without this (it wants to use its own main)

#include <fff.h>
#include <gtest/gtest.h>

DEFINE_FFF_GLOBALS

int main(int argc, char* argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}