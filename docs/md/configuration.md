# Configuration

The library can be configured using the following macros. In general, these macros allow you to
opt-out of certain features, rather than opt-in. All Centurion macros feature the `CENTURION_`
prefix. Remember, you have to define the customization macros *before* you include the Centurion
header.

```C++
#define CENTURION_CONFIGURATION_MACRO
#include <centurion.hpp>

int main(int argc, char** argv) 
{
  cen::library lib;
  
  // ...
  
  return 0;
}
```

## `CENTURION_NO_OPENGL`

Define this macro to exclude the OpenGL API.

## `CENTURION_NO_VULKAN`

Define this macro to exclude the Vulkan API.

## `CENTURION_NO_DEBUG_LOG_MACROS`

Define this macro to exclude the logging macros, e.g. `CENTURION_LOG_INFO`. Note, this eliminates their definition altogether.

## `CENTURION_NO_PRAGMA_ONCE`

Define this macro to prevent usage of `#pragma once` in the Centurion header.
