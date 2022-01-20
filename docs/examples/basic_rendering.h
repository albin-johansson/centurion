/**
 * \page page-basic-rendering Basic Rendering
 *
 * This example demonstrates basic usage of the rendering API. An important aspect to
 * understand is that SDL batches rendering calls behind-the-scenes. This means that an
 * individual rendering call has no immediate effect on the active rendering target.
 * A series of rendering calls must instead be explicitly applied to the render target.
 *
 * Each rendering frame should begin with a call to either `basic_renderer::clear()` or
 * `basic_renderer::clear_with()`, which clears the current rendering target. Then, when
 * all rendering calls have been made for the frame, call `basic_renderer::present()` to
 * present the batched draw calls to the rendering target.
 *
 * \include basic-rendering/demo.cpp
 *
 * Running this example program should result in a window that looks like the following.
 *
 * \image html basic_rendering.png
 */