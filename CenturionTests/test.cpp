#include "pch.h"

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);

  Centurion::Init();
  int i = RUN_ALL_TESTS();
  Centurion::Close();

  return i;
}