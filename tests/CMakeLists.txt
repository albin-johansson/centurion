project(centurion-tests LANGUAGES CXX)

function(cen_prepare_target target)
  set_target_properties(${target}
                        PROPERTIES
                        CXX_STANDARD_REQUIRED ON
                        CXX_EXTENSIONS OFF
                        )

  target_precompile_headers(${target} PRIVATE
                            <array>
                            <algorithm>
                            <vector>
                            <memory>
                            <string>
                            <string_view>
                            <sstream>
                            <optional>
                            <ostream>
                            <iostream>
                            <utility>
                            <type_traits>
                            )

  if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${target}
                           PRIVATE
                           /EHsc
                           /MP
                           /W4
                           /Zc:preprocessor # Enable conforming preprocessor
                           /Zc:__cplusplus  # Force MSVC to use __cplusplus macro with correct value
                           /wd4996          # Disable deprecation warnings
                           )

    if (CEN_TREAT_WARNINGS_AS_ERRORS MATCHES ON)
      target_compile_options(${target} PRIVATE /WX)
    endif ()
  else ()
    target_compile_options(${target} PRIVATE
                           -Wall
                           -Wextra
                           -Wpedantic
                           -Wconversion
                           -Wno-deprecated
                           -Wno-deprecated-declarations
                           -Wno-format-security
                           )

    if (CEN_TREAT_WARNINGS_AS_ERRORS MATCHES ON)
      target_compile_options(${target} PRIVATE -Werror)
    endif ()
  endif ()
endfunction()

add_subdirectory(unit-tests)
