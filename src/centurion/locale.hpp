#ifndef CENTURION_LOCALE_HPP_
#define CENTURION_LOCALE_HPP_

#include <SDL.h>

#include <cassert>  // assert
#include <cstddef>  // size_t
#include <memory>   // unique_ptr

#include "detail/sdl_deleter.hpp"
#include "detail/stdlib.hpp"

namespace cen {

#if SDL_VERSION_ATLEAST(2, 0, 14)

class Locale final {
 public:
  /* Returns the current preferred locales on the system. */
  [[nodiscard]] static auto GetPreferred() noexcept -> Locale
  {
    return Locale{SDL_GetPreferredLocales()};
  }

  /* Indicates whether a language (and optionally a country) is a part of the locale. */
  [[nodiscard]] auto HasLanguage(const char* language,
                                 const char* country = nullptr) const noexcept -> bool
  {
    assert(language);

    if (const auto* array = mLocales.get()) {
      for (auto index = 0u; array[index].language; ++index) {
        const auto& item = array[index];

        if (country && item.country) {
          if (detail::cmp(language, item.language) && detail::cmp(country, item.country)) {
            return true;
          }
        }
        else {
          if (detail::cmp(language, item.language)) {
            return true;
          }
        }
      }
    }

    return false;
  }

  /* Returns the amount of entries in the locale. */
  [[nodiscard]] auto GetSize() const noexcept -> std::size_t
  {
    std::size_t result{0};

    if (const auto* array = mLocales.get()) {
      for (auto index = 0u; array[index].language; ++index) {
        ++result;
      }
    }

    return result;
  }

  /* Indicates whether the locale contains a non-null pointer. */
  explicit operator bool() const noexcept { return mLocales != nullptr; }

 private:
  std::unique_ptr<SDL_Locale, detail::SDLDeleter> mLocales;

  explicit Locale(SDL_Locale* locales) noexcept : mLocales{locales} {}
};

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

}  // namespace cen

#endif  // CENTURION_LOCALE_HPP_
