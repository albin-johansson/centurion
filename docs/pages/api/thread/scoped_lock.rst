scoped_lock
===========

The ``scoped_lock`` class represents an RAII-style blocking lock that automatically unlocks the associated mutex
upon destruction. It will blocking the invoking thread until the mutex becomes available.

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
Header                   ``scoped_lock.hpp``
======================  =========================================

Interface 
---------

.. doxygenclass:: centurion::scoped_lock
  :members:
  :undoc-members:
  :outline:
  :no-link:

Examples
--------

The trivial operation of locking a mutex is actually quite tricky in raw SDL2, see the following example.

.. code-block:: c
  :linenos:
  
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
  :linenos:

  cen::mutex mutex;
  {
    cen::scoped_lock lock{mutex};

    /* Do stuff while mutex is locked */

  } // mutex is automatically unlocked
  