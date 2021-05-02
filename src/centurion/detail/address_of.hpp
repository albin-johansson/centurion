#ifndef CENTURION_DETAIL_ADDRESS_OF_HEADER
#define CENTURION_DETAIL_ADDRESS_OF_HEADER

#include <sstream>  // ostringstream
#include <string>   // string

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
[[nodiscard]] auto address_of(const T* ptr) -> std::string
{
  if (ptr)
  {
    std::ostringstream stream;
    stream << static_cast<const void*>(ptr);
    return stream.str();
  }
  else
  {
    return std::string{};
  }
}

}  // namespace cen::detail
/// \endcond

#endif  // CENTURION_DETAIL_ADDRESS_OF_HEADER
