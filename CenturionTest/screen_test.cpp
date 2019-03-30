#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using centurion::Centurion;
using centurion::tools::Screen;

namespace CenturionTest {
TEST_CLASS(ScreenTest){public : TEST_CLASS_INITIALIZE(Init){Centurion::Init();
}

TEST_CLASS_CLEANUP(cleanup) { Centurion::Close(); }

TEST_METHOD(GetWidth) {
  int w = Screen::GetWidth();
  int expected = 1920;
  Assert::AreEqual(expected, w);
}

TEST_METHOD(GetHeight) {
  int h = Screen::GetHeight();
  int expected = 1080;
  Assert::AreEqual(expected, h);
}
}
;
}