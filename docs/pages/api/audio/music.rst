music
=====

The ``music`` class represents a piece of music. The supported file formats are: WAVE/RIFF (``.wav``), 
AIFF (``.aiff``), VOC (``.voc``), OGG (``.ogg``), MIDI (``.mid``), OggVorbis (``.ogg``), MP3 (``.mp3``),
FLAC (``.flac``) and MOD (``.mod``, ``.xm``, ``.s3m``, ``.669``, ``.it``, ``.med``, etc.).

.. note::

  Unlike sound effects, only one ``music`` instance can be playing at any time. For this reason, many of the 
  functions provided in the ``music`` interface are static.

General information
-------------------

======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Default constructible    No
Copyable                 No
Movable                  Yes
Implicit conversions     None
Explicit conversions     ``Mix_Music*``, ``const Mix_Music*``
Overloaded operators     ``<<``
Printable                Yes
Namespace                ``::centurion``
Header                   ``music.hpp``
Since                    3.0.0
======================  =========================================

Interface
---------

.. doxygenclass:: centurion::music
  :members:
  :undoc-members:
  :outline:
  :no-link:

Examples
--------

Basic playback
~~~~~~~~~~~~~~

.. code-block:: C++

  #include <centurion_as_ctn.hpp>
  #include <music.hpp>

  void demo()
  {
    ctn::music music{"never_gonna_give_you_up.mp3"};
    using ms = ctn::milliseconds<int>;

    // play music one time
    music.play();

    // pause the playing music
    ctn::music::pause();

    // indicates whether or not the music is paused
    if (ctn::music::is_paused()) {
      // ...
    }

    // resume playback of music
    ctn::music::resume();
    ctn::music::pause();

    // play music two times
    music.play(2);
    ctn::music::pause();

    // loop music forever
    music.play(ctn::music::loopForever);

    // indicates whether or not any music is playing
    if (ctn::music::is_playing()) {
      // ...
    }

    ctn::music::pause();
  }

Fading music in and out
~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: C++

  #include <centurion_as_ctn.hpp>
  #include <music.hpp>

  void demo()
  {
    ctn::music music{"never_gonna_give_you_up.mp3"};

    using ms = ctn::milliseconds<int>;
    using secs = ctn::seconds<int>;

    // fade in music
    music.fade_in(ms{576});

    // unlike pause, this halts any playing OR fading music
    ctn::music::halt();

    // fade in music during first playback, then loop normally
    music.fade_in(ms{576}, 2);

    // checks whether or not any music is currently fading
    if (ctn::music::is_fading()) {
      // ...
    }

    ctn::music::halt();

    // fade out music
    music.fade_out(secs{5});
  }