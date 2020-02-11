#include "centurion_exception.h"

namespace centurion {

CenturionException::CenturionException(const char* msg)
    : msg{msg ? msg : "N/A"} {}

CenturionException::CenturionException(const std::string& msg)
    : msg{msg} {}

const char* CenturionException::what() const noexcept {
  return msg.c_str();
}

}