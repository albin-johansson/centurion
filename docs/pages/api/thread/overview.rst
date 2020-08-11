Overview
========

The library provides abstractions of the SDL functions related to threading and synchronization,
which makes it harder to make silly mistakes, such as forgetting to unlock or destroy a mutex. However,
if you know that your target platforms support the abstractions provided by the C++ standard library, then you 
might want to consider using those instead.
