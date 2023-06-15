/*
 * MIT License
 *
 * Copyright (c) 2019-2023 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <gtest/gtest.h>

#include <iostream>  // cout
#include <memory>    // unique_ptr

#include "centurion/video/renderer.hpp"
#include "centurion/video/window.hpp"

class RendererHandleTest : public testing::Test {
 protected:
  [[maybe_unused]] static void SetUpTestSuite()
  {
    mWindow = std::make_unique<cen::window>();
    mRenderer = std::make_unique<cen::renderer>(mWindow->make_renderer());
  }

  [[maybe_unused]] static void TearDownTestSuite()
  {
    mRenderer.reset();
    mWindow.reset();
  }

  inline static std::unique_ptr<cen::window> mWindow;
  inline static std::unique_ptr<cen::renderer> mRenderer;
};

TEST_F(RendererHandleTest, RawPointerConstructor)
{
  {  // Null pointer
    cen::renderer_handle handle {nullptr};
    ASSERT_FALSE(handle);
    ASSERT_FALSE(handle.get());
  }

  {  // Valid pointer
    const cen::renderer_handle handle {mRenderer->get()};

    ASSERT_TRUE(handle);
    ASSERT_TRUE(handle.get());
  }
}

TEST_F(RendererHandleTest, FromOwningRenderer)
{
  const cen::renderer_handle handle {*mRenderer};

  ASSERT_TRUE(handle);
  ASSERT_TRUE(handle.get());
}

TEST_F(RendererHandleTest, StreamOperator)
{
  const cen::renderer_handle handle {*mRenderer};
  std::cout << handle << '\n';
}
