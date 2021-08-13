/**
 * \page page-minimal-centurion-program Minimal Centurion Program
 *
 * The following is a minimal example of a valid Centurion program. All that is required
 * to initialize the library is to create an instance of the `library` class, which must
 * outlive the rest of your program, so it should be the first thing created in your
 * `main` function.
 *
 * \note The signature of the `main` function must be equivalent to `int(int, char**)`.
 *
 * \code{cpp}
 * #include <centurion.hpp>
 *
 * int main(int, char**)
 * {
 *   cen::library centurion;
 *
 *   // The core SDL library along with the extension libraries are now initialized!
 *
 *   return 0;
 * }
 * \endcode
 */