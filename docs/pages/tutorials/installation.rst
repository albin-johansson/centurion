Installation
============

This tutorial demonstrates the installation process for Centurion. If you've ever used SDL2
before, then this tutorial might be a little basic.

.. note::

  This tutorial assumes that you are using CMake as your build system, and that you've got SDL2
  installed and ready.

As Shared Library
-----------------

Download the latest release of Centurion `here <https://github.com/albin-johansson/Centurion/releases>`_.
Select and download "Source code" as either a zip or tar archive depending on your platform. It
doesn't really matter, the contents are the same. Now, we also need to download the appropriate
pre-compiled binaries. If you're on Windows, you'll want to select one of the MSVC and MinGW
archives. If you're on Linux (Ubuntu), you'll want the GCC version.

Extract the archives wherever you'd like on your system. Proceed to copying the header files in
the ``include`` folder to the library directory of your project. A suggestion for the path of the
headers is ``your-project/lib/centurion``.

In your ``CMakeLists.txt`` file, add the following line, where ``your-target`` is the executable
target in your project.

.. code-block:: cmake

  target_include_directories(your-target SYSTEM PUBLIC ${CENTURION_PATH})

You could set the Centurion path variable with the following line, if you're in your root
``CMakeLists.txt`` file.

.. code-block:: cmake

  set(CENTURION_PATH lib/centurion)

Now your IDE should be able to identify the Centurion library! However, if you try to compile,
you'll get linker errors related to undefined references. This is because we need to link against
the shared library that we previously downloaded. One possible approach is to put the binary in a
directory in your project tree, which is what this tutorial will demonstrate.

Copy the shared library binary to a ``bin`` directory, located in the top-level directory of your
project. Then, add the following line to your root ``CMakeLists.txt`` file.

.. code-block:: cmake

  set(CENTURION_LIBRARY bin/libCenturion${CMAKE_IMPORT_LIBRARY_SUFFIX})

Now add the ``CENTURION_LIBRARY`` variable to your linker directive so that it looks something
like the following.

.. code-block:: cmake

  target_link_libraries(your-target
        PUBLIC ${CENTURION_LIBRARY}
        PUBLIC ${SDL2_IMAGE_LIBRARIES}
        PUBLIC ${SDL2_MIXER_LIBRARIES}
        PUBLIC ${SDL2_TTF_LIBRARIES}
        PUBLIC ${SDL2_LIBRARY})

.. note::

  The order of the arguments for ``target_link_libraries`` can be important for certain compilers.

You should now be able to compile your program without any linker errors. However, we're not
quite done. Your executable needs to be able to find the shared library at runtime. Which means
that we need to ensure that the shared library is located next to the executable. Now, you could
do this manually, but this can get annoying. The following CMake function can be used to copy the
binary directory to the output directory.

.. code-block:: cmake

  # Copies a directory.
  #   target: the associated target.
  #   from: the directory that will be copied.
  #   to: the target destination of the copied directory.
  function(copy_directory_post_build [target [from [to]]])
      add_custom_command(
              TARGET ${ARGV0} POST_BUILD
              COMMAND ${CMAKE_COMMAND} -E copy_directory
              ${ARGV1}
              ${ARGV2})
  endfunction()

Add the following line, using the above function, to automatically copy the binaries after
building the project. The ``BINARY_DIR`` variable is assumed to be set to the path to the binary
directory, such as ``${PROJECT_SOURCE_DIR}/bin``.

.. code-block:: cmake

  copy_directory_post_build(your-target ${BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR})

By now, everything should be in order for you to start using Centurion!

.. note::

  The structure of your project assumed by this tutorial is illustrated in the following diagram.

::

    your-project
    ├───bin
    │   └───libCenturion.so
    ├───lib
    │   └───centurion
    │       └───centurion.hpp
    │       └───...
    └───CMakeLists.txt


As "Header-only"
----------------

If you, for some reason, don't want to use Centurion as a shared library, you can actually use it
as if it was a header-only library! There are some downsides, such as needing to include a lot
more source files and longer compilation times. On the other hand, you *might* see slightly
improved performance due to more inlining. However, no guarantees.

Download the latest release of Centurion from
`here <https://github.com/albin-johansson/Centurion/releases>`_. You don't need to download
anything else that the source code archive. Extract the contents of the archive and put the
headers and the source files (located in the ``include`` and ``src`` directories, respectively) in
the library directory of your project.

Just like with the shared library approach, include the Centurion sources with the following line.

.. code-block:: cmake

  target_include_directories(your-target SYSTEM PUBLIC ${CENTURION_PATH})

Furthermore, you need to tell the Centurion library to go into header-only mode. This is
accomplished by defining the ``CENTURION_HEADER_ONLY`` macro in the ``centurion_cfg.hpp`` header.

This should be all you need to do to use the library!

.. note::

  The structure of your project assumed by this tutorial is illustrated in the following diagram.

::

    your-project
    ├───lib
    │   └───centurion
    │       └───centurion.hpp
    │       └───centurion.cpp
    │       └───...
    └───CMakeLists.txt