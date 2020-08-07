Threads API
===========

The library provides abstractions of the SDL functions related to threading and synchronization,
which makes it harder to make silly mistakes, such as forgetting to unlock or destroy a mutex. However,
if you know that your target platforms support the abstractions provided by the C++ standard library, then you 
might want to consider using those instead.

-----------------------------------------------------------------

thread (class)
--------------

The ``thread`` class represents a single thread of execution. It has been purposefully designed to feature an API that is 
simliar to that of ``std::thread``. However, unlike ``std::thread``, ``thread`` will automatically join itself upon destruction.

General information
~~~~~~~~~~~~~~~~~~~

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
Namespace                ``::centurion``
Header                   ``thread.hpp``
======================  =========================================

Interface 
~~~~~~~~~

.. doxygenclass:: centurion::thread
  :members:
  :undoc-members:
  :outline:
  :no-link:

Examples
~~~~~~~~

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
  #include <centurion_as_ctn.hpp>

  int main(int, char**)
  {
    std::cout << "Simple thread test: \n";

    ctn::thread thread{[](void* data) -> int {
      int count{};
  
      for (; count < 10; ++count) {
        std::cout << "Thread counter: " << count << '\n';
        ctn::thread::sleep(ctn::milliseconds<u32>{50});
      }
  
      return count;
    }, "TestThread"};

    const auto ret = thread.join();
    std::cout << "Thread returned value: " << ret << '\n';

    return 0;
  }

-----------------------------------------------------------------

mutex (class)
-------------

The ``mutex`` class represents a recursive mutex.

.. note:: 

  Whilst it's possible to use ``mutex`` directly, it's recommended to use 
  one of the lock types for actually locking and unlocking the mutex.

General information
~~~~~~~~~~~~~~~~~~~

======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Default constructible    No
Copyable                 No
Movable                  Yes
Implicit conversions     None
Explicit conversions     None
Overloaded operators     None
Printable                No
Namespace                ``::centurion``
Header                   ``mutex.hpp``
======================  =========================================

Interface 
~~~~~~~~~

.. doxygenclass:: centurion::mutex
  :members:
  :undoc-members:
  :outline:
  :no-link:

-----------------------------------------------------------------

Locks
-----

There are two different locks provided in the library, ``scoped_lock`` and ``try_lock``.

-----------------------------------------------------------------

scoped_lock (class)
~~~~~~~~~~~~~~~~~~~

The ``scoped_lock`` class represents an RAII-style blocking lock that automatically unlocks the associated mutex
upon destruction. It will blocking the invoking thread until the mutex becomes available.

General information
^^^^^^^^^^^^^^^^^^^

======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Default constructible    No
Copyable                 No
Movable                  Yes
Implicit conversions     None
Explicit conversions     None
Overloaded operators     None
Printable                No
Namespace                ``::centurion``
Header                   ``scoped_lock.hpp``
======================  =========================================

Interface 
^^^^^^^^^

.. doxygenclass:: centurion::scoped_lock
  :members:
  :undoc-members:
  :outline:
  :no-link:

Examples
^^^^^^^^

The trivial operation of locking a mutex is actually quite tricky in raw SDL2, see the following example.

.. code-block:: c

  SDL_mutex *mutex;
      
  mutex = SDL_CreateMutex();
  if (!mutex) {
    fprintf(stderr, "Couldn't create mutex\n");
    return;
  }
      
  if (SDL_LockMutex(mutex) == 0) {
    /* Do stuff while mutex is locked */
    SDL_UnlockMutex(mutex);
  } else {
    fprintf(stderr, "Couldn't lock mutex\n");
  }
      
  SDL_DestroyMutex(mutex);

With ``mutex`` and ``scoped_lock``, locking a mutex is truly trivial, as it should be.

.. code-block:: c++

  ctn::mutex mutex;
  {
    ctn::scoped_lock lock{mutex};

    /* Do stuff while mutex is locked */

  } // lock is automatically unlocked
  
