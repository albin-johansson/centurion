#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using centurion::Centurion;
using centurion::Rectangle;
using centurion::Point;

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
			Rectangle rect = Rectangle(w, h);
			Assert::AreEqual(w, rect.getWidth());
			Assert::AreEqual(h, rect.getHeight());
		}

		TEST_METHOD(ConstructorTest2)
		{
			int x = -27;
			int y = 54;
			int w = 812;
			int h = 362;
			Rectangle rect = Rectangle(x, y, w, h);

			Assert::AreEqual(x, rect.getX());
			Assert::AreEqual(y, rect.getY());
			Assert::AreEqual(w, rect.getWidth());
			Assert::AreEqual(h, rect.getHeight());
		}

		TEST_METHOD(SetLocation)
		{
			Rectangle rect = Rectangle(44, 177, 10, 10);
			int x = 148;
			int y = 93;
			rect.setLocation(x, y);

			Assert::AreEqual(x, rect.getX());
			Assert::AreEqual(y, rect.getY());
		}

		TEST_METHOD(SetX)
		{
			Rectangle rect = Rectangle(0, 0, 10, 10);
			int x = 812;
			rect.setX(x);
			Assert::AreEqual(x, rect.getX());
		}

		TEST_METHOD(SetY)
		{
			Rectangle rect = Rectangle(0, 0, 10, 10);
			int y = -428;
			rect.setY(y);
			Assert::AreEqual(y, rect.getY());
		}

		TEST_METHOD(Intersects)
		{
			Rectangle rect1 = Rectangle(0, 0, 10, 10);
			Rectangle rect2 = Rectangle(10, 0, 10, 10);
			Assert::IsFalse(rect1.intersects(rect2));

			Rectangle rect3 = Rectangle(5, 0, 10, 10);
			Rectangle rect4 = Rectangle(8, 3, 10, 10);
			Assert::IsTrue(rect3.intersects(rect4));
		}

		TEST_METHOD(Contains1)
		{
			Rectangle rect = Rectangle(0, 0, 10, 10);
			Assert::IsTrue(rect.contains(5, 5));
			Assert::IsFalse(rect.contains(1239, 123));
		}

		TEST_METHOD(Contains2)
		{
			Rectangle rect = Rectangle(0, 0, 10, 10);

			Point point1 = Point(4, 8);
			Assert::IsTrue(rect.contains(point1));

			Point point2 = Point(235, -124);
			Assert::IsFalse(rect.contains(point2));
		}

		TEST_METHOD(GetX)
		{
			int x = 420;
			Rectangle rect = Rectangle(x, 0, 10, 10);
			Assert::AreEqual(x, rect.getX());
		}

		TEST_METHOD(GetY)
		{
			int y = 281;
			Rectangle rect = Rectangle(0, y, 10, 10);
			Assert::AreEqual(y, rect.getY());
		}

		TEST_METHOD(GetWidth)
		{
			int w = 1246;
			Rectangle rect = Rectangle(0, 0, w, 10);
			Assert::AreEqual(w, rect.getWidth());
		}

		TEST_METHOD(GetHeight)
		{
			int h = 987;
			Rectangle rect = Rectangle(0, 0, 10, h);
			Assert::AreEqual(h, rect.getHeight());
		}

		TEST_METHOD(CreateSDLRect)
		{
			int x = 123;
			int y = 456;
			int w = 789;
			int h = 912;
			Rectangle rect = Rectangle(x, y, w, h);
			SDL_Rect sdlRect = rect.createSDLRect();

			Assert::AreEqual(x, sdlRect.x);
			Assert::AreEqual(y, sdlRect.y);
			Assert::AreEqual(w, sdlRect.w);
			Assert::AreEqual(h, sdlRect.h);
		}
	};
}