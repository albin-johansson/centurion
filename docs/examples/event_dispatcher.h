/**
 * \page page-event-dispatcher Event Dispatcher
 *
 * The `event_dispatcher` class is designed to reduce the verbosity and clumsiness of
 * having to check for a bunch of different events in the game loop using a long chain of
 * `if`-statements. The basic idea is to specify the events that we want to "subscribe"
 * to, i.e. the events that we are interested in handling, and let the `event_dispatcher`
 * automatically dispatch the subscribed events whenever they occur. There is no
 * requirement to actually bind a subscribed event to a handler, but it makes little sense
 * not to do so. Handlers can be free functions, member functions or even stateful
 * lambdas, as long as they accept an argument equivalent to `const Event&`, where `Event`
 * is the subscribed event.
 *
 * \include event-dispatcher/demo.cpp
 */