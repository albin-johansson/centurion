#include "centurion_exception.h"
#include <type_traits>

namespace centurion {

static_assert(std::is_default_constructible_v<CenturionException>);
static_assert(std::is_nothrow_destructible_v<CenturionException>);
static_assert(std::is_final_v<CenturionException>);

CenturionException::CenturionException(const char* msg)
    : msg{msg ? msg : "N/A"} {}

CenturionException::CenturionException(const std::string& msg)
    : msg{msg} {}

const char* CenturionException::what() const noexcept {
  return msg.c_str();
}

}