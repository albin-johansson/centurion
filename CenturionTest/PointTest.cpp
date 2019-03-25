#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using centurion::Centurion;
using centurion::CTN_Point;

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
			CTN_Point p = CTN_Point(x, y);

			Assert::AreEqual(x, p.getX());
			Assert::AreEqual(y, p.getY());
		}

		TEST_METHOD(SetLocation)
		{
			CTN_Point p = CTN_Point(0, 0);
			int x = 8502;
			int y = 1202;
			p.setLocation(x, y);

			Assert::AreEqual(x, p.getX());
			Assert::AreEqual(y, p.getY());
		}

		TEST_METHOD(SetX)
		{
			CTN_Point p = CTN_Point(0, 0);
			int x = 1250;
			p.setX(x);
			Assert::AreEqual(x, p.getX());
		}

		TEST_METHOD(SetY)
		{
			CTN_Point p = CTN_Point(0, 0);
			int y = 9386;
			p.setY(y);
			Assert::AreEqual(y, p.getY());
		}

		TEST_METHOD(GetX)
		{
			int x = 48301;
			CTN_Point p = CTN_Point(x, 0);
			Assert::AreEqual(x, p.getX());
		}

		TEST_METHOD(GetY)
		{
			int y = 12859;
			CTN_Point p = CTN_Point(0, y);
			Assert::AreEqual(y, p.getY());
		}
	};
}