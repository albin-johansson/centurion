/**
 * \page owners-and-handles Owners and Handles
 *
 * \tableofcontents
 *
 * \section intro Introduction
 *
 * An important aspect of the Centurion library is the concept of owners and handles.
 * Certain classes in the library come in two "flavours", where the difference is in their
 * ownership semantics. For instance, you can default construct a `window` instance and
 * don’t have to worry about memory management at all. Subsequently, you can create a
 * `window_handle` from a raw pointer to a `SDL_Window` which won't manage the lifetime of
 * the supplied pointer at all.
 *
 * You can always create handles from owners, but you can't create owners from handles.
 *
 * \section terminology Terminology
 *
 * * **Owner**: A version of a class with owning semantics, i.e. it manages the lifetime
 * of its associated resources.
 * * **Handle**: A version of a class with non-owning semantics, i.e. it performs no
 * resource management at all.
 *
 * \section syntax Syntax
 *
 * In most cases, you'd want to use the owning versions of Centurion classes. As a result,
 * owners feature the shorter and more obvious names, e.g. `window` is the owning version
 * of `basic_window`. Subsequently, handles always feature a `_handle` suffix. So the
 * handle version of `basic_window` is therefore `window_handle`.
 *
 * \section extensions Extensions
 *
 * Some classes that come in both owner and handle versions may provide API extensions for
 * the owning version. For example, `basic_renderer` provides APIs for automatically
 * translated rendering and font handling with its owning version, `renderer`.
 *
 * \section examples Examples
 *
 * In order to clarify this concept, let’s look at some examples.
 *
 * \code{cpp}
 * #include <centurion.hpp>
 *
 * // Valid usage of an owning window, no need to worry about ownership and lifetimes
 * void basic_owning_window()
 * {
 *   cen::window window;
 *
 *   // Do stuff...
 *
 * } // The window is destroyed
 *
 * // Valid usage of an owning window along with a handle, handles don't claim ownership
 * void valid_handle_usage()
 * {
 *   cen::window window;                 // Creates an owning window
 *   cen::window_handle handle{window};  // Creates a handle to an owning window
 *
 *   // Do stuff...
 *
 * } // The window is only destroyed once, since the handle is non-owning
 *
 * \endcode
 *
 * So what makes owners and handles so useful? Well, let's imagine a simple function like
 * the following, which takes a non-owning pointer to an SDL struct, such as
 * `SDL_Renderer`.
 *
 * \code{cpp}
 * void foo(SDL_Renderer* ptr)
 * {
 *   // Fancy rendering...
 * }
 * \endcode
 *
 * If our codebase features functions like the one in our example and we want to start
 * using Centurion, we might not be able to immediately refactor all such functions in our
 * codebase (there may be a lot of them). So we might be tempted to write something like
 * the following.
 *
 * \code{cpp}
 * void foo(SDL_Renderer* ptr)
 * {
 *   cen::renderer renderer{ptr};  // Claims ownership of the pointer!
 *
 *   // Fancier rendering...
 *
 * } // Oops, the renderer is deleted here!
 * \endcode
 *
 * The problem with the above approach is that **we cannot supply a non-owning pointer to
 * an owning Centurion component**. This is where handles come to the rescue! Handles are
 * perfect for providing a _view_ into the fancy Centurion APIs, without committing
 * ownership of the associated resources. A correct version of the earlier example
 * would look like the following.
 *
 * \code{cpp}
 * void foo(SDL_Renderer* ptr)
 * {
 *   cen::renderer_handle handle{ptr};  // Does not claim ownership of the pointer!
 *
 *   // Fancier rendering...
 *
 * }  // The SDL renderer is not deleted!
 * \endcode
 *
 * Furthermore, handles allow Centurion to provide wrappers for SDL functions that return
 * non-owning raw pointers. For instance, one such function is `SDL_GetWindowFromID()`,
 * which returns `SDL_Window*`. It would be impossible to safely wrap the returned
 * pointers of such functions in Centurion components if we did not have the ability to
 * explicitly specify the ownership semantics. Since we have handles, there is a Centurion
 * function for the aforementioned SDL function, `get_window()`. There are many more
 * examples of this throughout the library.
 */