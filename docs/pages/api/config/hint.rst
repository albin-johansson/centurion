Hints
=====

The hints API provides type-safe configuration of the behaviour of SDL. Every hint is 
represented by its own class. However, the implementation of the hint classes is not 
really of interest. 

.. note::

  In the current implementation, the type-safety is acheived using SFINAE. In the future, concepts 
  might replace this implementation and improve the error messages thrown when using incorrect types.

Interface
---------

.. doxygenfunction:: centurion::set_hint
  :outline:

.. doxygenfunction:: centurion::get_hint
  :outline:

.. doxygenfunction:: centurion::add_hint_callback
  :outline:

Enum hints
----------

Enum hints only accept their associated enum's enumerators as values.

.. note:: 

  Enum hints have public member enums that provides the acceptable values. For example, ``render_driver::open_gl``
  is a possible value for the ``render_driver`` hint.

============================================== =======================================================
 Hint class                                     SDL Counterpart                                       
---------------------------------------------- -------------------------------------------------------
 ``render_driver``                              ``SDL_HINT_RENDER_DRIVER``                            
 ``audio_resampling_mode``                      ``SDL_HINT_AUDIO_RESAMPLING_MODE``                    
 ``scale_quality``                              ``SDL_HINT_RENDER_SCALE_QUALITY``                     
 ``framebuffer_acceleration``                   ``SDL_HINT_FRAMEBUFFER_ACCELERATION``                 
 ``audio_category``                             ``SDL_HINT_AUDIO_CATEGORY``                           
 ``windows::d3d_compiler``                      ``SDL_HINT_VIDEO_WIN_D3DCOMPILER``
 ``wave_riff_chunk_size``                       ``SDL_HINT_WAVE_RIFF_CHUNK_SIZE``                     
 ``wave_truncation``                            ``SDL_HINT_WAVE_TRUNCATION``                          
 ``wave_fact_chunk``                            ``SDL_HINT_WAVE_FACT_CHUNK``                          
 ``logical_size_mode``                          ``SDL_HINT_RENDER_LOGICAL_SIZE_MODE``                          
 ``qt_wayland_content_orientation``             ``SDL_HINT_QTWAYLAND_CONTENT_ORIENTATION``                 
============================================== =======================================================

Boolean hints
-------------

Boolean hints only accept either ``true`` or ``false`` as values.

============================================== =======================================================
 Hint class                                     SDL Counterpart                                       
