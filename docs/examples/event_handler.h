/**
 * \page page-event-handler Event Handler
 *
 * __Synopsis:__ Demonstrates the basics of the `event_handler` API.
 *
 * The `event_handler` class is the main interface for working with events in the Centurion
 * library, through which there are a couple of different ways to query information about
 * pending events.
 *
 * First of, the templated overload of `event_handler::is()` takes an event type, and simply
 * checks whether the pending event is of the specified type. However, this function is limited
 * to checking for events that have dedicated event types, which far from all event types have.
 * For more widely applicable and fine-grained checks, the `event_handler::is(event_type)`
 * function can be used to check whether the pending event is of a specific type.
 *
 * Furthermore, there are more direct getters to retrieve the representations of the pending
 * event, using the `event_handler::get<T>()` and `event_handler::try_get<T>()` functions. The
 * `get<T>()` function throws an exception if the pending event is of a different type, whilst
 * `try_get<T>()` is a non-throwing alternative.
 *
 * The demo shows the basics of how to create a program that can respond to system events. The
 * window will change color every time a keyboard button is pressed, and the last mouse press
 * in the window is also displayed.
 *
 * \include event-handler/demo.cpp
 */
