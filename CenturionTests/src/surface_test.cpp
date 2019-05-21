#include "pch.h"

class SurfaceTest : public testing::Test {
 protected:
  Surface* surface = nullptr;
  int width;
  int height;

  static void SetUpTestCase() {}

  static void TearDownTestCase() {}

  void SetUp() override {
    SDL_Surface* surf = IMG_Load("resources/test.png");
    width = surf->w;
    height = surf->h;
    surface = new Surface(surf);
  }

  void TearDown() override { delete surface; }
};

TEST_F(SurfaceTest, Ctor) { EXPECT_THROW(Surface(nullptr), inv_arg); }

TEST_F(SurfaceTest, SetAlpha) {
  int alpha = 184;
  surface->SetAlpha(alpha);
  EXPECT_EQ(surface->GetAlpha(), alpha);
}

TEST_F(SurfaceTest, SetBlendMode) {
  SDL_BlendMode bmode = SDL_BLENDMODE_BLEND;
  surface->SetBlendMode(bmode);
  EXPECT_EQ(surface->GetBlendMode(), bmode);
}

TEST_F(SurfaceTest, SetColorModulation) {
  int red = 125;
  int green = 89;
  int blue = 207;
  Color color = Color(red, green, blue);
  surface->SetColorModulation(color);

  Color result = surface->GetColorModulation();
  EXPECT_EQ(result.GetRed(), red);
  EXPECT_EQ(result.GetGreen(), green);
  EXPECT_EQ(result.GetBlue(), blue);
}

TEST_F(SurfaceTest, Duplicate) {
  Surface_uptr copy = surface->Duplicate();

  EXPECT_EQ(copy->GetAlpha(), surface->GetAlpha());
  EXPECT_EQ(copy->GetBlendMode(), surface->GetBlendMode());

  Color copyModColor = copy->GetColorModulation();
  Color originalModColor = surface->GetColorModulation();

  EXPECT_TRUE(copyModColor.Equals(originalModColor));
  EXPECT_TRUE(originalModColor.Equals(copyModColor));

  EXPECT_EQ(copy->GetWidth(), surface->GetWidth());
  EXPECT_EQ(copy->GetHeight(), surface->GetHeight());
}

TEST_F(SurfaceTest, Lock) {
  surface->Lock();
  EXPECT_TRUE(surface->IsLocked());
  SDL_Surface* sdlSurface = surface->GetSDLVersion();
  EXPECT_TRUE(sdlSurface->locked);
}

TEST_F(SurfaceTest, Unlock) {
  surface->Unlock();
  EXPECT_FALSE(surface->IsLocked());
  SDL_Surface* sdlSurface = surface->GetSDLVersion();
  EXPECT_FALSE(sdlSurface->locked);
}

TEST_F(SurfaceTest, GetWidth) { EXPECT_EQ(width, surface->GetWidth()); }

TEST_F(SurfaceTest, GetHeight) { EXPECT_EQ(height, surface->GetHeight()); }

TEST_F(SurfaceTest, GetSDLVersion) {
  SDL_Surface* sdlVersion = surface->GetSDLVersion();
  ASSERT_NE(sdlVersion, nullptr);
  EXPECT_EQ(sdlVersion->w, surface->GetWidth());
  EXPECT_EQ(sdlVersion->h, surface->GetHeight());
}