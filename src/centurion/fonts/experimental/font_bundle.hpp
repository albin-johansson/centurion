/*
 * MIT License
 *
 * Copyright (c) 2019-2023 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CENTURION_FONTS_EXPERIMENTAL_FONT_BUNDLE_HPP_
#define CENTURION_FONTS_EXPERIMENTAL_FONT_BUNDLE_HPP_

#ifndef CENTURION_NO_SDL_TTF

#include <cassert>        // assert
#include <ostream>        // ostream
#include <string>         // string, to_string
#include <string_view>    // string_view
#include <unordered_map>  // unordered_map

#include "../../common/errors.hpp"
#include "../../common/primitives.hpp"
#include "../../features.hpp"
#include "../font.hpp"
#include "../font_cache.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen::experimental {

/**
 * Utility for handling fonts of various sizes.
 *
 * The main motivation behind this utility is the fact that it is common to load the same font
 * family in several different sizes. This class provides a simple API for efficiently managing
 * such pools of fonts.
 *
 * This class works by organizing different pools of fonts based on their file paths. Which
 * means that the same font, loaded from different file paths, will be put into different
 * pools.
 *
 * Despite the name, this class actually stores font_cache instances. However, you can still
 * easily extract the underlying font instances if you do not need the extra features provided
 * by the `font_cache` class.
 *
 * \see font
 * \see font_cache
 */
class font_bundle final {
 public:
  using id_type = usize;
  using size_type = usize;

  /**
   * Loads a font in a specific size.
   *
   * It is safe to load a font that has already been previously loaded. Furthermore, this
   * function has no effect if there is already a font of the specified size stored in the pool
   * for the font family.
   *
   * \param path the file path of the font.
   * \param size the size of the font.
   *
   * \return the identifier associated with the font.
   */
  auto load_font(const char* path, const int size) -> id_type
  {
    assert(path);
    if (const auto id = get_id(path)) {
      mPools[*id].caches.try_emplace(size, font {path, size});
      return *id;
    }
    else {
      const auto newId = mNextFontId;

      auto& pack = mPools[newId];
      pack.path = path;
      pack.caches.try_emplace(size, font {path, size});

      ++mNextFontId;

      return newId;
    }
  }

  /// Indicates whether there is a font pool associated with an ID.
  [[nodiscard]] auto contains(const id_type id) const -> bool
  {
    return mPools.find(id) != mPools.end();
  }

  /// Indicates whether there is a pool for the specified file path.
  [[nodiscard]] auto contains(const std::string_view path) const -> bool
  {
    return get_id(path).has_value();
  }

  /// Indicates whether there is a font of a specific size in a pool.
  [[nodiscard]] auto contains(const id_type id, const int size) const -> bool
  {
    if (const auto pack = mPools.find(id); pack != mPools.end()) {
      return pack->second.caches.find(size) != pack->second.caches.end();
    }
    else {
      return false;
    }
  }

  /// Returns a previously loaded font of a particular size from a pool.
  [[nodiscard]] auto at(const id_type id, const int size) -> font_cache&
  {
    if (const auto pool = mPools.find(id); pool != mPools.end()) {
      auto& caches = pool->second.caches;
      if (const auto cache = caches.find(size); cache != caches.end()) {
        return cache->second;
      }
      else {
        throw exception {"No loaded font of the requested size!"};
      }
    }
    else {
      throw exception {"Invalid font pool identifier!"};
    }
  }

  [[nodiscard]] auto at(const id_type id, const int size) const -> const font_cache&
  {
    return mPools.at(id).caches.at(size);
  }

  /**
   * Returns a previously loaded font of a particular size from a pool.
   *
   * This function is provided as a shorthand, and simply calls at() and extracts the font
   * from the found font cache.
   *
   * \param id the identifier of the pool to query.
   * \param size the size of the desired font.
   *
   * \return the found font.
   */
  [[nodiscard]] auto get_font(const id_type id, const int size) -> font&
  {
    return at(id, size).get_font();
  }

  [[nodiscard]] auto get_font(const id_type id, const int size) const -> const font&
  {
    return at(id, size).get_font();
  }

  /// Returns the amount of fonts that have been loaded (including different sizes).
  [[nodiscard]] auto font_count() const noexcept -> size_type
  {
    size_type count = 0;

    for (const auto& [id, pack] : mPools) {
      count += pack.caches.size();
    }

    return count;
  }

  /// Returns the amount of loaded font pools, i.e. font faces irrespective of sizes.
  [[nodiscard]] auto pool_count() const -> size_type { return mPools.size(); }

 private:
  struct font_pool final {
    std::string path;
    std::unordered_map<int, font_cache> caches;  ///< Size -> Cache
  };

  std::unordered_map<id_type, font_pool> mPools;
  id_type mNextFontId {1};

  [[nodiscard]] auto get_id(const std::string_view path) const -> maybe<id_type>
  {
    for (const auto& [id, pack] : mPools) {
      if (!pack.caches.empty()) {
        if (pack.path == path) {
          return id;
        }
      }
    }

    return nothing;
  }
};

[[nodiscard]] inline auto to_string(const font_bundle& bundle) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("font_bundle(#pools: {}, #fonts: {})",
                     bundle.pool_count(),
                     bundle.font_count());
#else
  return "font_bundle(#pools: " + std::to_string(bundle.pool_count()) +
         ", #fonts: " + std::to_string(bundle.font_count()) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

inline auto operator<<(std::ostream& stream, const font_bundle& bundle) -> std::ostream&
{
  return stream << to_string(bundle);
}

}  // namespace cen::experimental

#endif  // CENTURION_NO_SDL_TTF
#endif  // CENTURION_FONTS_EXPERIMENTAL_FONT_BUNDLE_HPP_
