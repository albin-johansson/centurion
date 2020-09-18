#include "point.hpp"

#include <catch.hpp>
#include <iostream>

#include "log.hpp"

TEST_CASE("point::to_string", "[point]")
{
  const cen::ipoint ip{123, 456};
  cen::log::info(cen::log::category::test, "%s", cen::to_string(ip).c_str());

  const cen::fpoint fp{12.3f, 45.6f};
  cen::log::info(cen::log::category::test, "%s", cen::to_string(fp).c_str());

  std::cout << "COUT: " << fp << '\n';
  std::cout << "COUT: " << fp << '\n';
}

TEST_CASE("point::distance", "[point]")
{
  SECTION("Unit x-step")
  {
    const cen::ipoint a{0, 123};
    const cen::ipoint b{1, 123};

    CHECK(cen::distance(a, b) == 1);
    CHECK(cen::distance(b, a) == 1);
  }

  SECTION("Unit y-step")
  {
    const cen::ipoint a{42, 0};
    const cen::ipoint b{42, 1};

    CHECK(cen::distance(a, b) == 1);
    CHECK(cen::distance(b, a) == 1);
  }

  SECTION("Non-trivial distance")
  {
    const cen::fpoint a{189.2f, 86.9f};
    const cen::fpoint b{66.5f, 36.6f};

    const auto expected =
        std::sqrt(std::abs(a.x() - b.x()) + std::abs(a.y() - b.y()));

    CHECK(cen::distance(a, b) == expected);
    CHECK(cen::distance(b, a) == expected);
  }
}

TEST_CASE("point::operator==", "[point]")
{
  SECTION("Self")
  {
    const cen::ipoint ip{};
    const cen::fpoint fp{};
    CHECK(ip == ip);
    CHECK(fp == fp);
  }

  SECTION("Not equal")
  {
    SECTION("ipoint")
    {
      const cen::ipoint fst{839, 902};
      const cen::ipoint snd{73483, 1289};
      CHECK_FALSE(fst == snd);
      CHECK_FALSE(snd == fst);
    }

    SECTION("fpoint")
    {
      const cen::fpoint fst{531.5f, 8313.4f};
      const cen::fpoint snd{34.2f, 173.3f};
      CHECK_FALSE(fst == snd);
      CHECK_FALSE(snd == fst);
    }
  }

  SECTION("Equal")
  {
    SECTION("ipoint")
    {
      const cen::ipoint fst{883, 922};
      const cen::ipoint snd{fst};
      CHECK(fst == snd);
      CHECK(snd == fst);
      CHECK_FALSE(fst != snd);
      CHECK_FALSE(snd != fst);
    }

    SECTION("fpoint")
    {
      const cen::fpoint fst{211.5f, 823.1f};
      const cen::fpoint snd{fst};
      CHECK(fst == snd);
      CHECK(snd == fst);
      CHECK_FALSE(fst != snd);
      CHECK_FALSE(snd != fst);
    }
  }
}

TEST_CASE("point::operator!=", "[point]")
{
  SECTION("Self")
  {
    const cen::ipoint ip{};
    const cen::fpoint fp{};
    CHECK_FALSE(ip != ip);
    CHECK_FALSE(fp != fp);
  }

  SECTION("Not equal")
  {
    SECTION("ipoint")
    {
      const cen::ipoint fst{1234, 12412421};
      const cen::ipoint snd{4345, 7712};
      CHECK(fst != snd);
      CHECK(snd != fst);
    }

    SECTION("fpoint")
    {
      const cen::fpoint fst{8392.5f, 12452.4f};
      const cen::fpoint snd{5236.2f, 321.3f};
      CHECK(fst != snd);
      CHECK(snd != fst);
    }
  }

  SECTION("Equal")
  {
    SECTION("ipoint")
    {
      const cen::ipoint fst{883, 922};
      const cen::ipoint snd{fst};
      CHECK_FALSE(fst != snd);
      CHECK_FALSE(snd != fst);
    }

    SECTION("fpoint")
    {
      const cen::fpoint fst{211.5f, 823.1f};
      const cen::fpoint snd{fst};
      CHECK_FALSE(fst != snd);
      CHECK_FALSE(snd != fst);
    }
  }
}

