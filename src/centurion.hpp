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

#ifndef CENTURION_HPP_
#define CENTURION_HPP_

#ifndef CENTURION_NO_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_NO_PRAGMA_ONCE

#include "centurion/audio.hpp"
#include "centurion/concurrency.hpp"
#include "centurion/core/common.hpp"
#include "centurion/core/exception.hpp"
#include "centurion/core/features.hpp"
#include "centurion/core/initialization.hpp"
#include "centurion/core/logging.hpp"
#include "centurion/core/memory.hpp"
#include "centurion/core/sdl_string.hpp"
#include "centurion/core/time.hpp"
#include "centurion/core/version.hpp"
#include "centurion/events/audio_device_event.hpp"
#include "centurion/events/common_event.hpp"
#include "centurion/events/controller_axis_event.hpp"
#include "centurion/events/controller_button_event.hpp"
#include "centurion/events/controller_device_event.hpp"
#include "centurion/events/controller_sensor_event.hpp"
#include "centurion/events/controller_touchpad_event.hpp"
#include "centurion/events/display_event.hpp"
#include "centurion/events/dollar_gesture_event.hpp"
#include "centurion/events/drop_event.hpp"
#include "centurion/events/event.hpp"
#include "centurion/events/event_dispatcher.hpp"
#include "centurion/events/event_type.hpp"
#include "centurion/events/joy_axis_event.hpp"
#include "centurion/events/joy_ball_event.hpp"
#include "centurion/events/joy_button_event.hpp"
#include "centurion/events/joy_device_event.hpp"
#include "centurion/events/joy_hat_event.hpp"
#include "centurion/events/joy_hat_position.hpp"
#include "centurion/events/keyboard_event.hpp"
#include "centurion/events/mouse_button_event.hpp"
#include "centurion/events/mouse_motion_event.hpp"
#include "centurion/events/mouse_wheel_direction.hpp"
#include "centurion/events/mouse_wheel_event.hpp"
#include "centurion/events/multi_gesture_event.hpp"
#include "centurion/events/quit_event.hpp"
#include "centurion/events/sensor_event.hpp"
#include "centurion/events/text_editing_event.hpp"
#include "centurion/events/text_input_event.hpp"
#include "centurion/events/touch_finger_event.hpp"
#include "centurion/events/user_event.hpp"
#include "centurion/events/window_event.hpp"
#include "centurion/events/window_event_id.hpp"
#include "centurion/filesystem.hpp"
#include "centurion/input/button_state.hpp"
#include "centurion/input/controller.hpp"
#include "centurion/input/haptic.hpp"
#include "centurion/input/haptic_condition.hpp"
#include "centurion/input/haptic_constant.hpp"
#include "centurion/input/haptic_custom.hpp"
#include "centurion/input/haptic_direction.hpp"
#include "centurion/input/haptic_direction_type.hpp"
#include "centurion/input/haptic_effect.hpp"
#include "centurion/input/haptic_feature.hpp"
#include "centurion/input/haptic_left_right.hpp"
#include "centurion/input/haptic_periodic.hpp"
#include "centurion/input/haptic_ramp.hpp"
#include "centurion/input/joystick.hpp"
#include "centurion/input/key_code.hpp"
#include "centurion/input/key_modifier.hpp"
#include "centurion/input/keyboard.hpp"
#include "centurion/input/keycodes.hpp"
#include "centurion/input/mouse.hpp"
#include "centurion/input/scan_code.hpp"
#include "centurion/input/scancodes.hpp"
#include "centurion/input/sensor.hpp"
#include "centurion/input/touch.hpp"
#include "centurion/input/touch_device_type.hpp"
#include "centurion/math.hpp"
#include "centurion/pixels.hpp"
#include "centurion/render.hpp"
#include "centurion/system.hpp"
#include "centurion/texture.hpp"
#include "centurion/video.hpp"
#include "centurion/video/button_order.hpp"
#include "centurion/video/color.hpp"
#include "centurion/video/colors.hpp"
#include "centurion/video/cursor.hpp"
#include "centurion/video/font.hpp"
#include "centurion/video/font_cache.hpp"
#include "centurion/video/graphics_drivers.hpp"
#include "centurion/video/message_box.hpp"
#include "centurion/video/message_box_type.hpp"
#include "centurion/video/opengl.hpp"
#include "centurion/video/renderer.hpp"
#include "centurion/video/scale_mode.hpp"
#include "centurion/video/screen.hpp"
#include "centurion/video/surface.hpp"
#include "centurion/video/texture_access.hpp"
#include "centurion/video/unicode_string.hpp"
#include "centurion/video/vulkan.hpp"
#include "centurion/video/window.hpp"

#endif  // CENTURION_HPP_
