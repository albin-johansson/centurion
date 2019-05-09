#include <pch.h>

TEST(Rectangle, ctor_exceptions) {
  // width, height
  EXPECT_THROW(Rectangle(1, 0), inv_arg);
  EXPECT_THROW(Rectangle(0, 1), inv_arg);

  // x, y, width and height
  EXPECT_THROW(Rectangle(0, 0, 0, 1), inv_arg);
  EXPECT_THROW(Rectangle(0, 0, 1, 0), inv_arg);
}

TEST(Rectangle, setters) {
  int initialX = 125;
  int initialY = 0;
  Rectangle rect = Rectangle(initialX, initialY, 10, 10);

  int newX = 1249512;
  int newY = -1246;
  rect.SetX(newX);
  rect.SetY(newY);

  EXPECT_EQ(rect.GetX(), newX);
  EXPECT_EQ(rect.GetY(), newY);
}

TEST(Rectangle, intersects) {
  Rectangle rect1 = Rectangle(0, 0, 10, 10);
  Rectangle rect2 = Rectangle(rect1.GetMaxX() - 1, 0, 10, 10);
  EXPECT_TRUE(rect1.Intersects(rect2));
  EXPECT_TRUE(rect2.Intersects(rect1));

  Rectangle rect3 = Rectangle(0, 0, 10, 10);
  Rectangle rect4 = Rectangle(rect3.GetMaxX() + 1, 0, 10, 10);
  EXPECT_FALSE(rect3.Intersects(rect4));
  EXPECT_FALSE(rect4.Intersects(rect3));

  Rectangle rect5 = Rectangle(0, 0, 10, 10);
  EXPECT_NO_THROW(rect5.Intersects(rect5));
  EXPECT_TRUE(rect5.Intersects(rect5));
}

TEST(Rectangle, contains) {
  Rectangle rect = Rectangle(0, 0, 10, 10);

  int centerX = rect.GetX() + (rect.GetWidth() / 2);
  int centerY = rect.GetY() + (rect.GetHeight() / 2);
  Point centerPoint = Point(centerX, centerY);
  EXPECT_TRUE(rect.Contains(centerPoint));
  EXPECT_TRUE(rect.Contains(centerX, centerY));

  int edgeX = rect.GetMaxX() - 1;
  int edgeY = rect.GetMaxY() - 1;
  Point edgePoint = Point(edgeX, edgeY);
  EXPECT_TRUE(rect.Contains(edgePoint));
  EXPECT_TRUE(rect.Contains(edgeX, edgeY));

  int outsideX = rect.GetMaxX() + 123125;
  int outsideY = rect.GetY() - 10231259;
  Point outsidePoint = Point(outsideX, outsideY);
  EXPECT_FALSE(rect.Contains(outsidePoint));
  EXPECT_FALSE(rect.Contains(outsideX, outsideY));
}

TEST(Rectangle, getters) {
  int x = -12480;
  int y = 12914;
  int width = 2412;
  int height = 129404;
  Rectangle rect = Rectangle(x, y, width, height);

  EXPECT_EQ(rect.GetX(), x);
  EXPECT_EQ(rect.GetY(), y);
  EXPECT_EQ(rect.GetWidth(), width);
  EXPECT_EQ(rect.GetHeight(), height);

  int maxX = x + width;
  int maxY = y + height;
  EXPECT_EQ(rect.GetMaxX(), maxX);
  EXPECT_EQ(rect.GetMaxY(), maxY);

  SDL_Rect sdlVersion = rect.GetSDLVersion();
  EXPECT_EQ(sdlVersion.x, rect.GetX());
  EXPECT_EQ(sdlVersion.y, rect.GetY());
  EXPECT_EQ(sdlVersion.w, rect.GetWidth());
  EXPECT_EQ(sdlVersion.h, rect.GetHeight());
}

TEST(Rectangle, smart_pointers) {
  int x = 129859;
  int y = -1219950;
  int w = 87;
  int h = 619;

  auto unique1 = Rectangle::CreateUnique(x, y, w, h);
  auto unique2 = Rectangle::CreateUnique(w, h);
  EXPECT_NE(unique1, nullptr);

  auto shared1 = Rectangle::CreateShared(x, y, w, h);
  auto shared2 = Rectangle::CreateShared(w, h);
  EXPECT_NE(shared1, nullptr);
  EXPECT_NE(shared2, nullptr);
}