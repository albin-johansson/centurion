#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using centurion::CTN_Color;
using centurion::Centurion;

namespace CenturionTest
{
	TEST_CLASS(ColorTest)
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

		TEST_METHOD(getRed)
		{
			int r = 128;
			CTN_Color c = CTN_Color(r, 0, 0, 0);
			Assert::AreEqual(r, (int) c.getRed());
		}
		
		TEST_METHOD(getGreen)
		{
			int g = 27;
			CTN_Color c = CTN_Color(0, g, 0, 0);
			Assert::AreEqual(g, (int) c.getGreen());
		}

		TEST_METHOD(getBlue)
		{
			int b = 27;
			CTN_Color c = CTN_Color(0, 0, b, 0);
			Assert::AreEqual(b, (int) c.getBlue());
		}

		TEST_METHOD(getAlpha)
		{
			int a = 219;
			CTN_Color c = CTN_Color(0, 0, 0, a);
			Assert::AreEqual(a, (int) c.getAlpha());
		}

		TEST_METHOD(Constants)
		{
			Assert::AreEqual(255, (int) CTN_Color::MAX_VAL);
			Assert::AreEqual(0, (int) CTN_Color::MIN_VAL);

			CTN_Color red = CTN_Color(255, 0, 0, 255);
			CTN_Color redConst = CTN_Color::RED;
			compare(red, redConst);

			CTN_Color green = CTN_Color(0, 255, 0, 255);
			CTN_Color greenConst = CTN_Color::GREEN;
			compare(green, greenConst);

			CTN_Color blue = CTN_Color(0, 0, 255, 255);
			CTN_Color blueConst = CTN_Color::BLUE;
			compare(blue, blueConst);

			CTN_Color white = CTN_Color(255, 255, 255, 255);
			CTN_Color whiteConst = CTN_Color::WHITE;
			compare(white, whiteConst);

			CTN_Color black = CTN_Color(0, 0, 0, 255);
			CTN_Color blackConst = CTN_Color::BLACK;
			compare(black, blackConst);
		}

		void compare(CTN_Color& c1, CTN_Color& c2)
		{
			Assert::AreEqual((int) c1.getRed(), (int) c2.getRed());
			Assert::AreEqual((int) c1.getGreen(), (int) c2.getGreen());
			Assert::AreEqual((int) c1.getBlue(), (int) c2.getBlue());
			Assert::AreEqual((int) c1.getAlpha(), (int) c2.getAlpha());
		}
	};
}