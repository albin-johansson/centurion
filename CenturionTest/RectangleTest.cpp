#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using centurion::Centurion;
using centurion::CTN_Rectangle;
using centurion::CTN_Point;

namespace CenturionTest
{
	TEST_CLASS(RectangleTest)
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

		TEST_METHOD(ConstructorTest1)
		{
			int w = 127;
			int h = 81;
			CTN_Rectangle rect = CTN_Rectangle(w, h);
			Assert::AreEqual(w, rect.getWidth());
			Assert::AreEqual(h, rect.getHeight());
		}

		TEST_METHOD(ConstructorTest2)
		{
			int x = -27;
			int y = 54;
			int w = 812;
			int h = 362;
			CTN_Rectangle rect = CTN_Rectangle(x, y, w, h);

			Assert::AreEqual(x, rect.getX());
			Assert::AreEqual(y, rect.getY());
			Assert::AreEqual(w, rect.getWidth());
			Assert::AreEqual(h, rect.getHeight());
		}

		TEST_METHOD(SetLocation)
		{
			CTN_Rectangle rect = CTN_Rectangle(44, 177, 10, 10);
			int x = 148;
			int y = 93;
			rect.setLocation(x, y);

			Assert::AreEqual(x, rect.getX());
			Assert::AreEqual(y, rect.getY());
		}

		TEST_METHOD(SetX)
		{
			CTN_Rectangle rect = CTN_Rectangle(0, 0, 10, 10);
			int x = 812;
			rect.setX(x);
			Assert::AreEqual(x, rect.getX());
		}

		TEST_METHOD(SetY)
		{
			CTN_Rectangle rect = CTN_Rectangle(0, 0, 10, 10);
			int y = -428;
			rect.setY(y);
			Assert::AreEqual(y, rect.getY());
		}

		TEST_METHOD(Intersects)
		{
			CTN_Rectangle rect1 = CTN_Rectangle(0, 0, 10, 10);
			CTN_Rectangle rect2 = CTN_Rectangle(10, 0, 10, 10);
			Assert::IsFalse(rect1.intersects(rect2));

			CTN_Rectangle rect3 = CTN_Rectangle(5, 0, 10, 10);
			CTN_Rectangle rect4 = CTN_Rectangle(8, 3, 10, 10);
			Assert::IsTrue(rect3.intersects(rect4));
		}

		TEST_METHOD(Contains1)
		{
			CTN_Rectangle rect = CTN_Rectangle(0, 0, 10, 10);
			Assert::IsTrue(rect.contains(5, 5));
			Assert::IsFalse(rect.contains(1239, 123));
		}

		TEST_METHOD(Contains2)
		{
			CTN_Rectangle rect = CTN_Rectangle(0, 0, 10, 10);

			CTN_Point point1 = CTN_Point(4, 8);
			Assert::IsTrue(rect.contains(point1));

			CTN_Point point2 = CTN_Point(235, -124);
			Assert::IsFalse(rect.contains(point2));
		}

		TEST_METHOD(GetX)
		{
			int x = 420;
			CTN_Rectangle rect = CTN_Rectangle(x, 0, 10, 10);
			Assert::AreEqual(x, rect.getX());
		}

		TEST_METHOD(GetY)
		{
			int y = 281;
			CTN_Rectangle rect = CTN_Rectangle(0, y, 10, 10);
			Assert::AreEqual(y, rect.getY());
		}

		TEST_METHOD(GetWidth)
		{
			int w = 1246;
			CTN_Rectangle rect = CTN_Rectangle(0, 0, w, 10);
			Assert::AreEqual(w, rect.getWidth());
		}

		TEST_METHOD(GetHeight)
		{
			int h = 987;
			CTN_Rectangle rect = CTN_Rectangle(0, 0, 10, h);
			Assert::AreEqual(h, rect.getHeight());
		}

		TEST_METHOD(CreateSDLRect)
		{
			int x = 123;
			int y = 456;
			int w = 789;
			int h = 912;
			CTN_Rectangle rect = CTN_Rectangle(x, y, w, h);
			SDL_Rect sdlRect = rect.createSDLRect();

			Assert::AreEqual(x, sdlRect.x);
			Assert::AreEqual(y, sdlRect.y);
			Assert::AreEqual(w, sdlRect.w);
			Assert::AreEqual(h, sdlRect.h);
		}
	};
}