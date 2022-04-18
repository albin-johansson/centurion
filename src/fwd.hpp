/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
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

#pragma once

namespace cen {

struct sdl_cfg;
struct mix_cfg;
struct img_cfg;
class sdl;
class mix;
class img;
class ttf;

struct version;

class file;

class font;
class font_cache;
class unicode_string;

struct dpi_info;
struct blend_task;
struct renderer_scale;
class color;
class gl_library;
class vk_library;
class display_mode;

class music;

class palette;

class condition;
class mutex;
class scoped_lock;
class try_lock;
class semaphore;
class thread;

class audio_device_event;
class controller_axis_event;
class controller_button_event;
class controller_device_event;
class dollar_gesture_event;
class drop_event;
class joy_axis_event;
class joy_ball_event;
class joy_button_event;
class joy_device_event;
class joy_hat_event;
class keyboard_event;
class mouse_button_event;
class mouse_motion_event;
class mouse_wheel_event;
class multi_gesture_event;
class quit_event;
class text_editing_event;
class text_input_event;
class touch_finger_event;
class sensor_event;
class user_event;
class window_event;
class display_event;
class controller_touchpad_event;
class controller_sensor_event;
class event_handler;

struct ball_axis_delta;
class key_code;
class scan_code;
class keyboard;
class mouse;
class finger;

class locale;

class simd_block;
class shared_object;

class message_box_color_scheme;
class message_box;

namespace experimental {
class font_bundle;
}  // namespace experimental

template <typename T>
class event_base;

template <typename... Events>
class event_dispatcher;

template <typename E>
class event_sink;

template <typename T>
struct basic_vector3;

template <typename T>
struct basic_area;

template <typename T>
class basic_point;

template <typename T>
class basic_rect;

template <typename T>
class basic_window;

template <typename T>
class basic_renderer;

template <typename T>
class basic_gl_context;

template <typename T>
class basic_sound_effect;

template <typename T>
class basic_controller;

template <typename T>
class basic_joystick;

template <typename T>
class basic_cursor;

template <typename T>
class basic_pixel_format_info;

template <typename T>
class basic_sensor;

template <typename T>
class basic_surface;

template <typename T>
class basic_texture;

template <typename T>
struct deleter;

}  // namespace cen
