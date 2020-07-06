#ifndef CENTURION_EXCEPTION_SOURCE
#define CENTURION_EXCEPTION_SOURCE

#include "centurion_exception.hpp"

namespace centurion {

CENTURION_DEF
CenturionException::CenturionException(CZString what) noexcept
    : m_what{what ? what : "N/A"}
{}

CENTURION_DEF
CenturionException::CenturionException(std::string what) noexcept
    : m_what{what.empty() ? "N/A" : what}
{}

CENTURION_DEF
CenturionException::CenturionException(const CenturionException& other) noexcept
    : m_what{other.m_what}
{}

}  // namespace centurion

#endif  // CENTURION_EXCEPTION_SOURCE