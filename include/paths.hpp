/*
 * MIT License
 *
 * Copyright (c) 2019-2020 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @file paths.hpp
 *
 * @brief Provides the `base_path` and `pref_path` classes.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_PATHS_HEADER
#define CENTURION_PATHS_HEADER

#include "centurion_api.hpp"
#include "centurion_utils.hpp"

namespace centurion {

/**
 * @class base_path
 *
 * @brief A wrapper for the application path obtained through `SDL_GetBasePath`.
 *
 * @details There is no guarantee that the application path is obtainable, so
 * you should always check for null when dealing with a base path instance.
 * See the following example.
 * @code{.cpp}
 *   ctn::base_path basePath;
 *   if (basePath) {
 *     // the application path was successfully obtained
 *   } else {
 *     // failed to obtain the application path
 *   }
 * @endcode
 *
 * @see `SDL_GetBasePath`
 *
 * @since 3.0.0
 */
class base_path final {
 public:
  /**
   * @brief Obtains the path of the application executable.
   *
   * @note This might be an expensive operation, so it's recommended to create
   * only one instance of this class and cache it.
   *
   * @since 3.0.0
   */
  CENTURION_API
  base_path() noexcept;

  /**
   * @brief Moves the supplied base path into a new base path instance.
   *
   * @param other the base path instance that will be moved.
   *
   * @since 4.0.0
   */
  CENTURION_API
  base_path(base_path&& other) noexcept;

  base_path(const base_path&) = delete;

  /**
   * @brief Moves the contents of the supplied base path into this instance.
   *
   * @param other the base path instance that will be moved.
   *
   * @return the base path that absorbed the supplied base path.
   *
   * @since 4.0.0
   */
  CENTURION_API
  auto operator=(base_path&& other) noexcept -> base_path&;

  auto operator=(const base_path&) -> base_path& = delete;

  /**
   * @brief Frees the base path string.
   */
  CENTURION_API
  ~base_path() noexcept;

  /**
   * @copydoc BasePath()
   */
  CENTURION_QUERY
  static auto unique() -> std::unique_ptr<base_path>;

  /**
   * @copydoc BasePath()
   */
  CENTURION_QUERY
  static auto shared() -> std::shared_ptr<base_path>;

  /**
   * @brief Indicates whether or not there is a non-null string in the base path
   * instance.
   *
   * @return `true` if the internal string is non-null; `false` otherwise.
   *
   * @since 3.0.0
   */
  [[nodiscard]] explicit operator bool() const noexcept
  {
    return static_cast<bool>(m_path);
  }

  /**
   * @brief Returns the path of the application executable.
   *
   * @note The returned pointer might be null! You should always check the
   * returned pointer.
   *
   * @return the path of the application executable, might be `nullptr`.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto get() const noexcept -> czstring { return m_path; }

 private:
  zstring m_path{nullptr};

  /**
   * @brief Destroys the resources associated with the base path instance.
   *
   * @since 4.0.0
   */
  void destroy() noexcept;

  /**
   * @brief Moves the contents of the supplied base path instance into this
   * instance.
   *
   * @param other the base path that will be moved.
   *
   * @since 4.0.0
   */
  void move(base_path&& other) noexcept;
};

/**
 * @class pref_path
 *
 * @brief A wrapper for the preferred path for storing application related
 * files.
 *
 * @details This class is used to obtain the "pref dir". Where users are
 * meant to write personal files (such as preferences and save games, etc) that
 * are specific to your application. This directory is unique per user, per
 * application.
 *
 * @par Usage
 * You should always check that a `pref_path` instance holds a valid string
 * before using the associated string. See the following example.
 * @code{.cpp}
 *   ctn::pref_path prefPath{"my organization", "my awesome app"};
 *   if (prefPath) {
 *     // the preferred path was successfully obtained
 *   } else {
 *     // failed to obtain the preferred path
 *   }
 * @endcode
 *
 * @since 3.0.0
 *
 * @see `SDL_GetPrefPath`
 *
 * @headerfile paths.hpp
 */
class pref_path final {
 public:
  /**
   * @brief Constructs a `pref_path` instance.
   *
   * @note Only use letters, numbers, and spaces in the supplied strings!
   *
   * @param org the name of your organization.
   * @param app the name of your application.
   *
   * @since 3.0.0
   */
  CENTURION_API
  pref_path(czstring org, czstring app) noexcept;

  /**
   * @brief Creates a `pref_path` instance by moving the supplied instance.
   *
   * @param other the `pref_path` instance that will be moved.
   *
   * @since 4.0.0
   */
  CENTURION_API
  pref_path(pref_path&& other) noexcept;

  pref_path(const pref_path&) = delete;

  /**
   * @brief Frees the associated string.
   */
  CENTURION_API
  ~pref_path() noexcept;

  /**
   * @brief Moves the contents of the supplied `pref_path` into this instance.
   *
   * @param other the instance that will be moved.
   *
   * @since 4.0.0
   */
  CENTURION_API
  auto operator=(pref_path&& other) noexcept -> pref_path&;

  auto operator=(const pref_path&) -> pref_path& = delete;

  /**
   * @copydoc pref_path(czstring, czstring)
   */
  CENTURION_QUERY
  static auto unique(czstring org, czstring app) noexcept
      -> std::unique_ptr<pref_path>;

  /**
   * @copydoc pref_path(czstring, czstring)
   */
  CENTURION_QUERY
  static auto shared(czstring org, czstring app) noexcept
      -> std::shared_ptr<pref_path>;

  /**
   * @brief Indicates whether or not the instance holds a non-null path.
   *
   * @return `true` if the object holds a non-null path; `false` otherwise.
   *
   * @since 3.0.0
   */
  [[nodiscard]] explicit operator bool() const noexcept
  {
    return static_cast<bool>(m_path);
  }

  /**
   * @brief Returns a string that represents the preferred path.
   *
   * @return a string that represents the preferred path.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto get() const noexcept -> czstring { return m_path; }

 private:
  zstring m_path{nullptr};

  /**
   * @brief Destroys the resources associated with the instance.
   *
   * @since 4.0.0
   */
  void destroy() noexcept;

  /**
   * @briefMoves the contents of the supplied `pref_path` instance into this
   * instance.
   *
   * @param other the instance that will be moved.
   *
   * @since 4.0.0
   */
  void move(pref_path&& other) noexcept;
};

}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "paths.cpp"
#endif

#endif  // CENTURION_PATHS_HEADER