-----------------------------------------------------------------

try_lock (class)
~~~~~~~~~~~~~~~~

The ``try_lock`` class represents an RAII-style non-blocking lock that automatically unlocks the associated mutex
upon destruction. It immediately returns after trying to lock a mutex.

General information
^^^^^^^^^^^^^^^^^^^

======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Default constructible    No
Copyable                 No
Movable                  Yes
Implicit conversions     None
Explicit conversions     None
Overloaded operators     None
Printable                No
Namespace                ``::centurion``
Header                   ``try_lock.hpp``
======================  =========================================

Interface 
^^^^^^^^^

.. doxygenclass:: centurion::try_lock
  :members:
  :undoc-members:
  :outline:
  :no-link:

Example
^^^^^^^

The ``try_lock`` class can be used in two different ways. The terse syntax is useful if you don't care whether or not the
lock timed out.

.. code-block:: c++

  ctn::mutex mutex;
  if (ctn::try_lock lock{mutex}; lock.success()) {
    // succeeded to lock mutex
  } else if (lock.timed_out()) {
    // timed out whilst trying to lock
  } else {
    // error locking mutex
  }

  // terse syntax
  ctn::try_lock lock{mutex};
  if (lock) {
    // succeeded to lock mutex
  }

-----------------------------------------------------------------

condition (class)
-----------------

Condition variables are represented by the ``condition`` class. These can be used by threads to send signals to each other.

General information
~~~~~~~~~~~~~~~~~~~

======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Default constructible    Yes
Copyable                 No
Movable                  Yes
Implicit conversions     None
Explicit conversions     None
Overloaded operators     None
Printable                No
Namespace                ``::centurion``
Header                   ``condition.hpp``
======================  =========================================

Interface 
~~~~~~~~~

.. doxygenclass:: centurion::condition
  :members:
  :undoc-members:
  :outline:
  :no-link:

Example
~~~~~~~

The following is a typical use case of condition variables. This is adapted from the SDL example 
that can be found `here <https://wiki.libsdl.org/SDL_CreateCond>`_.

.. code-block:: c++ 

  bool condition{};

  ctn::mutex m;
  ctn::condition cond;

  Thread A:
    ctn::scoped_lock lock{m};
    while (!condition) {
      cond.wait(m);
    }

  Thread B:
    ctn::scoped_lock lock{m};
    // ...
    condition = true;
    // ...
    cond.signal();

-----------------------------------------------------------------

semaphore (class)
-----------------

The ``semaphore`` class represents a semaphore with a set of tokens.

General information
~~~~~~~~~~~~~~~~~~~

======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Default constructible    No
Copyable                 No
Movable                  Yes
Implicit conversions     None
Explicit conversions     None
Overloaded operators     None
Printable                No
Namespace                ``::centurion``
Header                   ``semaphore.hpp``
======================  =========================================

Interface 
~~~~~~~~~

.. doxygenclass:: centurion::semaphore
  :members:
  :undoc-members:
  :outline:
  :no-link:

Example
~~~~~~~

The following example demonstrates typical usage of semaphores, it's based on an SDL example which 
can be found `here <https://wiki.libsdl.org/SDL_SemWait>`_. Note that the example uses ``std::atomic<T>`` 
instead of the SDL atomic facilities, since the standard library provides a much richer interface.

.. code-block:: c++

  std::atomic<bool> done{false},
  ctn::semaphore sem{0};  // no initial tokens
  
  Thread A:
    while (!done.load()) {
      add_data_to_queue();
      sem.release();  // returns a token to the semaphore
    }

  Thread B:
    while (!done.load()) {
      sem.acquire();  // takes a token from the semaphore
      if (data_available()) {
        get_data_from_queue();
      }
    }

  done = true;
  sem.release();
  wait_for_threads();

-----------------------------------------------------------------

