Logging
=======

The logging API is based on a set of functions contained in the 
``ctn::log`` namespace. Additionally, function macros are provided 
(although they can be disabled), which can be used for logging in 
debug mode, that expand to nothing in release mode.

The logging API is based on a set of different priorities and categories. 
Usually, the priority is specified by selecting one of the ``info``, ``warn``,
``verbose``, ``debug``, ``critical`` and ``error`` functions. The category can 
be explicitly specified as an optional parameter to any of these functions.

For cases when you just want to print a string, there's the ``put`` function, 
which accepts either ``std::string`` or raw C-style strings.

General information
-------------------
======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Namespace                ``::centurion::log``
Header                   ``log.hpp``
Since                    3.0.0
======================  =========================================

Interface
---------

.. doxygennamespace:: centurion::log
  :outline:
  :members:

Examples
--------

Basic logging
~~~~~~~~~~~~~

.. code-block:: C++

  #include <centurion_as_ctn.hpp>
  #include <log.hpp>

  void foo()
  {
    // The simplest logging function 
    ctn::log::put("abc");

    // Traditional formatting is supported
    ctn::log::warn("bar: %i", 42);
  }

Explicit category
~~~~~~~~~~~~~~~~~

All of the logging functions will, if no category is explicitly specified, use the
``app`` category. To use another category, simply provide it as the first parameter.

.. code-block:: C++

  #include <centurion_as_ctn.hpp>
  #include <log.hpp>

  void foo()
  {
    // Prints "Hello" using implicit "app" category
    ctn::log::info("Hello");

    // Prints "World" using the explicitly specified "video" category
    ctn::log::info(ctn::log::category::video, "World");
  }

Debug-only logging macros
~~~~~~~~~~~~~~~~~~~~~~~~~~

Sometimes, it's desirable to remove logging from release builds, in order to
reduce code size, improve performance or simply because it isn't needed. This can 
be accomplished with the ``CENTURION_LOG_`` macros. There's a macro that corresponds 
to each of the standard logging functions.

.. note::

  The logging macros can be disabled by not defining ``CENTURION_USE_DEBUG_LOGGING_MACROS``
  in ``centurion_cfg.hpp``.

.. code-block:: C++

  #include <centurion_as_ctn.hpp>
  #include <log.hpp>

  void foo()
  {
    // This expands to nothing in release mode
    CENTURION_LOG_INFO("Gandalf > Saruman");
  }