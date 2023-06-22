target_sources(centurion-headers-only PUBLIC
  FILE_SET HEADERS
  FILES
    audio.hpp
    common.hpp
    concurrency.hpp
    events.hpp
    features.hpp
    fonts.hpp
    fwd.hpp
    initialization.hpp
    input.hpp
    io.hpp
    system.hpp
    video.hpp
)

add_subdirectory(audio)
add_subdirectory(common)
add_subdirectory(concurrency)
add_subdirectory(detail)
add_subdirectory(events)
add_subdirectory(fonts)
add_subdirectory(input)
add_subdirectory(io)
add_subdirectory(system)
add_subdirectory(video)
