cmake_minimum_required(VERSION 3.12)
project(${CENTURION_DEMO})

add_executable(${CENTURION_DEMO} demo_main.cpp)

set_target_properties(${CENTURION_DEMO} PROPERTIES
        CXX_STANDARD 17)
remove_definitions(-DWIN_EXPORT)

set(dp "C:/Users/albin/Documents/GitHub/Centurion/cmake-build-release/src/libCenturion.dll")

target_include_directories(${CENTURION_DEMO} PUBLIC "${PROJECT_SOURCE_DIR}/../src")
target_include_directories(${CENTURION_DEMO} PUBLIC "${PROJECT_SOURCE_DIR}/../src/lib")
target_include_directories(${CENTURION_DEMO} PUBLIC "${PROJECT_SOURCE_DIR}/../src/lib/gsl")

target_include_directories(${CENTURION_DEMO} PUBLIC ${SDL2_INCLUDE_DIR})
target_include_directories(${CENTURION_DEMO} PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS})
target_include_directories(${CENTURION_DEMO} PUBLIC ${SDL2_MIXER_INCLUDE_DIRS})
target_include_directories(${CENTURION_DEMO} PUBLIC ${SDL2_TTF_INCLUDE_DIRS})

if (WIN32)
    target_link_libraries(${CENTURION_DEMO}
            mingw32
            ${dp}
            ${SDL2_LIBRARY}
            ${SDL2_IMAGE_LIBRARIES}
            ${SDL2_MIXER_LIBRARIES}
            ${SDL2_TTF_LIBRARIES})
else ()
    target_link_libraries(${CENTURION_DEMO}
            ${CENTURION_LIB}
            ${SDL2_LIBRARY}
            ${SDL2_IMAGE_LIBRARIES}
            ${SDL2_MIXER_LIBRARIES}
            ${SDL2_TTF_LIBRARIES})
endif ()

# Copies all of the files in the bin folder and puts them next to the executable
add_custom_command(TARGET ${CENTURION_DEMO} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${BINARIES_DIR}"
        ${CMAKE_BINARY_DIR}/demo)

# Copies all of the resources and puts the in the build folder
add_custom_command(TARGET ${CENTURION_DEMO} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${RESOURCES_DIR}"
        ${CMAKE_BINARY_DIR}/demo/resources)
