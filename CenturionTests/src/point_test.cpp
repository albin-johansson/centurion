#include <pch.h>

TEST(Point, defaults) {
  Point p;
  EXPECT_EQ(p.GetX(), 0);
  EXPECT_EQ(p.GetY(), 0);
}

TEST(Point, setters) {
  Point p = Point(0, 0);

  int x = 1295012;
  int y = -12499601;

  p.SetX(x);
  p.SetY(y);

  EXPECT_EQ(p.GetX(), x);
  EXPECT_EQ(p.GetY(), y);
}

TEST(Point, getters) {
  int x = 12395;
  int y = 91285;

  Point point = Point(x, y);
  EXPECT_EQ(point.GetX(), x);
  EXPECT_EQ(point.GetY(), y);

  SDL_Point sdlPoint = point.GetSDLVersion();
  EXPECT_EQ(sdlPoint.x, point.GetX());
  EXPECT_EQ(sdlPoint.y, point.GetY());
}