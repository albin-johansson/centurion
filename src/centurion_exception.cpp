#ifndef CENTURION_EXCEPTION_SOURCE
#define CENTURION_EXCEPTION_SOURCE

#include "centurion_exception.h"

namespace centurion {

CENTURION_DEF
CenturionException::CenturionException(const char* msg) : msg{msg ? msg : "N/A"}
{}

CENTURION_DEF
CenturionException::CenturionException(const std::string& msg) : msg{msg}
{}

CENTURION_DEF
CenturionException::CenturionException(const CenturionException& other) noexcept
    : msg{other.msg}
{}

CENTURION_DEF
const char* CenturionException::what() const noexcept
{
  return msg.c_str();
}

CENTURION_DEF
CenturionException::~CenturionException() noexcept = default;

}  // namespace centurion

#endif  // CENTURION_EXCEPTION_SOURCE