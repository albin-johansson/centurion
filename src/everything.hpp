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

#include "centurion/area.hpp"
#include "centurion/base_path.hpp"
#include "centurion/battery.hpp"
#include "centurion/blend_mode.hpp"
#include "centurion/button_state.hpp"
#include "centurion/byte_order.hpp"
#include "centurion/cast.hpp"
#include "centurion/centurion.hpp"
#include "centurion/centurion_cfg.hpp"
#include "centurion/clipboard.hpp"
#include "centurion/color.hpp"
#include "centurion/colors.hpp"
#include "centurion/compiler.hpp"
#include "centurion/condition.hpp"
#include "centurion/controller.hpp"
#include "centurion/counter.hpp"
#include "centurion/cpu.hpp"
#include "centurion/cursor.hpp"
#include "centurion/czstring.hpp"
#include "centurion/event.hpp"
#include "centurion/event_dispatcher.hpp"
#include "centurion/event_type.hpp"
#include "centurion/exception.hpp"
#include "centurion/file.hpp"
#include "centurion/font.hpp"
#include "centurion/font_cache.hpp"
#include "centurion/graphics_drivers.hpp"
#include "centurion/haptic.hpp"
#include "centurion/hints.hpp"
#include "centurion/integers.hpp"
#include "centurion/joystick.hpp"
#include "centurion/key_code.hpp"
#include "centurion/key_modifier.hpp"
#include "centurion/key_state.hpp"
#include "centurion/locale.hpp"
#include "centurion/log.hpp"
#include "centurion/message_box.hpp"
#include "centurion/mouse_state.hpp"
#include "centurion/music.hpp"
#include "centurion/mutex.hpp"
#include "centurion/not_null.hpp"
#include "centurion/owner.hpp"
#include "centurion/pixel_format.hpp"
#include "centurion/platform.hpp"
#include "centurion/point.hpp"
#include "centurion/pref_path.hpp"
#include "centurion/ram.hpp"
#include "centurion/rect.hpp"
#include "centurion/renderer.hpp"
#include "centurion/scale_mode.hpp"
#include "centurion/scan_code.hpp"
#include "centurion/scoped_lock.hpp"
#include "centurion/screen.hpp"
#include "centurion/sdl_string.hpp"
#include "centurion/semaphore.hpp"
#include "centurion/sensor.hpp"
#include "centurion/shared_object.hpp"
#include "centurion/sound_effect.hpp"
#include "centurion/surface.hpp"
#include "centurion/texture.hpp"
#include "centurion/texture_access.hpp"
#include "centurion/thread.hpp"
#include "centurion/time.hpp"
#include "centurion/touch.hpp"
#include "centurion/try_lock.hpp"
#include "centurion/unicode_string.hpp"
#include "centurion/vector3.hpp"
#include "centurion/window.hpp"
#include "centurion/window_utils.hpp"
