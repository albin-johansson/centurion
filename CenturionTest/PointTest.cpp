#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using centurion::Centurion;
using centurion::Point;

namespace CenturionTest
{
	TEST_CLASS(PointTest)
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

		TEST_METHOD(Constructor)
		{
			int x = 15;
			int y = 118;
			Point p = Point(x, y);

			Assert::AreEqual(x, p.getX());
			Assert::AreEqual(y, p.getY());
		}

		TEST_METHOD(SetLocation)
		{
			Point p = Point(0, 0);
			int x = 8502;
			int y = 1202;
			p.setLocation(x, y);

			Assert::AreEqual(x, p.getX());
			Assert::AreEqual(y, p.getY());
		}

		TEST_METHOD(SetX)
		{
			Point p = Point(0, 0);
			int x = 1250;
			p.setX(x);
			Assert::AreEqual(x, p.getX());
		}

		TEST_METHOD(SetY)
		{
			Point p = Point(0, 0);
			int y = 9386;
			p.setY(y);
			Assert::AreEqual(y, p.getY());
		}

		TEST_METHOD(GetX)
		{
			int x = 48301;
			Point p = Point(x, 0);
			Assert::AreEqual(x, p.getX());
		}

		TEST_METHOD(GetY)
		{
			int y = 12859;
			Point p = Point(0, y);
			Assert::AreEqual(y, p.getY());
		}
	};
}