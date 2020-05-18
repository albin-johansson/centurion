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

#ifndef CENTURION_PATHS_HEADER
#define CENTURION_PATHS_HEADER

#include "centurion_api.h"
#include "centurion_utils.h"

namespace centurion {

/**
 * The BasePath class is a simple wrapper class for a string that represents the
 * application path obtained by SDL_GetBasePath.
 *
 * @since 3.0.0
 */
class BasePath final {
 public:
  /**
   * Constructs an BasePath object that represents the path of the application
   * executable. Note! This might be an expensive operation, so it is
   * recommended to create only one instance of this class and cache it.
   *
   * @since 3.0.0
   */
  CENTURION_API BasePath() noexcept;

  /**
   * Moves the contents of the supplied BasePath into this instance.
   *
   * @param other the BasePath that will be moved.
   * @since 4.0.0
   */
  CENTURION_API BasePath(BasePath&& other) noexcept;

  BasePath(const BasePath&) = delete;

  CENTURION_API ~BasePath() noexcept;

  /**
   * Moves the contents of the supplied BasePath into this instance.
   *
   * @param other the BasePath that will be moved.
   * @since 4.0.0
   */
  CENTURION_API BasePath& operator=(BasePath&& other) noexcept;

  BasePath& operator=(const BasePath&) = delete;

  /**
   * Creates and returns a unique pointer to an BasePath object that represents
   * the path of the application executable. Note! This might be an expensive
   * operation, so it is recommended to create only one instance of this class
   * and cache it.
   *
   * @return a unique pointer to an BasePath instance.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static UniquePtr<BasePath> unique() noexcept;

  /**
   * Creates and returns a shared pointer to an BasePath object that represents
   * the path of the application executable. Note! This might be an expensive
   * operation, so it is recommended to create only one instance of this class
   * and cache it.
   *
   * @return a shared pointer to an BasePath instance.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static SharedPtr<BasePath> shared() noexcept;

  /**
   * Indicates whether or not there is a non-null string in the BasePath object.
   *
   * @return true if the internal string pointer isn't null; false otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  explicit operator bool() const noexcept { return static_cast<bool>(m_path); }

  /**
   * Returns the path of the application executable. The returned pointer might
   * be null!
   *
   * @return the path of the application executable, can be null.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CZString get() const noexcept { return m_path; }

 private:
  ZString m_path = nullptr;

  /**
   * Destroys the resources associated with the BasePath instance.
   *
   * @since 4.0.0
   */
  void destroy() noexcept;

  /**
   * Moves the contents of the supplied BasePath instance into this instance.
   *
   * @param other the instance that will be moved.
   * @since 4.0.0
   */
  void move(BasePath&& other) noexcept;
};

/**
 * The PrefPath class provides a way to obtain the preferred path for where you
 * should store application related files.
 *
 * @since 3.0.0
 */
class PrefPath final {
 public:
  /**
   * Constructs a PrefPath object. Only use letters, numbers, and spaces in the
   * supplied strings!
   *
   * @param org the name of your organization.
   * @param app the name of your application.
   * @since 3.0.0
   */
  CENTURION_API PrefPath(CZString org, CZString app) noexcept;

  /**
   * Moves the contents of the supplied PrefPath into this instance.
   *
   * @param other the PrefPath that will be moved.
   * @since 4.0.0
   */
  CENTURION_API PrefPath(PrefPath&& other) noexcept;

  PrefPath(const PrefPath&) = delete;

  CENTURION_API ~PrefPath() noexcept;

  /**
   * Moves the contents of the supplied PrefPath into this instance.
   *
   * @param other the PrefPath that will be moved.
   * @since 4.0.0
   */
  CENTURION_API PrefPath& operator=(PrefPath&& other) noexcept;

  PrefPath& operator=(const PrefPath&) = delete;

  /**
   * Creates and returns a unique pointer to a PrefPath object. Only use
   * letters, numbers, and spaces in the supplied strings!
   *
   * @param org the name of your organization.
   * @param app the name of your application.
   * @return a unique pointer to a PrefPath instance.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static UniquePtr<PrefPath> unique(CZString org,
                                                  CZString app) noexcept;

  /**
   * Creates and returns a shared pointer to a PrefPath object. Only use
   * letters, numbers, and spaces in the supplied strings!
   *
   * @param org the name of your organization.
   * @param app the name of your application.
   * @return a shared pointer to a PrefPath instance.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static SharedPtr<PrefPath> shared(CZString org,
                                                  CZString app) noexcept;

  /**
   * Indicates whether or not the path object holds a non-null path.
   *
   * @return true if the object holds a non-null path; false otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  explicit operator bool() const noexcept { return static_cast<bool>(m_path); }

  /**
   * Returns a string that represents the preferred path.
   *
   * @return a string that represents the preferred path.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CZString get() const noexcept { return m_path; }

 private:
  ZString m_path = nullptr;

  /**
   * Destroys the resources associated with the PrefPath instance.
   *
   * @since 4.0.0
   */
  void destroy() noexcept;

  /**
   * Moves the contents of the supplied PrefPath instance into this instance.
   *
   * @param other the instance that will be moved.
   * @since 4.0.0
   */
  void move(PrefPath&& other) noexcept;
};

}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "paths.cpp"
#endif

#endif  // CENTURION_PATHS_HEADER