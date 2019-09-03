cmake_minimum_required(VERSION 3.14)

project(Centurion)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCE_FILES
        include/centurion_audio.h
        include/centurion_events.h
        include/centurion_everything.h
        include/centurion_geo.h
        include/centurion_input.h
        include/centurion_tools.h
        include/centurion_visuals.h
        include/ctn_abstract_window.h
        include/ctn_action.h
        include/ctn_application_path.h
        include/ctn_audio_component.h
        include/ctn_bool_converter.h
        include/ctn_centurion.h
        include/ctn_color.h
        include/ctn_event.h
        include/ctn_font.h
        include/ctn_fullscreen_window.h
        include/ctn_image_impl.h
        include/ctn_image_interface.h
        include/ctn_input_dispatcher.h
        include/ctn_key_event.h
        include/ctn_key_listener.h
        include/ctn_key_listener_composite.h
        include/ctn_key_state.h
        include/ctn_key_stroke.h
        include/ctn_key_stroke_composite.h
        include/ctn_key_stroke_interface.h
        include/ctn_key_trigger.h
        include/ctn_mouse_event.h
        include/ctn_mouse_listener.h
        include/ctn_mouse_listener_composite.h
        include/ctn_mouse_state.h
        include/ctn_music.h
        include/ctn_point.h
        include/ctn_rectangle.h
        include/ctn_renderer.h
        include/ctn_renderer_interface.h
        include/ctn_screen.h
        include/ctn_sound_effect.h
        include/ctn_surface.h
        include/ctn_texture.h
        include/ctn_texture_interface.h
        include/ctn_window.h
        include/ctn_window_interface.h
        src/ctn_abstract_window.cpp
        src/ctn_application_path.cpp
        src/ctn_centurion.cpp
        src/ctn_color.cpp
        src/ctn_event.cpp
        src/ctn_font.cpp
        src/ctn_fullscreen_window.cpp
        src/ctn_image_impl.cpp
        src/ctn_input_dispatcher.cpp
        src/ctn_key_event.cpp
        src/ctn_key_listener_composite.cpp
        src/ctn_key_state.cpp
        src/ctn_key_stroke.cpp
        src/ctn_key_stroke_composite.cpp
        src/ctn_mouse_event.cpp
        src/ctn_mouse_listener_composite.cpp
        src/ctn_mouse_state.cpp
        src/ctn_music.cpp
        src/ctn_point.cpp
        src/ctn_rectangle.cpp
        src/ctn_renderer.cpp
        src/ctn_screen.cpp
        src/ctn_sound_effect.cpp
        src/ctn_surface.cpp
        src/ctn_texture.cpp
        src/ctn_window.cpp)

set(SDL2_ROOT ${PROJECT_SOURCE_DIR}/SDL2-x64)

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/src)

include_directories(${SDL2_ROOT}/include/SDL2)
link_directories(${SDL2_ROOT}/lib)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})