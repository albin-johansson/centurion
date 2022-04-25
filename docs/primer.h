/**
 * \page primer Primer
 *
 * \tableofcontents
 *
 * This page goes through important core concepts related to the Centurion APIs.
 *
 * \section impl-details Implementation Details
 * All implementation details used by the library are located in the `cen::detail`
 * namespace. **Do not use anything from this namespace directly!** Implementation details
 * are subject to change and/or removal often and without notice.
 *
 * \section owners-handles-primer Owners and Handles
 * One of the most important concepts for understanding the Centurion APIs is the notion
 * of "owners" and "handles". In a nutshell, some Centurion classes come in two flavours,
 * where the differences lie in whether or not they own their associated resources. You
 * can read more about owners and handles here: \ref owners-and-handles.
 *
 * \section raw-pointer-ownership Ownership of Raw Pointers
 * In accordance to the [C++ Core
 * Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines), all raw
 * pointers in the Centurion APIs should be considered non-owning. In other words, if a
 * function returns a raw pointer, you should not claim ownership of it. Likewise, if a
 * function takes a raw pointer as a parameter, it does not claim ownership of it.
 *
 * Owning raw pointers are marked explicitly using the `owner` alias. Additionally,
 * there's the `maybe_owner` alias which is used in certain constructors for owner/handle
 * classes, for which the owning version claims ownership of the pointer, and the handle
 * version does not.
 *
 * \section non-null-pointers Non-Null Pointers
 * Wherever possible, assertions will abort the execution of the program in debug builds if a
 * null pointer is supplied to an API that does not allow them. In general, make sure to avoid
 * passing null C-style strings (`const char*`), since that is generally disallowed.
 *
 * \section stringification Stringification
 * Most Centurion classes and enums feature stringification support in the form of
 * overloads of the `to_string()` function. Additionally, all classes and enums that
 * provide a `to_string()` overload also provide an overload of `operator<<`, for use with
 * standard streams such as `std::cout` and `std::clog`.
 *
 * \section serialization Serialization
 * Certain Centurion classes provide serialization support, using the API of the
 * [Cereal](https://github.com/USCiLab/cereal) library. In other words, the classes that
 * support serialization either provide a `serialize()` member function or an
 * associated overload of `serialize()` in the form of a free function. These functions
 * accept a generic "archive", on which `operator()` is applied to serialize the
 * associated data. As a result, you do **not** need to install Cereal to use Centurion,
 * and it should be relatively straight forward to write archive wrappers for use with
 * other serialization libraries.
 */