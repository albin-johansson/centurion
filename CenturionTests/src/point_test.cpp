#include <pch.h>

TEST(PointTest, defaults) {
  Point point;
  EXPECT_EQ(point.GetX(), 0);
  EXPECT_EQ(point.GetY(), 0);
}

TEST(PointTest, setters) {
  Point point;

  int x = 1295012;
  int y = -12499601;

  point.SetX(x);
  point.SetY(y);

  EXPECT_EQ(point.GetX(), x);
  EXPECT_EQ(point.GetY(), y);
}

TEST(PointTest, getters) {
  int x = 12395;
  int y = 91285;

  Point point = Point(x, y);
  EXPECT_EQ(point.GetX(), x);
  EXPECT_EQ(point.GetY(), y);

  SDL_Point sdlPoint = point.GetSDLVersion();
  EXPECT_EQ(sdlPoint.x, point.GetX());
  EXPECT_EQ(sdlPoint.y, point.GetY());
}