/**
 * @brief Only contains documentation for Doxygen.
 * @note Don't include this file, there's no code in it!
 * @file centurion_docs.h
 * @author Albin Johansson
 * @date 2019-2020
 * @copyright MIT License
 * @since 4.0.0
 */

/**
 * @mainpage notitle
 *
 * @section what_is_centurion What is Centurion?
 * Centurion is a modern C++ library built on top of SDL2 in order to improve
 * type-safety, memory safety and overall ease-of-use. It can be used for
 * creating windows, 2D-rendering, keyboard input, mouse input, sound effects,
 * music, etc. In other words, most of the things you can do with SDL2. In
 * addition to this, all Centurion components are built to support being used
 * alongside the SDL2 components so that you can use SDL2 for the things that
 * Centurion doesn't cover.
 *
 * @section why_use_centurion Why use Centurion?
 * Centurion is written in modern C++17 (and supports being used in C++11 and
 * C++14 environments) and as such is much more intuitive and easy to use that
 * raw SDL2, which is written in C. No need to worry about memory leaks and
 * ownership of resources! By using Centurion you will write code that is
 * type-safe, clear and efficient.
 *
 * @section how_to_install How do I install Centurion?
 * There are two ways of installing the Centurion library in your project.
 * <ul>
 *   <li>
 *     You can simply link against a dynamic library file, just like any other
 *     library. This is the recommended approach for using the Centurion
 *     library.
 *   </li>
 *   <li>
 *     You can use the library as a header only library, by defining the macro
 *     CENTURION_HEADER_ONLY in the file centurion_cfg.h. This means that you'll
 *     build the library by yourself when you compile your project. This option
 *     might lead to better performance due to more inlining, at the cost of
 *     longer compilation times.
 *   </li>
 * </ul>
 * Since Centurion is built on top of SDL2, you'll
 * need to install SDL2! In order to be able use everything in Centurion,
 * you'll need to install SDL2, SDL2_image, SDL2_ttf and SDL2_mixer.
 *
 * @section how_to_use How do I use Centurion?
 * Before you can get started with using the Centurion components, you'll
 * need to initialize the library! Here's how to do just that. See the
 * documentation for the various Centurion components for details and examples.
 * @code{.cpp}
 *   #include <centurion.h>
 *
 *   int main(int, char**)
 *   {
 *     using namespace centurion;
 *     Centurion c;
 *
 *     // The library is now initialized and ready for use!
 *
 *     return 0;
 *   }
 * @endcode
 */

/**
 * @page centurion_101 Centurion 101
 * This page covers the basics of the Centurion library, which makes reading the
 * documentation easier.
 *
 * @section api_conventions API Conventions
 * This section discusses some of the general conventions utilized by the
 * Centurion library.
 *
 * @subsection implementation_details Implementation details
 * Some components, methods and aliases in the Centurion library reside in the
 * <code>centurion::detail</code> namespace (or a namespace that ends with
 * <code>::detail</code>). These are reserved for use solely in the
 * implementation of the library, and might change without notice at any time.
 * So don't explicitly use anything from a detail namespace.
 *
 * @subsection factory_methods Factory methods
 * Many Centurion components feature static factory methods for smart pointers,
 * for convenience. For example, if you're working with a Centurion class
 * <code>T</code>, then you should expect to be able to call
 * <code>T::unique</code>, in order to create a unique pointer to a
 * <code>T</code> instance. The same applies for shared pointers
 *
 * @subsection to_string String representation
 * Many Centurion components feature a <code>to_string()</code> method which
 * returns a textual representation of the component, which can be useful for
 * logging and general debugging.
 *
 * @subsection naming_style Naming style
 * Centurion utilizes a naming convention of setters and getters inspired by Qt.
 * Where if a component has a setter <code>void set_foo(int foo);</code> then
 * you would expect the corresponding getter to be <code>int foo();</code>.
 *
 * @subsection ownership Ownership
 * Since Centurion is a wrapper library for SDL2, it would be very hard to avoid
 * raw pointers completely. The Centurion library adheres to the principle that
 * raw pointers are non-owning by default. This means that if a method of a
 * Centurion component returns <code>T*</code>, then you <b>shouldn't</b> claim
 * ownership of that pointer. Likewise, if a Centurion method takes a
 * <code>T*</code> as its parameter, then the method doesn't claim ownership
 * of the pointer. See the <code>Owner</code> template for explicit markup of
 * ownership.
 *
 * @subsection strings Strings
 * The string type aliases follow a basic naming convention, set by the
 * guidelines support library (GSL), where C = const and Z = null-terminated.
 * See <code>CZString</code> and <code>ZString</code>.
 */

/**
 * @page faq FAQ
 *
 * This document provides answers to some of the common questions and thoughts
 * that you might have about the Centurion library.
 *
 * @section compatibility What versions of C++ can I use Centurion with?
 * Centurion is currently compatible with C++11, C++14 and C++17.
 *
 * @section purpose What is Centurion meant to be used for?
 * Since Centurion is a wrapper for SDL2. You can basically use it for
 * anything that SDL2 is used for.
 *
 * @section allowed_to_do What am I allowed to do with Centurion?
 * Pretty much anything as long as the license is kept with the source code.
 * Centurion uses the MIT license.
 *
 * @section missing_apis Why is X from SDL2 not covered in Centurion?
 * The most likely reason is that it would be *redundant*. The C++ standard
 * library is huge and provides nicer abstractions than what SDL2 can provide in
 * C. However, if you feel like this isn't the case, feel free to request a
 * feature!
 *
 * @section gui_programming Can Centurion be used for GUI programming?
 * Neither SDL2 nor Centurion are GUI-libraries, so there are no built-in GUI
 * components such as buttons or toolbars. If you're looking for a good GUI
 * library then you'd probably want to use something like Qt.
 *
 * @section contributions Can I contribute to Centurion?
 * Yes. Anyone can make pull requests and suggest improvements, new features
 * and/or bug fixes.
 */
