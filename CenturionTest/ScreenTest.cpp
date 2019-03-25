#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using centurion::Centurion;
using centurion::CTN_Screen;

namespace CenturionTest
{
	TEST_CLASS(ScreenTest)
	{
	public:
		TEST_CLASS_INITIALIZE(Init)
		{
			Centurion::Init();
		}

		TEST_CLASS_CLEANUP(cleanup)
		{
			Centurion::Close();
		}

		TEST_METHOD(GetWidth)
		{
			int w = CTN_Screen::getWidth();
			int expected = 1920;
			Assert::AreEqual(expected, w);
		}

		TEST_METHOD(GetHeight)
		{
			int h = CTN_Screen::getHeight();
			int expected = 1080;
			Assert::AreEqual(expected, h);
		}
	};
}