# Printing

Here I test how to log messages in thread-safe way.

Looks like POSIX [requires](https://man7.org/linux/man-pages/man7/pthreads.7.html)
printf to be thread-safe (as well as almost all other standard funcitons).