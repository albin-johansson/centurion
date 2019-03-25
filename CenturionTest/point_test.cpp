#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using centurion::Centurion;
using centurion::Point;

namespace CenturionTest
{
	TEST_CLASS(PointTest)
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

		TEST_METHOD(Constructor)
		{
			int x = 15;
			int y = 118;
			Point p = Point(x, y);

			Assert::AreEqual(x, p.GetX());
			Assert::AreEqual(y, p.GetY());
		}

		TEST_METHOD(SetLocation)
		{
			Point p = Point(0, 0);
			int x = 8502;
			int y = 1202;
			p.SetLocation(x, y);

			Assert::AreEqual(x, p.GetX());
			Assert::AreEqual(y, p.GetY());
		}

		TEST_METHOD(SetX)
		{
			Point p = Point(0, 0);
			int x = 1250;
			p.SetX(x);
			Assert::AreEqual(x, p.GetX());
		}

		TEST_METHOD(SetY)
		{
			Point p = Point(0, 0);
			int y = 9386;
			p.SetY(y);
			Assert::AreEqual(y, p.GetY());
		}

		TEST_METHOD(GetX)
		{
			int x = 48301;
			Point p = Point(x, 0);
			Assert::AreEqual(x, p.GetX());
		}

		TEST_METHOD(GetY)
		{
			int y = 12859;
			Point p = Point(0, y);
			Assert::AreEqual(y, p.GetY());
		}
	};
}