TEST_CASE("point::operator+", "[point]")
{
  SECTION("ipoint")
  {
    const cen::ipoint fst{738, 912};
    const cen::ipoint snd{123, 423};

    const auto expectedX = fst.x() + snd.x();
    const auto expectedY = fst.y() + snd.y();

    const auto fstSnd = fst + snd;
    CHECK(fstSnd.x() == expectedX);
    CHECK(fstSnd.y() == expectedY);

    const auto sndFst = snd + fst;
    CHECK(sndFst.x() == expectedX);
    CHECK(sndFst.y() == expectedY);
  }

  SECTION("fpoint")
  {
    const cen::fpoint fst{62.4f, 381.3f};
    const cen::fpoint snd{779.3f, 819.3f};

    const auto expectedX = fst.x() + snd.x();
    const auto expectedY = fst.y() + snd.y();

    const auto fstSnd = fst + snd;
    CHECK(fstSnd.x() == expectedX);
    CHECK(fstSnd.y() == expectedY);

    const auto sndFst = snd + fst;
    CHECK(sndFst.x() == expectedX);
    CHECK(sndFst.y() == expectedY);
  }
}

TEST_CASE("point::operator-", "[point]")
{
  const cen::ipoint fst{673, 123};
  const cen::ipoint snd{-547, 451};

  CHECK((fst - snd) != (snd - fst));

  SECTION("fst - snd")
  {
    const cen::ipoint diff = fst - snd;

    CHECK(diff.x() == fst.x() - snd.x());
    CHECK(diff.y() == fst.y() - snd.y());
  }

  SECTION("snd - fst")
  {
    const cen::ipoint diff = snd - fst;

    CHECK(diff.x() == snd.x() - fst.x());
    CHECK(diff.y() == snd.y() - fst.y());
  }
}

TEST_CASE("Conversions")
{
  SECTION("ipoint -> fpoint")
  {
    const cen::ipoint from{684, 912};
    const auto to = cen::cast<cen::fpoint>(from);

    CHECK(to.x() == static_cast<float>(from.x()));
    CHECK(to.y() == static_cast<float>(from.y()));
  }

  SECTION("fpoint -> ipoint")
  {
    const cen::fpoint from{58.8f, 123.4f};
    const auto to = cen::cast<cen::ipoint>(from);

    CHECK(to.x() == static_cast<int>(from.x()));
    CHECK(to.y() == static_cast<int>(from.y()));
  }

  SECTION("ipoint -> const SDL_Point*")
  {
    cen::ipoint point{843, 9123};

    SECTION("Non-const")
    {
      auto* ptr = static_cast<SDL_Point*>(point);
      CHECK(point.x() == ptr->x);
      CHECK(point.y() == ptr->y);
    }

    SECTION("Const")
    {
      const auto* ptr = static_cast<const SDL_Point*>(point);
      CHECK(point.x() == ptr->x);
      CHECK(point.y() == ptr->y);
    }
  }

  SECTION("fpoint -> const SDL_FPoint*")
  {
    cen::fpoint point{3813.3f, 892.5f};

    SECTION("Non-const")
    {
      auto* ptr = static_cast<SDL_FPoint*>(point);
      CHECK(point.x() == ptr->x);
      CHECK(point.y() == ptr->y);
    }

    SECTION("Const")
    {
      const auto* ptr = static_cast<const SDL_FPoint*>(point);
      CHECK(point.x() == ptr->x);
      CHECK(point.y() == ptr->y);
    }
  }
}

TEST_CASE("point::get", "[point]")
{
  SECTION("ipoint")
  {
    const cen::ipoint point{393, 934};
    const auto sdl = point.get();

    CHECK(point.x() == sdl.x);
    CHECK(point.y() == sdl.y);
  }

  SECTION("fpoint")
  {
    const cen::fpoint point{3923.3f, 7718.1f};
    const auto sdl = point.get();

    CHECK(point.x() == sdl.x);
    CHECK(point.y() == sdl.y);
  }
}
