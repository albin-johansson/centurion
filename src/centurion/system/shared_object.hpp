#ifndef CENTURION_SHARED_OBJECT_HEADER
#define CENTURION_SHARED_OBJECT_HEADER

#include <SDL.h>

#include <cassert>  // assert
#include <memory>   // unique_ptr
#include <string>   // string

#include "../core/exception.hpp"
#include "../core/not_null.hpp"
#include "../core/str.hpp"

namespace cen {

/// \addtogroup system
/// \{

/**
 * \class shared_object
 *
 * \brief Represents a shared object, such as dynamic libraries (e.g. `.so` and `.dll`
 * files).
 *
 * \since 5.3.0
 */
class shared_object final
{
 public:
  /**
   * \brief Loads a shared object.
   *
   * \param object the name of the shared object that will be loaded.
   *
   * \throws sdl_error if the shared object cannot be loaded.
   *
   * \since 5.3.0
   */
  explicit shared_object(const not_null<str> object) : m_object{SDL_LoadObject(object)}
  {
    if (!m_object) {
      throw sdl_error{};
    }
  }

  /**
   * \brief Loads a shared object.
   *
   * \param object the name of the shared object that will be loaded.
   *
   * \throws sdl_error if the shared object cannot be loaded.
   *
   * \since 5.3.0
   */
  explicit shared_object(const std::string& object) : shared_object{object.c_str()}
  {}

  /**
   * \brief Attempts to load a function from the shared object.
   *
   * \note The function must be a C-function!
   *
   * \tparam T the signature of the function, e.g. `void(int, float)`.
   *
   * \param name the name of the function in the shared object.
   *
   * \return the loaded function; a null pointer is returned if something goes wrong.
   *
   * \since 5.3.0
   */
  template <typename T>
  [[nodiscard]] auto load_function(const not_null<str> name) const noexcept -> T*
  {
    assert(name);
    return reinterpret_cast<T*>(SDL_LoadFunction(m_object.get(), name));
  }

  /**
   * \brief Attempts to load a function from the shared object.
   *
   * \note The function must be a C-function!
   *
   * \tparam T the signature of the function, e.g. `void(int, float)`.
   *
   * \param name the name of the function in the shared object.
   *
   * \return the loaded function; a null pointer is returned if something goes wrong.
   *
   * \since 5.3.0
   */
  template <typename T>
  [[nodiscard]] auto load_function(const std::string& name) const noexcept -> T*
  {
    return load_function<T>(name.c_str());
  }

 private:
  struct deleter final
  {
    void operator()(void* object) noexcept
    {
      SDL_UnloadObject(object);
    }
  };
  std::unique_ptr<void, deleter> m_object;

#ifdef CENTURION_MOCK_FRIENDLY_MODE

 public:
  shared_object() = default;
#endif  // CENTURION_MOCK_FRIENDLY_MODE
};

/// \} End of group system

}  // namespace cen

#endif  // CENTURION_SHARED_OBJECT_HEADER
