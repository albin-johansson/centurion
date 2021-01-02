cmake_minimum_required(VERSION 3.15)

project(CenturionSrc)

set(SOURCE_FILES
    ../include/area.hpp

    ../include/base_path.hpp
    ../include/battery.hpp
    ../include/blend_mode.hpp
    ../include/button_state.hpp

    ../include/cast.hpp
    ../include/centurion.hpp
    ../include/centurion_api.hpp
    ../include/centurion_cfg.hpp
    ../include/clipboard.hpp
    ../include/color.hpp
    ../include/colors.hpp
    ../include/condition.hpp
    ../include/controller.hpp
    ../include/counter.hpp
    ../include/cpu.hpp
    ../include/cursor.hpp
    ../include/czstring.hpp

    ../include/event_type.hpp
    ../include/event.hpp
    ../include/exception.hpp

    ../include/font.hpp
    ../include/font_cache.hpp

    ../include/graphics_drivers.hpp

    ../include/hints.hpp

    ../include/integers.hpp

    ../include/joystick.hpp

    ../include/key_code.hpp
    ../include/key_modifier.hpp
    ../include/key_state.hpp

    ../include/log.hpp

    ../include/message_box.hpp
    ../include/mouse_button.hpp
    ../include/mouse_state.hpp
    ../include/mutex.hpp

    ../include/not_null.hpp

    ../include/owner.hpp

    ../include/pixel_format.hpp
    ../include/platform.hpp
    ../include/point.hpp
    ../include/pref_path.hpp

    ../include/ram.hpp
    ../include/rect.hpp
    ../include/renderer.hpp

    ../include/scale_mode.hpp
    ../include/scan_code.hpp
    ../include/scoped_lock.hpp
    ../include/screen.hpp
    ../include/sdl_string.hpp
    ../include/semaphore.hpp
    ../include/surface.hpp

    ../include/texture.hpp
    ../include/texture_access.hpp
    ../include/thread.hpp
    ../include/time.hpp
    ../include/touch.hpp
    ../include/try_lock.hpp
    ../include/types.hpp

    ../include/unicode_string.hpp

    ../include/window.hpp
    ../include/window_utils.hpp

    ../include/detail/address_of.hpp
    ../include/detail/any_eq.hpp
    ../include/detail/clamp.hpp
    ../include/detail/convert_bool.hpp
    ../include/detail/czstring_eq.hpp
    ../include/detail/max.hpp
    ../include/detail/owner_handle_api.hpp
    ../include/detail/stack_resource.hpp
    ../include/detail/static_bimap.hpp
    ../include/detail/to_string.hpp

    graphics/graphics_drivers.cpp
    graphics/message_box.cpp
    graphics/message_box_button.cpp
    graphics/message_box_color_scheme.cpp
    graphics/texture.cpp

    system/pref_path.cpp
    system/screen.cpp

    input/key_code.cpp
    input/mouse_state.cpp
    input/scan_code.cpp
    input/touch.cpp)

if (CEN_AUDIO)
  set(SOURCE_FILES
      ${SOURCE_FILES}
      ../include/sound_effect.hpp
      ../include/music.hpp)
endif ()

add_library(${CENTURION_LIB_TARGET} SHARED ${SOURCE_FILES})

if (WIN32)
  add_definitions(-DWIN_EXPORT)
endif ()

set_target_properties(${CENTURION_LIB_TARGET} PROPERTIES
    OUTPUT_NAME ${CMAKE_IMPORT_LIBRARY_PREFIX}Centurion
    VERSION ${CENTURION_VERSION})

target_include_directories(${CENTURION_LIB_TARGET}
    SYSTEM PUBLIC ${SDL2_INCLUDE_DIR}
    SYSTEM PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS}
    SYSTEM PUBLIC ${SDL2_MIXER_INCLUDE_DIRS}
    SYSTEM PUBLIC ${SDL2_TTF_INCLUDE_DIRS}
    PRIVATE ${CEN_INCLUDE_DIR}
    PRIVATE ${CEN_SOURCE_DIR}
    SYSTEM INTERFACE ${CEN_INCLUDE_DIR})

target_link_libraries(${CENTURION_LIB_TARGET}
    PUBLIC ${SDL2_LIBRARY}
    PUBLIC ${SDL2_IMAGE_LIBRARIES}
    PUBLIC ${SDL2_MIXER_LIBRARIES}
    PUBLIC ${SDL2_TTF_LIBRARIES})

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${CENTURION_LIB_TARGET} PRIVATE
      -Wall
      -Wextra
      -Wpedantic
      -Wdouble-promotion
      -Wswitch-default
      -Wswitch-enum
      -Wunused
      -Wuninitialized
      -Wsuggest-final-types
      -Wsuggest-final-methods
      -Wsuggest-override
      -Wduplicated-cond
      -Wconversion
      -Wc++17-compat
      -Wno-attributes)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_compile_options(${CENTURION_LIB_TARGET} PRIVATE
      /EHsc
      -Wall
      -Wextra
      -Wpedantic
      -Wdouble-promotion
      -Wswitch-default
      -Wswitch-enum
      -Wunused
      -Wuninitialized
      -Wconversion
      -Wc++17-compat
      -Wno-c++98-compat
      -Wno-c++98-compat-pedantic
      -Wno-unused-template
      -Wno-unused-macros
      -Wno-newline-eof
      -Wno-documentation-unknown-command)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(${CENTURION_LIB_TARGET} PRIVATE
      /EHsc
      /MP
      /W3)
endif ()

