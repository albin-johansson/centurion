#ifndef CENTURION_CURSOR_HEADER
#define CENTURION_CURSOR_HEADER

#include <SDL.h>

#include "../detail/owner_handle_api.hpp"
#include "../math/point.hpp"
#include "surface.hpp"
#include "system_cursor.hpp"

namespace cen {

/// \addtogroup video
/// \{

template <typename T>
class basic_cursor;

/**
 * \typedef cursor
 *
 * \brief Represents an owning cursor.
 *
 * \since 5.0.0
 */
using cursor = basic_cursor<detail::owning_type>;

/**
 * \typedef cursor_handle
 *
 * \brief Represents a non-owning cursor.
 *
 * \since 5.0.0
 */
using cursor_handle = basic_cursor<detail::handle_type>;

/**
 * \class basic_cursor
 *
 * \brief Represents a mouse cursor.
 *
 * \ownerhandle `cursor`/`cursor_handle`
 *
 * \since 5.0.0
 *
 * \see `cursor`
 * \see `cursor_handle`
 */
template <typename T>
class basic_cursor final
{
 public:
  /// \name Construction
  /// \{

  /**
   * \brief Creates a cursor based on a cursor type.
   *
   * \param cursor the type of the cursor that will be created.
   *
   * \throws sdl_error if the cursor cannot be created.
   *
   * \since 4.0.0
   */
  template <typename TT = T, detail::is_owner<TT> = 0>
  explicit basic_cursor(const system_cursor cursor)
      : m_cursor{SDL_CreateSystemCursor(static_cast<SDL_SystemCursor>(cursor))}
  {
    if (!m_cursor) {
      throw sdl_error{};
    }
  }

  /**
   * \brief Creates a cursor based on a surface and an associated hotspot.
   *
   * \param surface the icon associated with the cursor.
   * \param hotspot the hotspot that will be used to determine the location of mouse
   * clicks.
   *
   * \throws sdl_error if the cursor cannot be created.
   *
   * \since 4.0.0
   */
  template <typename TT = T, detail::is_owner<TT> = 0>
  basic_cursor(const surface& surface, const ipoint hotspot)
      : m_cursor{SDL_CreateColorCursor(surface.get(), hotspot.x(), hotspot.y())}
  {
    if (!m_cursor) {
      throw sdl_error{};
    }
  }

  /**
   * \brief Creates a handle to a cursor based on a raw pointer.
   *
   * \note This constructor is only available for handles since it would be very easy to
   * introduce subtle bugs by creating owning cursors from `SDL_GetCursor` or
   * `SDL_GetDefaultCursor`, which should not be freed.
   *
   * \param cursor a pointer to the associated cursor.
   *
   * \since 5.0.0
   */
  template <typename TT = T, detail::is_handle<TT> = 0>
  explicit basic_cursor(SDL_Cursor* cursor) noexcept : m_cursor{cursor}
  {}

  /**
   * \brief Creates a handle to an owning cursor.
   *
   * \param owner the associated owning cursor.
   *
   * \since 5.0.0
   */
  template <typename TT = T, detail::is_handle<TT> = 0>
  explicit basic_cursor(const cursor& owner) noexcept : m_cursor{owner.get()}
  {}

  /// \} End of construction

  /// \name Static members
  /// \{

  /**
   * \brief Resets the active cursor to the system default.
   *
   * \since 4.0.0
   */
  static void reset() noexcept
  {
    SDL_SetCursor(SDL_GetDefaultCursor());
  }

  /**
   * \brief Forces a cursor redraw.
   *
   * \since 4.0.0
   */
  static void force_redraw() noexcept
  {
    SDL_SetCursor(nullptr);
  }

  /**
   * \brief Sets whether or not any mouse cursor is visible.
   *
   * \param visible `true` if cursors should be visible; `false` otherwise.
   *
   * \since 4.0.0
   */
  static void set_visible(const bool visible) noexcept
  {
    SDL_ShowCursor(visible ? SDL_ENABLE : SDL_DISABLE);
  }

  /**
   * \brief Returns a handle to the default cursor for the system.
   *
   * \return a handle to the default cursor for the system; might not be present.
   *
   * \since 5.0.0
   */
  [[nodiscard]] static auto get_default() noexcept -> cursor_handle
  {
    return cursor_handle{SDL_GetDefaultCursor()};
  }

  /**
   * \brief Returns a handle to the currently active cursor.
   *
   * \return a handle to the currently active cursor; might not be present.
   *
   * \since 5.0.0
   */
  [[nodiscard]] static auto get_current() noexcept -> cursor_handle
  {
    return cursor_handle{SDL_GetCursor()};
  }

  /**
   * \brief Indicates whether or not cursors are visible.
   *
   * \return `true` if cursors are visible; `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] static auto visible() noexcept -> bool
  {
    return SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE;
  }

  /**
   * \brief Returns the number of system cursors.
   *
   * \return the amount of system cursors.
   *
   * \since 5.0.0
   */
  [[nodiscard]] constexpr static auto count() noexcept -> int
  {
    return SDL_NUM_SYSTEM_CURSORS;
  }

  /// \} End of static members

  /// \name Instance members
  /// \{

  /**
   * \brief Enables the cursor by making it the currently active cursor.
   *
   * \since 4.0.0
   */
  void enable() noexcept
  {
    SDL_SetCursor(m_cursor);
  }

  /**
   * \brief Indicates whether or not this cursor is currently active.
   *
   * \note This function checks whether or not the associated cursor is active by
   * comparing the pointer obtained from `SDL_GetCursor` with the internal pointer.
   *
   * \return `true` if the cursor is currently enabled; `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto is_enabled() const noexcept -> bool
  {
    return SDL_GetCursor() == get();
  }

  /**
   * \brief Returns a pointer to the associated cursor.
   *
   * \warning Don't take ownership of the returned pointer!
   *
   * \return a pointer to the associated cursor.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto get() const noexcept -> SDL_Cursor*
  {
    return m_cursor.get();
  }

  /// \} End of instance members

  /// \name Conversions
  /// \{

  /**
   * \brief Indicates whether or not the cursor handle holds a non-null pointer.
   *
   * \return `true` if the internal pointer is not null; `false` otherwise.
   *
   * \since 5.0.0
   */
  template <typename TT = T, detail::is_handle<TT> = 0>
  explicit operator bool() const noexcept
  {
    return m_cursor != nullptr;
  }

  /// \} End of conversions

 private:
  struct deleter final
  {
    void operator()(SDL_Cursor* cursor) noexcept
    {
      SDL_FreeCursor(cursor);
    }
  };
  detail::pointer_manager<T, SDL_Cursor, deleter> m_cursor;
};

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_CURSOR_HEADER