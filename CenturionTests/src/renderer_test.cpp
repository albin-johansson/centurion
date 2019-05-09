#include <pch.h>

class RendererTest : public testing::Test {
 protected:
  static IWindow_uptr window;
  static IRenderer_sptr renderer;
  static Font_sptr font;

  static void SetUpTestCase() {
    font = Font::CreateShared("resources/type_writer.ttf", 12);
    window = Window::CreateUnique(800, 600);
    renderer = window->GetRenderer();
    window->Show();
  }

  static void TearDownTestCase() {
    window->Hide();
    font.reset();
    renderer.reset();
    window.release();
  }

  void SetUp() override {}

  void TearDown() override {}
};

IWindow_uptr RendererTest::window = nullptr;
IRenderer_sptr RendererTest::renderer = nullptr;
Font_sptr RendererTest::font = nullptr;

TEST_F(RendererTest, CreateTextureFromString) {
  renderer->SetFont(nullptr);
  EXPECT_THROW(renderer->CreateTextureFromString(""), except);
  renderer->SetFont(font);
  EXPECT_THROW(renderer->CreateTextureFromString(""), inv_arg);
}

TEST_F(RendererTest, CreateTextureFromStringShaded) {
  renderer->SetFont(nullptr);
  EXPECT_THROW(renderer->CreateTextureFromStringShaded(""), except);
  renderer->SetFont(font);
  EXPECT_THROW(renderer->CreateTextureFromStringShaded(""), inv_arg);
}

TEST_F(RendererTest, CreateTextureFromStringWrapped) {
  renderer->SetFont(nullptr);
  EXPECT_THROW(renderer->CreateTextureFromStringWrapped("", 10),
               std::exception);
  renderer->SetFont(font);
  EXPECT_THROW(renderer->CreateTextureFromStringWrapped("", 10), inv_arg);
}

TEST_F(RendererTest, CreateEmptyTexture) {
  SDL_TextureAccess access = SDL_TEXTUREACCESS_STATIC;
  EXPECT_THROW(renderer->CreateEmptyTexture(0, 10, 0, access), inv_arg);
  EXPECT_THROW(renderer->CreateEmptyTexture(10, 0, 0, access), inv_arg);
}

TEST_F(RendererTest, CreateRenderTarget) {
  EXPECT_THROW(renderer->CreateRenderTarget(0, 10), inv_arg);
  EXPECT_THROW(renderer->CreateRenderTarget(10, 0), inv_arg);
}

TEST_F(RendererTest, GetSDLVersion) {
  EXPECT_NE(renderer->GetSDLVersion(), nullptr);
}