---------------------------------------------- -------------------------------------------------------
 ``accelerometer_as_joystick``                  ``SDL_HINT_ACCELEROMETER_AS_JOYSTICK``                
 ``allow_top_most``                             ``SDL_HINT_ALLOW_TOPMOST``                            
 ``android::block_on_pause``                    ``SDL_HINT_ANDROID_BLOCK_ON_PAUSE``
 ``android::trap_back_button``                  ``SDL_HINT_ANDROID_TRAP_BACK_BUTTON``
 ``apple_tv_controller_ui_events``              ``SDL_HINT_APPLE_TV_CONTROLLER_UI_EVENTS``            
 ``apple_tv_remote_allow_rotation``             ``SDL_HINT_APPLE_TV_REMOTE_ALLOW_ROTATION``           
 ``bmp_save_legacy_format``                     ``SDL_HINT_BMP_SAVE_LEGACY_FORMAT``                   
 ``double_buffer``                              ``SDL_HINT_VIDEO_DOUBLE_BUFFER``                      
 ``enable_steam_controllers``                   ``SDL_HINT_ENABLE_STEAM_CONTROLLERS``                 
 ``gamecontroller::use_button_labels``          ``SDL_HINT_GAMECONTROLLER_USE_BUTTON_LABELS``
 ``grab_keyboard``                              ``SDL_HINT_GRAB_KEYBOARD``
 ``idle_timer_disabled``                        ``SDL_HINT_IDLE_TIMER_DISABLED``                      
 ``ime_internal_editing``                       ``SDL_HINT_IME_INTERNAL_EDITING``                     
 ``joystick::allow_background_events``          ``SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS``
 ``joystick::use_hidapi``                       ``SDL_HINT_JOYSTICK_HIDAPI``
 ``joystick::use_hidapi_ps4``                   ``SDL_HINT_JOYSTICK_HIDAPI_PS4``
 ``joystick::use_hidapi_ps4_rumble``            ``SDL_HINT_JOYSTICK_HIDAPI_PS4_RUMBLE``
 ``joystick::use_hidapi_steam``                 ``SDL_HINT_JOYSTICK_HIDAPI_STEAM``
 ``joystick::use_hidapi_switch``                ``SDL_HINT_JOYSTICK_HIDAPI_SWITCH``
 ``joystick::use_hidapi_xbox``                  ``SDL_HINT_JOYSTICK_HIDAPI_XBOX``
 ``joystick::use_hidapi_game_cube``             ``SDL_HINT_JOYSTICK_HIDAPI_GAMECUBE``
 ``mac::background_app``                        ``SDL_HINT_MAC_BACKGROUND_APP``
 ``mac::ctrl_click_emulate_right_click``        ``SDL_HINT_MAC_CTRL_CLICK_EMULATE_RIGHT_CLICK``
 ``mouse::focus_clickthrough``                  ``SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH``
 ``mouse::relative_mode_warp``                  ``SDL_HINT_MOUSE_RELATIVE_MODE_WARP``
 ``no_signal_handlers``                         ``SDL_HINT_NO_SIGNAL_HANDLERS``                       
 ``d3d::v11_debug``                             ``SDL_HINT_RENDER_DIRECT3D11_DEBUG``
 ``d3d::thread_safe``                           ``SDL_HINT_RENDER_DIRECT3D_THREADSAFE``
 ``opengl_es_driver``                           ``SDL_HINT_OPENGL_ES_DRIVER``
 ``enable_opengl_shaders``                      ``SDL_HINT_RENDER_OPENGL_SHADERS``                    
 ``vsync``                                      ``SDL_HINT_RENDER_VSYNC``
 ``allow_screensaver``                          ``SDL_HINT_VIDEO_ALLOW_SCREENSAVER``                  
 ``video_external_context``                     ``SDL_HINT_VIDEO_EXTERNAL_CONTEXT``                   
 ``disable_high_dpi``                           ``SDL_HINT_VIDEO_HIGHDPI_DISABLED``                   
 ``mac::fullscreen_spaces``                     ``SDL_HINT_VIDEO_MAC_FULLSCREEN_SPACES``
 ``minimize_on_focus_loss``                     ``SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS``             
 ``x11::net_wm_ping``                           ``SDL_HINT_VIDEO_X11_NET_WM_PING``
 ``x11::net_wm_bypass_compositor``              ``SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR``
 ``x11::force_egl``                             ``SDL_HINT_VIDEO_X11_FORCE_EGL``
 ``x11::xinerama``                              ``SDL_HINT_VIDEO_X11_XINERAMA``
 ``x11::xrandr``                                ``SDL_HINT_VIDEO_X11_XRANDR``
 ``x11::xvidmode``                              ``SDL_HINT_VIDEO_X11_XVIDMODE``
 ``windows::no_thread_naming``                  ``SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING``
 ``windows::enable_message_loop``               ``SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP``
 ``windows::no_close_on_alt_f4``                ``SDL_HINT_WINDOWS_NO_CLOSE_ON_ALT_F4``
 ``window_frame_usable_while_cursor_hidden``    ``SDL_HINT_WINDOW_FRAME_USABLE_WHILE_CURSOR_HIDDEN``  
 ``mouse_touch_events``                         ``SDL_HINT_MOUSE_TOUCH_EVENTS``                       
 ``render_batching``                            ``SDL_HINT_RENDER_BATCHING``                          
 ``return_key_hides_ime``                       ``SDL_HINT_RETURN_KEY_HIDES_IME``                     
 ``touch_mouse_events``                         ``SDL_HINT_TOUCH_MOUSE_EVENTS``                       
 ``tv_remote_as_joystick``                      ``SDL_HINT_TV_REMOTE_AS_JOYSTICK``                    
 ``xinput_enabled``                             ``SDL_HINT_XINPUT_ENABLED``                           
 ``xinput_use_old_joystick_mapping``            ``SDL_HINT_XINPUT_USE_OLD_JOYSTICK_MAPPING``
 ``winrt::handle_back_button``                  ``SDL_HINT_WINRT_HANDLE_BACK_BUTTON``
============================================== =======================================================

String hints
------------

String hints accept any string. Whilst still type-safe, there are no compile-time checks that supplied 
strings are actually valid. It should be noted that quite a few of the hints have restrictions on the 
format of the string arguments.

============================================== =======================================================
 Hint class                                     SDL Counterpart                                       
