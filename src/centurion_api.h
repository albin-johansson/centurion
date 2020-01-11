#pragma once

// Define CENTURION_API for any platform https://atomheartother.github.io/c++/2018/07/12/CPPDynLib.html
#ifdef _WIN32
# ifdef WIN_EXPORT
#   define CENTURION_API __declspec(dllexport)
# else
#   define CENTURION_API __declspec(dllimport)
# endif
#else
# define CENTURION_API
#endif