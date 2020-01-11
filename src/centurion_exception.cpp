#include "centurion_exception.h"

namespace centurion {

CenturionException::CenturionException() = default;

CenturionException::CenturionException(const char* msg) : msg{msg} {}

CenturionException::CenturionException(const std::string& msg) : msg{msg} {}

CenturionException::CenturionException(std::string&& msg) : msg{msg} {}

CenturionException::~CenturionException() = default;

const char* CenturionException::what() const noexcept {
  return msg.c_str();
}

}