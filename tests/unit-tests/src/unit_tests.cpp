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

#include <exception>  // exception
#include <cstdlib>    // EXIT_FAILURE
#include <iostream>   // cerr

#include <gtest/gtest.h>

#include <centurion/centurion.hpp>

auto main(int argc, char* argv[]) -> int
{
  try {
    cen::SDLMixerConfig mixer_cfg = {};
    mixer_cfg.flags = MIX_INIT_MP3;

    const cen::SDL sdl;
    const cen::SDLImage sdl_image {IMG_INIT_PNG};
    const cen::SDLMixer sdl_mixer {mixer_cfg};
    const cen::SDLTTF sdl_ttf;

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
  }
  catch (const std::exception& e) {
    std::cerr << "Unit tests threw exception: " << e.what() << '\n';
    return EXIT_FAILURE;
  }
}