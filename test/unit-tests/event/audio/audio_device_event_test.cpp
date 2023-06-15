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

#include "centurion/events/audio_events.hpp"

TEST(AudioDeviceEvent, Defaults)
{
  const cen::audio_device_event event;
  ASSERT_EQ(cen::event_type::audio_device_added, event.type());
}

TEST(AudioDeviceEvent, SetWhich)
{
  cen::audio_device_event event;

  const Uint32 which = 7;
  event.set_which(which);

  ASSERT_EQ(which, event.which());
}

TEST(AudioDeviceEvent, SetCapture)
{
  cen::audio_device_event event;

  event.set_capture(true);
  ASSERT_TRUE(event.is_capture());
  ASSERT_FALSE(event.is_output());

  event.set_capture(false);
  ASSERT_FALSE(event.is_capture());
  ASSERT_TRUE(event.is_output());
}

TEST(AudioDeviceEvent, AsSDLEvent)
{
  const cen::audio_device_event event;
  const auto underlying = cen::as_sdl_event(event);

  ASSERT_EQ(underlying.adevice.type, cen::to_underlying(event.type()));
  ASSERT_EQ(underlying.adevice.timestamp, event.timestamp().count());
}