---------------------------------------------- -------------------------------------------------------
 ``display_usable_bounds``                      ``SDL_HINT_DISPLAY_USABLE_BOUNDS``                    
 ``emscripten_keyboard_element``                ``SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT``              
 ``gamecontroller::type``                       ``SDL_HINT_GAMECONTROLLERTYPE``
 ``gamecontroller::config``                     ``SDL_HINT_GAMECONTROLLERCONFIG``
 ``gamecontroller::config_file``                ``SDL_HINT_GAMECONTROLLERCONFIG_FILE``
 ``gamecontroller::ignore_devices``             ``SDL_HINT_GAMECONTROLLER_IGNORE_DEVICES``
 ``gamecontroller::ignore_devices_except``      ``SDL_HINT_GAMECONTROLLER_IGNORE_DEVICES_EXCEPT``
 ``orientations``                               ``SDL_HINT_ORIENTATIONS``                             
 ``x11::window_visual_id``                      ``SDL_HINT_VIDEO_X11_WINDOW_VISUALID``
 ``window_share_pixel_format``                  ``SDL_HINT_VIDEO_WINDOW_SHARE_PIXEL_FORMAT``
 ``windows::int_resource_icon``                 ``SDL_HINT_WINDOWS_INTRESOURCE_ICON``
 ``windows::int_resource_icon_small``           ``SDL_HINT_WINDOWS_INTRESOURCE_ICON_SMALL``
 ``winrt::privacy_policy_label``                ``SDL_HINT_WINRT_PRIVACY_POLICY_LABEL``
 ``winrt::privacy_policy_url``                  ``SDL_HINT_WINRT_PRIVACY_POLICY_URL``
 ``qt_wayland_window_flags``                    ``SDL_HINT_QTWAYLAND_WINDOW_FLAGS``                   
============================================== =======================================================

Integer hints
-------------

Integer hints accept ``int`` (or ``unsigned int``) as values.

.. note::

  ``thread_stack_size`` and ``timer_resolution`` take ``unsigned int`` as arguments.

============================================== =======================================================
 Hint class                                     SDL Counterpart                                       
---------------------------------------------- -------------------------------------------------------
 ``mouse::double_click_time``                   ``SDL_HINT_MOUSE_DOUBLE_CLICK_TIME``
 ``mouse::double_click_radius``                 ``SDL_HINT_MOUSE_DOUBLE_CLICK_RADIUS``
 ``event_logging``                              ``SDL_HINT_EVENT_LOGGING``                            
 ``android::apk_expansion_main_file_version``   ``SDL_HINT_ANDROID_APK_EXPANSION_MAIN_FILE_VERSION``
 ``android::apk_expansion_patch_file_version``  ``SDL_HINT_ANDROID_APK_EXPANSION_PATCH_FILE_VERSION``
 ``raspberry_pi_video_layer``                   ``SDL_HINT_RPI_VIDEO_LAYER``                          
 ``thread_stack_size``                          ``SDL_HINT_THREAD_STACK_SIZE``
 ``timer_resolution``                           ``SDL_HINT_TIMER_RESOLUTION``                         
============================================== =======================================================

Float hints
-----------

Float hints only accept ``float`` as values.

============================================== =======================================================
 Hint class                                     SDL Counterpart                                       
---------------------------------------------- -------------------------------------------------------
 ``mouse::normal_speed_scale``                  ``SDL_HINT_MOUSE_NORMAL_SPEED_SCALE``
 ``mouse::relative_speed_scale``                ``SDL_HINT_MOUSE_RELATIVE_SPEED_SCALE``
============================================== =======================================================

Examples
--------

Setting the value of a hint
~~~~~~~~~~~~~~~~~~~~~~~~~~~

The idea behind the hint API is to be type-safe and ensure that the correct  
type is used when setting the value of a hint. In contrast with raw SDL 
functions, such as ``SDL_SetHint``, that simply accept raw strings. The following 
demonstrates this in action.

.. code-block:: C++

  #include <centurion_as_ctn.hpp>
  #include <hints.hpp>

  void foo()
  {
    using ctn::hint::render_driver;

    // attempts to specify OpenGL as desired render driver
    const auto success = ctn::set_hint<render_driver>(render_driver::open_gl);

    if (success) {
      // successfully set the render driver hint
    }

    // the following results in compile-time errors...
    // ctn::set_hint<render_driver>(42);
    // ctn::set_hint<render_driver>(true);
    // ctn::set_hint<render_driver>("bar");
  }

Getting the value of a hint
~~~~~~~~~~~~~~~~~~~~~~~~~~~

The following example shows how the value of hints are obtained. The ``get_hint`` function
always returns a ``std::optional`` that wraps a value of the value type used by the hint.

.. code-block:: C++

  #include <centurion_as_ctn.hpp>
  #include <hints.hpp>

  void foo()
  {
    using ctn::hint::render_batching;
    using ctn::hint::event_logging;

    if (const std::optional<bool> batching = ctn::get_hint<render_batching>(); batching) {
      // successfully obtained render batching value
    }
    
    if (const std::optional<int> level = ctn::get_hint<event_logging>(); level) {
      // successfully obtained event logging value
    }
  }

Observing hint value changes
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

It's possible to observe changes to hints with callbacks. 

.. code-block:: C++

  #include <centurion_as_ctn.hpp>
  #include <hints.hpp>

  void foo()
  {
    auto callback = [](void* userData, czstring hint, czstring oldValue, czstring newValue) {
      // handle the hint update
    }

    // adds the callback, it's also possible to supply a pointer to user data
    auto handle = ctn::add_hint_callback(callback);

    // the handle makes it possible to disconnect/connect the callback
    handle.disconnect();
  }
