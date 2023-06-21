target_sources(centurion PUBLIC
  FILE_SET HEADERS
  BASE_DIRS ${CEN_SOURCE_DIR}
  FILES centurion.hpp
)

add_subdirectory(centurion)
