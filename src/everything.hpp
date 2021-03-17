/*
 * MIT License
 *
 * Copyright (c) 2019-2021 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "audio/music.hpp"
#include "audio/sound_effect.hpp"
#include "centurion/battery.hpp"
#include "centurion/blend_mode.hpp"
#include "centurion/byte_order.hpp"
#include "centurion/cast.hpp"
#include "centurion/centurion_cfg.hpp"
#include "centurion/clipboard.hpp"
#include "centurion/compiler.hpp"
#include "centurion/counter.hpp"
#include "centurion/cpu.hpp"
#include "centurion/czstring.hpp"
#include "centurion/events/event.hpp"
#include "centurion/events/event_dispatcher.hpp"
#include "centurion/events/event_type.hpp"
#include "centurion/exception.hpp"
#include "centurion/hints.hpp"
#include "centurion/integers.hpp"
#include "centurion/library.hpp"
#include "centurion/locale.hpp"
#include "centurion/log.hpp"
#include "centurion/not_null.hpp"
#include "centurion/owner.hpp"
#include "centurion/platform.hpp"
#include "centurion/ram.hpp"
#include "centurion/sdl_string.hpp"
#include "centurion/shared_object.hpp"
#include "centurion/time.hpp"
#include "filesystem/base_path.hpp"
#include "filesystem/file.hpp"
#include "filesystem/pref_path.hpp"
#include "input/button_state.hpp"
#include "input/controller.hpp"
#include "input/haptic.hpp"
#include "input/joystick.hpp"
#include "input/key_code.hpp"
#include "input/key_modifier.hpp"
#include "input/key_state.hpp"
#include "input/mouse_state.hpp"
#include "input/scan_code.hpp"
#include "input/sensor.hpp"
#include "input/touch.hpp"
#include "math/area.hpp"
#include "math/point.hpp"
#include "math/rect.hpp"
#include "math/vector3.hpp"
#include "thread/condition.hpp"
#include "thread/mutex.hpp"
#include "thread/scoped_lock.hpp"
#include "thread/semaphore.hpp"
#include "thread/thread.hpp"
#include "thread/try_lock.hpp"
#include "video/color.hpp"
#include "video/colors.hpp"
#include "video/cursor.hpp"
#include "video/font.hpp"
#include "video/font_cache.hpp"
#include "video/graphics_drivers.hpp"
#include "video/message_box.hpp"
#include "video/pixel_format.hpp"
#include "video/renderer.hpp"
#include "video/scale_mode.hpp"
#include "video/screen.hpp"
#include "video/surface.hpp"
#include "video/texture.hpp"
#include "video/texture_access.hpp"
#include "video/unicode_string.hpp"
#include "video/window.hpp"
#include "video/window_utils.hpp"
