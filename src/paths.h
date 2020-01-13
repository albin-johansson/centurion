#pragma once
#include <string>

namespace centurion {

/**
 * The AppPath class is a simple wrapper class for a string that represents the application path
 * obtained by SDL_GetBasePath.
 *
 * @since 3.0.0
 */
class AppPath final {
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
  AppPath() noexcept;

  AppPath(const AppPath&) = delete;

  ~AppPath() noexcept;

  AppPath& operator=(const AppPath&) = delete;

  /**
   * Indicates whether or not there is a non-null string in the app path object.
   *
   * @return true if the internal string pointer isn't null; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  explicit operator bool() const noexcept { return path; }

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
class PrefPath final {
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
  PrefPath(const std::string& org, const std::string& app);

  PrefPath(const PrefPath&) = delete;

  ~PrefPath() noexcept;

  PrefPath& operator=(const PrefPath&) = delete;

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
