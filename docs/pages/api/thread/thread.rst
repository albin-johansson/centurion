thread
======

The ``thread`` class represents a single thread of execution. It has been purposefully designed to feature an API that is 
simliar to that of ``std::thread``. However, unlike ``std::thread``, ``thread`` will automatically join itself upon destruction.

General information
-------------------

======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Default constructible    No
Copyable                 No
Movable                  Yes
Implicit conversions     None
Explicit conversions     None
Overloaded operators     ``<<``
Printable                Yes
Namespace                ``::cen``
Header                   ``thread.hpp``
======================  =========================================

Interface 
---------

.. doxygenclass:: cen::thread
  :members:
  :undoc-members:
  :outline:
  :no-link:

Examples
--------

The following example is provided on the SDL2 wiki for how you could use the thread API.

.. code-block:: c
  
  #include <stdio.h>
  #include "SDL.h"
  
  /* Very simple thread - counts 0 to 9 delaying 50ms between increments */
  static int TestThread(void *ptr)
  {
      int cnt;
  
      for (cnt = 0; cnt < 10; ++cnt) {
          printf("Thread counter: %d\n", cnt);
          SDL_Delay(50);
      }
  
      return cnt;
  }
  
  int main(int argc, char *argv[])
  {
      SDL_Thread *thread;
      int         threadReturnValue;
  
      printf("Simple SDL_CreateThread test:\n");
  
      /* Simply create a thread */
      thread = SDL_CreateThread(TestThread, "TestThread", (void *)NULL);
  
      if (NULL == thread) {
          printf("SDL_CreateThread failed: %s\n", SDL_GetError());
      } else {
          SDL_WaitThread(thread, &threadReturnValue);
          printf("Thread returned value: %d\n", threadReturnValue);
      }
  
      return 0;
  }

The equivalent Centurion program looks something like the following. Note, the use of a lambda is of course optional, a traditional
function pointer is also valid.

.. code-block:: c++
  
  #include <iostream>

  #include <thread.cpp>
  #include <cen.hpp>

  int main(int, char**)
  {
    using namespace cen::literals;

    std::cout << "Simple thread test: \n";

    auto task = [](void* data) -> int {
      int count{};

      for (; count < 10; ++count) {
        std::cout << "Thread counter: " << count << '\n';
        cen::thread::sleep(50_ms);
      }

      return count;
    };

    cen::thread thread{task, "TestThread"};

    const auto ret = thread.join();
    std::cout << "Thread returned value: " << ret << '\n';

    return 0;
  }
