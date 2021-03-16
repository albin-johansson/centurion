file
====

Represents a file "context" or handle. In other words, this class can represent both typical files in a 
filesystem, but it can also be used for memory streams.

.. note::

  This class differs slightly from other Centurion classes, since it's owning, 
  but it does *not* throw if something goes wrong in a constructor. This is because file 
  operations are error-prone, so we avoid throwing exceptions for performance reasons. Instead, 
  make sure to check the validity of a ``file`` instance through the overloaded ``bool`` conversion.

General information
-------------------

=======================  =======================================================
  Property                Value
-----------------------  -------------------------------------------------------
 Default constructible    No
 Copyable                 No
 Movable                  Yes
 Implicit conversions     None
 Explicit conversions     ``bool``
 Overloaded operators     None
 Namespace                ``::cen``
 Since                    5.3.0
=======================  =======================================================

Interface
---------

.. doxygenclass:: cen::file
  :members:
  :undoc-members:
  :outline:
  :no-link:

Related components
------------------

.. doxygenenum:: cen::file_type
  :outline:
  :no-link:

.. doxygenenum:: cen::file_mode
  :outline:
  :no-link: 

.. doxygenenum:: cen::seek_mode
  :outline:
  :no-link:  
