#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using centurion::Centurion;
using centurion::Screen;

namespace CenturionTest
{
	TEST_CLASS(ScreenTest)
	{
	public:
		TEST_CLASS_INITIALIZE(init)
		{
			Centurion::init();
		}

		TEST_CLASS_CLEANUP(cleanup)
		{
			Centurion::close();
		}

		TEST_METHOD(GetWidth)
		{
			int w = Screen::getWidth();
			int expected = 1920;
			Assert::AreEqual(expected, w);
		}

		TEST_METHOD(GetHeight)
		{
			int h = Screen::getHeight();
			int expected = 1080;
			Assert::AreEqual(expected, h);
		}
	};
}