/**
 * \brief Provides utilities related to managing hints.
 *
 * \details Provides utilities related to managing hints ("configuration
 * variables" on the SDL2 wiki). Refer to the official SDL2 wiki or the
 * <code>SDL_hints.hpp</code> header for details regarding any specific hint
 * type.
 *
 * \todo `WindowsIntResourceIcon`, `WindowsIntResourceIconSmall`,
 * `X11WindowVisualID` are string hints because the types of their values
 * isn't known. Should be fixed if the type isn't actually string.
 *
 * \todo C++20: Make callback signature depend on the `UserData` and the type
 * of the associated hint, so that the values supplied to the callback aren't
 * always strings.
 *
 * \todo Document all of the hint classes.
 *
 * \file hints.hpp
 *
 * \since 4.1.0
 *
 * \author Albin Johansson
 *
 * \date 2019-2021
 *
 * \copyright MIT License
 */

#ifndef CENTURION_HINTS_HEADER
#define CENTURION_HINTS_HEADER

#include <SDL.h>

#include <optional>  // optional

#include "../core/exception.hpp"
#include "../core/log.hpp"
#include "../core/result.hpp"

namespace cen {

/// \addtogroup configuration
/// \{

/**
 * \enum hint_priority
 *
 * \brief Provides three different priorities that can be specified when
 * setting the value of a hint.
 *
 * \since 4.1.0
 *
 * \see `SDL_HintPriority`
 */
enum class hint_priority
{
  low = SDL_HINT_DEFAULT,       ///< The lowest possible priority.
  normal = SDL_HINT_NORMAL,     ///< The priority used by default by `set_hint`.
  override = SDL_HINT_OVERRIDE  ///< The highest priority.
};

/**
 * \brief Sets the value of the specified hint.
 *
 * \details This method will only accept values that are related to the
 * specified hint, supplying the wrong kind of value causes a compile-time
 * error. See the related hint class for more details about the associated
 * value type. However, whilst this method is type-safe, it doesn't ensure
 * that *correct* values are specified for the hints.
 *
 * \tparam Hint the type of the hint that will be modified.
 * \tparam priority the priority that will be used, defaults to `normal`.
 * \tparam Value the type of the hint value.
 *
 * \param value the new value that will be set for the specified hint.
 *
 * \return `success` if the hint was successfully set; `failure` otherwise.
 *
 * \since 4.1.0
 */
template <typename Hint,
          hint_priority priority = hint_priority::normal,
          typename Value,
          typename = std::enable_if_t<Hint::template valid_arg<Value>()>>
auto set_hint(const Value& value) -> result
{
  return static_cast<bool>(
      SDL_SetHintWithPriority(Hint::name(),
                              Hint::to_string(value).c_str(),
                              static_cast<SDL_HintPriority>(priority)));
}

/**
 * \brief Returns the current value of the specified hint.
 *
 * \note The returned value is a `std::optional` of the hint value type. Many
 * hints aren't actually set by default.
 *
 * \tparam Hint the type of the Hint to obtain the value of.
 *
 * \return the current value of the specified hint; `std::nullopt` if there is
 * no value set for the hint.
 *
 * \since 4.1.0
 */
template <typename Hint>
[[nodiscard]] auto get_hint() noexcept
{
  return Hint::current_value();
}

/**
 * \class hint_callback
 *
 * \brief Represents a handle for dealing with hint callbacks.
 *
 * \details This class provides methods for easily connecting and disconnecting a callback
 * from receiving updates.
 *
 * \tparam Hint the type of the associated hint. Should be one of the hint types defined
 * in the `hints.hpp` header.
 *
 * \tparam UserData the type of the user data.
 *
 * \since 4.1.0
 */
template <typename Hint, typename UserData = void>
class hint_callback final
{
 public:
  /**
   * \brief Creates a hint callback.
   *
   * \param callback the function object that will be called whenever the associated hint
   * is updated. The signature should be `void(void*, czstring, czstring, czstring)`.
   * \param userData a pointer to some user data. Defaults to `nullptr`.
   *
   * \throws cen_error if the supplied function pointer is null.
   *
   * \since 4.1.0
   */
  explicit hint_callback(SDL_HintCallback callback, UserData* userData = nullptr)
      : m_callback{callback}
      , m_userData{userData}
  {
    if (!callback)
    {
      throw cen_error{"Failed to create hint callback"};
    }
  }

  /**
   * \brief Registers the callback to be invoked whenever the associated hint is updated.
   *
   * \see `SDL_AddHintCallback`
   *
   * \since 4.1.0
   */
  void connect() noexcept
  {
    SDL_AddHintCallback(Hint::name(), m_callback, static_cast<void*>(m_userData));
  }

  /**
   * \brief Unregisters the callback from being updated whenever the associated hint is
   * updated.
   *
   * \see `SDL_DelHintCallback`
   *
   * \since 4.1.0
   */
  void disconnect() noexcept
  {
    SDL_DelHintCallback(Hint::name(), m_callback, static_cast<void*>(m_userData));
  }

  /**
   * \brief Returns a pointer to the function that is invoked when the associated hint is
   * updated.
   *
   * \return a pointer to the function that is invoked when the associated hint is
   * updated.
   *
   * \since 4.1.0
   */
  [[nodiscard]] auto get() noexcept -> SDL_HintCallback
  {
    return m_callback;
  }

  /**
   * \brief Returns a pointer to the user data associated with the callback.
   *
   * \return a pointer to the user data associated with the callback, can be null.
   *
   * \since 4.1.0
   */
  [[nodiscard]] auto user_data() const noexcept -> UserData*
  {
    return m_userData;
  }

 private:
  SDL_HintCallback m_callback;
  UserData* m_userData;
};

/**
 * \brief Adds a callback to observe changes of the value of the specified hint.
 *
 * \details A callback handle object is returned, which can be used to easily disconnect
 * the callback later. This function can be used with any function object that is
 * stateless, such as traditional function pointers and lambdas. The simplest way to add a
 * callback is with a lambda and no explicit user data.
 *
 * \note The callback will be immediately invoked with the current value of the hint.
 *
 * \note In a future version of centurion (that supports C++20), the signature of the
 * function object will be dependent on the `UserData` type. Unfortunately, this isn't
 * really doable with C++17. Since it requires default-constructible stateless lambdas.
 *
 * \tparam Hint should one of the many hint types defined in this header. However, all it
 * requires is that the type provides a static method that returns a `czstring`.
 * \tparam UserData the type of the user data, defaults to void.
 *
 * \param fun the function object that will be invoked when the hint is updated. The
 * signature should be `void(void*, czstring, czstring, czstring)`.
 * \param userData the user data to associate with the callback.
 *
 * \return a handle to the added callback.
 *
 * \since 4.1.0
 */
template <typename Hint, typename UserData = void>
auto add_hint_callback(SDL_HintCallback fun, UserData* userData = nullptr) noexcept
    -> hint_callback<Hint, UserData>
{
  hint_callback<Hint, UserData> hintCallback{fun, userData};
  hintCallback.connect();
  return hintCallback;
}

/**
 * \brief Clears all stored hints.
 *
 * \see `SDL_ClearHints`
 *
 * \since 4.1.0
 */
inline void clear_hints() noexcept
{
  SDL_ClearHints();
}

/// \} End of group configuration

}  // namespace cen

#endif  // CENTURION_HINTS_HEADER
