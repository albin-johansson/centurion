/*
 * MIT License
 *
 * Copyright (c) 2019 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once
#include <string>
#include "centurion_api.h"
#include <memory>

namespace centurion {

/**
 * The AppPath class is a simple wrapper class for a string that represents the application path
 * obtained by SDL_GetBasePath.
 *
 * @since 3.0.0
 */
class CENTURION_API AppPath final {
 private:
  char* path = nullptr;

 public:
  /**
   * Constructs an AppPath object that represents the path of the application executable. Note!
   * This might be an expensive operation, so it is recommended to create only one instance of
   * this class and cache it.
   *
   * @since 3.0.0
   */
  CENTURION_API AppPath() noexcept;

  AppPath(const AppPath&) = delete;

  CENTURION_API ~AppPath() noexcept;

  AppPath& operator=(const AppPath&) = delete;

  /**
   * Creates and returns a unique pointer to an AppPath object that represents the path of the
   * application executable. Note! This might be an expensive operation, so it is recommended to
   * create only one instance of this class and cache it.
   *
   * @return a unique pointer to an AppPath instance.
   * @since 3.0.0
   */
  [[nodiscard]]
  static std::unique_ptr<AppPath> unique();

  /**
   * Creates and returns a shared pointer to an AppPath object that represents the path of the
   * application executable. Note! This might be an expensive operation, so it is recommended to
   * create only one instance of this class and cache it.
   *
   * @return a shared pointer to an AppPath instance.
   * @since 3.0.0
   */
  [[nodiscard]]
  static std::shared_ptr<AppPath> shared();

  /**
   * Indicates whether or not there is a non-null string in the app path object.
   *
   * @return true if the internal string pointer isn't null; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API explicit operator bool() const noexcept;

  /**
   * Returns the path of the application executable. The returned pointer might be null!
   *
   * @return the path of the application executable, can be null.
   * @since 3.0.0
   */
  [[nodiscard]]
  const char* get() const noexcept { return path; }
};

/**
 * The PrefPath class provides a way to obtain the preferred path for where you should
 * store application related files.
 *
 * @since 3.0.0
 */
class CENTURION_API PrefPath final {
 private:
  char* path = nullptr;

 public:
  /**
   * Constructs a PrefPath object. Only use letters, numbers, and spaces in the supplied strings!
   *
   * @param org the name of your organization.
   * @param app the name of your application.
   * @since 3.0.0
   */
  CENTURION_API PrefPath(const std::string& org, const std::string& app);

  PrefPath(const PrefPath&) = delete;

  CENTURION_API ~PrefPath() noexcept;

  PrefPath& operator=(const PrefPath&) = delete;

  /**
   * Creates and returns a unique pointer to a PrefPath object. Only use letters, numbers, and
   * spaces in the supplied strings!
   *
   * @param org the name of your organization.
   * @param app the name of your application.
   * @return a unique pointer to a PrefPath instance.
   * @since 3.0.0
   */
  [[nodiscard]]
  static std::unique_ptr<PrefPath> unique(const std::string& org, const std::string& app);

  /**
   * Creates and returns a shared pointer to a PrefPath object. Only use letters, numbers, and
   * spaces in the supplied strings!
   *
   * @param org the name of your organization.
   * @param app the name of your application.
   * @return a shared pointer to a PrefPath instance.
   * @since 3.0.0
   */
  [[nodiscard]]
  static std::shared_ptr<PrefPath> shared(const std::string& org, const std::string& app);

  /**
   * Indicates whether or not the path object holds a non-null path.
   *
   * @return true if the object holds a non-null path; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  explicit operator bool() const noexcept { return path; }

  /**
   * Returns a string that represents the preferred path.
   *
   * @return a string that represents the preferred path.
   * @since 3.0.0
   */
  [[nodiscard]]
  const char* get() const noexcept { return path; }
};

}
