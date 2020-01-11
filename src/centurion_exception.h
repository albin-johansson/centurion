#pragma once
#include <stdexcept>
#include <string>

namespace centurion {

/**
 * A general exception used by the Centurion library.
 */
class CenturionException final : public std::exception {
 private:
  std::string msg = "";

 public:
  CenturionException();

  /**
   * @param msg the message of the exception.
   */
  explicit CenturionException(const char* msg);

  /**
   * @param msg the message of the exception.
   */
  explicit CenturionException(const std::string& msg);

  /**
   * @param msg the message of the exception.
   */
  explicit CenturionException(std::string&& msg);

  ~CenturionException() override;

  [[nodiscard]]
  const char* what() const noexcept override;
};

}
