This is a utility for tracking when and
how things change. This is really handy when
using multiple threads or in a driver.
There is very simple example test application
included. It may be fun to use this library
in the previous example to show how long it
takes to find factors in a large set of numbers.

In order to use this library, you need to
download gtkwave. Gtkwave is a utility for
reading vcd (Value Change Dump) files. A vcd
file is what this utility dumps out at the
end of a run.

What libvcdio does:
  Specifically this utility logs events
into a series of queues. When it is time to
finish up data is written to a specified
VCD file. The api consists of:
  vcdio_create()
  vcdio_create_stream()
  vcdio_start()
  vcdio_add()
  vcdio_close()

For more information check out the example
main.c and the header file vcdio.h

To run the example do the following:
  mkdir build
  cd build
  cmake ..
  make all
  make test
  gtkwave foobar.vcd
