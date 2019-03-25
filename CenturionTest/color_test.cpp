#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using centurion::Color;
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
			Color c = Color(r, 0, 0, 0);
			Assert::AreEqual(r, (int) c.getRed());
		}
		
		TEST_METHOD(getGreen)
		{
			int g = 27;
			Color c = Color(0, g, 0, 0);
			Assert::AreEqual(g, (int) c.getGreen());
		}

		TEST_METHOD(getBlue)
		{
			int b = 27;
			Color c = Color(0, 0, b, 0);
			Assert::AreEqual(b, (int) c.getBlue());
		}

		TEST_METHOD(getAlpha)
		{
			int a = 219;
			Color c = Color(0, 0, 0, a);
			Assert::AreEqual(a, (int) c.getAlpha());
		}

		TEST_METHOD(Constants)
		{
			Assert::AreEqual(255, (int) Color::MAX_VAL);
			Assert::AreEqual(0, (int) Color::MIN_VAL);

			Color red = Color(255, 0, 0, 255);
			Color redConst = Color::RED;
			compare(red, redConst);

			Color green = Color(0, 255, 0, 255);
			Color greenConst = Color::GREEN;
			compare(green, greenConst);

			Color blue = Color(0, 0, 255, 255);
			Color blueConst = Color::BLUE;
			compare(blue, blueConst);

			Color white = Color(255, 255, 255, 255);
			Color whiteConst = Color::WHITE;
			compare(white, whiteConst);

			Color black = Color(0, 0, 0, 255);
			Color blackConst = Color::BLACK;
			compare(black, blackConst);
		}

		void compare(Color& c1, Color& c2)
		{
			Assert::AreEqual((int) c1.getRed(), (int) c2.getRed());
			Assert::AreEqual((int) c1.getGreen(), (int) c2.getGreen());
			Assert::AreEqual((int) c1.getBlue(), (int) c2.getBlue());
			Assert::AreEqual((int) c1.getAlpha(), (int) c2.getAlpha());
		}
	};
}