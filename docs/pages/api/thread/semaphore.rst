semaphore
=========

The ``semaphore`` class represents a semaphore with a set of tokens.

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
Overloaded operators     None
Printable                No
Namespace                ``::centurion``
Header                   ``semaphore.hpp``
======================  =========================================

Interface 
---------

.. doxygenclass:: centurion::semaphore
  :members:
  :undoc-members:
  :outline:
  :no-link:

Example
-------

The following example demonstrates typical usage of semaphores, it's based on an SDL example which 
can be found `here <https://wiki.libsdl.org/SDL_SemWait>`_. Note that the example uses ``std::atomic<T>`` 
instead of the SDL atomic facilities, since the standard library provides a much richer interface.

.. code-block:: c++
  :linenos:
  
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
