#ifndef CENTURION_HINTS_HEADER
#define CENTURION_HINTS_HEADER

#include <SDL.h>

#include <optional>  // optional

#include "../compiler/features.hpp"
#include "../core/exception.hpp"
#include "../core/is_stateless_callable.hpp"
#include "../core/log.hpp"
#include "../core/result.hpp"
#include "../core/str.hpp"
#include "../detail/hints_impl.hpp"
#include "hint_priority.hpp"

namespace cen {

/// \addtogroup hints
/// \{

/**
 * \brief Sets the value of the specified hint.
 *
 * \details This function will only accept values that are related to the
 * specified hint, supplying the wrong kind of value causes a compile-time
 * error. See the related hint class for more details about the associated
 * value type. However, whilst this function is type-safe, it doesn't ensure
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
          detail::enable_if_hint_arg_t<Hint, Value> = 0>
auto set_hint(const Value& value) -> result
{
  return SDL_SetHintWithPriority(Hint::name(),
                                 Hint::to_string(value).c_str(),
                                 static_cast<SDL_HintPriority>(priority)) == SDL_TRUE;
}

/**
 * \brief Returns the current value of the specified hint.
 *
 * \note Many hints aren't actually set by default.
 *
 * \tparam Hint the type of the Hint to obtain the value of.
 *
 * \return the current value of the specified hint; `std::nullopt` if there is
 * no value set for the hint.
 *
 * \since 4.1.0
 */
template <typename Hint>
[[nodiscard]] auto get_hint() -> std::optional<typename Hint::value_type>
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
   * is updated. The signature should be `void(void*, str, str, str)`.
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
    if (!callback) {
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
 * \tparam Hint should one of the many hint types defined in this header. However, all it
 * requires is that the type provides a static function that returns a `str`.
 * \tparam UserData the type of the user data, defaults to void.
 *
 * \param fun the function object that will be invoked when the hint is updated. The
 * signature should be `void(void*, str, str, str)`.
 * \param userData the user data to associate with the callback.
 *
 * \return a handle to the added callback.
 *
 * \see `add_hint_callback_ex()`
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

#if CENTURION_HAS_FEATURE_CONCEPTS

/// \since 6.2.0
template <typename T, typename Hint, typename UserData>
concept is_hint_callback = is_stateless_callable<T,
                                                 UserData*,
                                                 str,
                                                 typename Hint::value_type,
                                                 typename Hint::value_type>;

/**
 * \brief Adds a callback to observe changes of the value of the specified hint.
 *
 * \details This function returns a callback handle object, which can be used to easily
 * disconnect the callback at a later time.
 *
 * \details The signature of the callable should be equivalent to `void(UserData*, str,
 * Hint::value_type, Hint::value_type)`.
 *
 * \note This function can be used with any function object that is stateless, such as
 * traditional function pointers or non-capturing lambdas.
 *
 * \details The following is an example of how usage of this function might look.
 * \code{cpp}
 * auto callable = [](int* data,
 *                    cen::str name,
 *                    cen::hint::render_driver::value_type previous,
 *                    cen::hint::render_driver::value_type current) {
 *   // Do stuff when the value of the hint is updated...
 * };
 *
 * int foo = 42;
 * auto handle = cen::add_hint_callback_ex<render_driver>(callable, &foo);
 * \endcode
 *
 * \tparam Hint the hint type, i.e. one of the types defined in the `cen::hint` namespace.
 * \tparam UserData the type of the optional user data.
 * \tparam Callable the type of the callable.
 *
 * \param fun the function object that will be invoked when the hint is updated.
 * \param data optional user data, can safely be null.
 *
 * \return a callback handle.
 *
 * \see `add_hint_callback()`
 *
 * \since 6.2.0
 */
template <typename Hint, typename UserData = void, is_hint_callback<Hint, UserData> Callable>
auto add_hint_callback_ex([[maybe_unused]] Callable fun, UserData* data = nullptr)
    -> hint_callback<Hint, UserData>
{
  const auto wrapper =
      [](void* erased, const str name, const str oldValue, const str newValue) {
        Callable callable;

        const auto previous = Hint::from_string(oldValue);
        const auto current = Hint::from_string(newValue);

        callable(static_cast<UserData*>(erased), name, previous, current);
      };

  return add_hint_callback<Hint>(wrapper, data);
}

#endif  // CENTURION_HAS_FEATURE_CONCEPTS

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

/// \} End of group hints

}  // namespace cen

#endif  // CENTURION_HINTS_HEADER
