#ifndef CENTURION_DETAIL_ADDRESS_OF_HEADER
#define CENTURION_DETAIL_ADDRESS_OF_HEADER

#include <sstream>  // ostringstream
#include <string>   // string

#include "../centurion_cfg.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

/// \cond FALSE
namespace cen::detail {

/**
 * \brief Returns a string that represents the memory address of the supplied
 * pointer.
 *
 * \details The empty string is returned if the supplied pointer is null.
 *
 * \tparam T the type of the pointer.
 * \param ptr the pointer that will be converted.
 *
 * \return a string that represents the memory address of the supplied
 * pointer.
 *
 * \since 3.0.0
 */
template <typename T>
[[nodiscard]] auto address_of(T* ptr) -> std::string
{
  if (ptr) {
    std::ostringstream address;
    address << static_cast<const void*>(ptr);
    return address.str();
  } else {
    return std::string{};
  }
}

}  // namespace cen::detail
/// \endcond

#endif  // CENTURION_DETAIL_ADDRESS_OF_HEADER
