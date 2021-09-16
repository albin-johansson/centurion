#ifndef CENTURION_DETAIL_STATIC_BIMAP_HEADER
#define CENTURION_DETAIL_STATIC_BIMAP_HEADER

#include <algorithm>  // find_if
#include <array>      // array
#include <utility>    // pair

#include "../core/exception.hpp"

/// \cond FALSE
namespace cen::detail {

/**
 * \class static_bimap
 *
 * \brief A bidirectional associative container for when keys and values are known at
 * compile-time.
 *
 * \note This class is only meant to be used in constexpr contexts.
 *
 * \remarks This class was inspired by Jason Turners C++ Weekly video on constexpr maps!
 *
 * \tparam Key the type of the keys, must provide an overloaded `operator==`.
 * \tparam Value the type of the values.
 * \tparam ValueCmp the predicate used to lookup values from keys.
 * \tparam size the amount of key-value pairs.
 *
 * \since 5.0.0
 */
template <typename Key, typename Value, typename ValueCmp, std::size_t Size>
class static_bimap final
{
  using pair_type = std::pair<Key, Value>;
  using storage_type = std::array<pair_type, Size>;

 public:
  storage_type data;

  constexpr auto find(const Key& key) const -> const Value&
  {
    const auto it = std::find_if(data.begin(), data.end(), [&](const pair_type& pair) {
      return pair.first == key;
    });

    if (it != data.end()) {
      return it->second;
    }
    else {
      throw cen_error{"Failed to find element in static map!"};
    }
  }

  constexpr auto key_from(const Value& value) const -> const Key&
  {
    const auto it = std::find_if(data.begin(), data.end(), [&](const pair_type& pair) {
      ValueCmp predicate;
      return predicate(pair.second, value);
    });

    if (it != data.end()) {
      return it->first;
    }
    else {
      throw cen_error{"Failed to find key in static map!"};
    }
  }
};

}  // namespace cen::detail
/// \endcond

#endif  // CENTURION_DETAIL_STATIC_BIMAP_HEADER
