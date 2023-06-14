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

#include "centurion/system.hpp"
#include "core_mocks.hpp"

extern "C" {
FAKE_VOID_FUNC(SDL_UnloadObject, void*)
FAKE_VALUE_FUNC(void*, SDL_LoadObject, const char*)
FAKE_VALUE_FUNC(void*, SDL_LoadFunction, void*, const char*)
}

class SharedObjectTest : public testing::Test {
 public:
  void SetUp() override
  {
    mocks::reset_core();
    RESET_FAKE(SDL_UnloadObject)
    RESET_FAKE(SDL_LoadObject)
    RESET_FAKE(SDL_LoadFunction)
  }

  cen::shared_object object;
};

TEST_F(SharedObjectTest, LoadFunction)
{
  using namespace std::string_literals;
  const auto name = "foo"s;

  auto* ptr [[maybe_unused]] = object.load_function<void(int, float)>(name);

  ASSERT_EQ(1u, SDL_LoadFunction_fake.call_count);
  ASSERT_EQ(name, SDL_LoadFunction_fake.arg1_val);
}
