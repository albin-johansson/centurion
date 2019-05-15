#include <pch.h>

class FontTest : public testing::Test {
 protected:
  static constexpr int SIZE = 12;
  Font_sptr font;

  static void SetUpTestCase() {}

  static void TearDownTestCase() {}

  void SetUp() override {
    font = Font::CreateShared("resources/type_writer.ttf", SIZE);
  }

  void TearDown() override { font.reset(); }
};

TEST_F(FontTest, ResetStyle) {
  font->ResetStyle();
  EXPECT_FALSE(font->IsBold());
  EXPECT_FALSE(font->IsItalic());
  EXPECT_FALSE(font->IsStrikethrough());
  EXPECT_FALSE(font->IsUnderlined());
}

TEST_F(FontTest, SetStyle) {
  font->SetStyle(TTF_STYLE_BOLD);
  EXPECT_TRUE(font->IsBold());

  font->ResetStyle();
  font->SetStyle(TTF_STYLE_ITALIC);
  EXPECT_TRUE(font->IsItalic());

  font->ResetStyle();
  font->SetStyle(TTF_STYLE_STRIKETHROUGH);
  EXPECT_TRUE(font->IsStrikethrough());

  font->ResetStyle();
  font->SetStyle(TTF_STYLE_UNDERLINE);
  EXPECT_TRUE(font->IsUnderlined());

  font->ResetStyle();
  font->SetStyle(TTF_STYLE_BOLD | TTF_STYLE_ITALIC);
  EXPECT_TRUE(font->IsBold());
  EXPECT_TRUE(font->IsItalic());
}

TEST_F(FontTest, SetBold) {
  font->SetBold(true);
  EXPECT_TRUE(font->IsBold());

  font->SetBold(false);
  EXPECT_FALSE(font->IsBold());
}

TEST_F(FontTest, SetItalic) {
  font->SetItalic(true);
  EXPECT_TRUE(font->IsItalic());

  font->SetItalic(false);
  EXPECT_FALSE(font->IsItalic());
}

TEST_F(FontTest, SetUnderlined) {
  font->SetUnderlined(true);
  EXPECT_TRUE(font->IsUnderlined());

  font->SetUnderlined(false);
  EXPECT_FALSE(font->IsUnderlined());
}

TEST_F(FontTest, SetStrikethrough) {
  font->SetStrikethrough(true);
  EXPECT_TRUE(font->IsStrikethrough());

  font->SetStrikethrough(false);
  EXPECT_FALSE(font->IsStrikethrough());
}

TEST_F(FontTest, SetOutlined) {
  font->SetOutlined(true);
  EXPECT_TRUE(font->IsOutlined());

  font->SetOutlined(false);
  EXPECT_FALSE(font->IsOutlined());
}

TEST_F(FontTest, GetSDLVersion) {
  TTF_Font* sdlFont = font->GetSDLVersion();
  EXPECT_NE(nullptr, sdlFont);
}

TEST_F(FontTest, GetSize) { EXPECT_EQ(SIZE, font->GetSize()); }

TEST_F(FontTest, GetStyleMask) {
  int mask = TTF_STYLE_BOLD | TTF_STYLE_ITALIC;
  font->SetStyle(mask);
  EXPECT_EQ(mask, font->GetStyleMask());
}