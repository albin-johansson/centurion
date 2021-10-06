#ifndef CENTURION_LOCALE_HEADER
#define CENTURION_LOCALE_HEADER

#include <SDL.h>

#include <cassert>  // assert
#include <memory>   // unique_ptr

#include "../core/integers.hpp"
#include "../core/not_null.hpp"
#include "../core/str.hpp"
#include "../detail/czstring_eq.hpp"
#include "../detail/sdl_deleter.hpp"

namespace cen {

#if SDL_VERSION_ATLEAST(2, 0, 14)

/// \addtogroup system
/// \{

/**
 * \class locale
 *
 * \brief Represents a set of locale entries.
 *
 * \since 5.2.0
 */
class locale final
{
 public:
  /**
   * \brief Returns the current preferred locales on the system.
   *
   * \note The preferred locales might change during the execution of the program.
   *
   * \return the preferred locales on the system.
   *
   * \since 5.2.0
   */
  [[nodiscard]] static auto get_preferred() noexcept -> locale
  {
    return locale{SDL_GetPreferredLocales()};
  }

  /**
   * \brief Indicates whether or not a language (and optionally a country) is part of the
   * locale.
   *
   * \param language the language that will be checked, e.g. "en" for english.
   * \param country optional country code that will be checked, e.g. "US" or "GB".
   *
   * \return `true` if the specified language and country is a part of the locale; `false`
   * otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_language(const not_null<str> language,
                                  const str country = nullptr) const noexcept -> bool
  {
    assert(language);

    if (const auto* array = m_locales.get()) {
      for (auto index = 0u; array[index].language; ++index) {
        const auto& item = array[index];

        if (country && item.country) {
          if (detail::czstring_eq(language, item.language) &&
              detail::czstring_eq(country, item.country)) {
            return true;
          }
        }
        else {
          if (detail::czstring_eq(language, item.language)) {
            return true;
          }
        }
      }
    }

    return false;
  }

  /**
   * \brief Returns the amount of entries in the locale.
   *
   * \return the amount of locale entries.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto count() const noexcept -> usize
  {
    usize result{0};

    if (const auto* array = m_locales.get()) {
      for (auto index = 0u; array[index].language; ++index) {
        ++result;
      }
    }

    return result;
  }

  /**
   * \brief Indicates whether or not the locale contains a non-null pointer.
   *
   * \note It's safe to call all member functions of this class, no matter if there is a
   * non-null internal pointer. This is intended as a quick and easy check to determine
   * whether or not there are any entries at all.
   *
   * \return `true` if the locale contains a non-null pointer; `false` otherwise.
   *
   * \since 5.2.0
   */
  explicit operator bool() const noexcept
  {
    return m_locales.operator bool();
  }

 private:
  std::unique_ptr<SDL_Locale, detail::sdl_deleter<SDL_Locale>> m_locales;

  explicit locale(SDL_Locale* locales) noexcept : m_locales{locales}
  {}
};

/// \} End of group system

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

}  // namespace cen

#endif  // CENTURION_LOCALE_HEADER
