Okay,
  I believe writing programs is fun
but compiling, linking them and running
regression tests over and over is not.
So here is one way to help do the busy
work of programming. Use CMAKE.
CMAKE is pretty cool.
I believe it is a step above
Make (though I really do like Makefiles)
in that it is very platform independent,
and it insures that you do not pollute
your source tree with build items.

So, here is a very simple example of
a CMAKE file which builds a library,
an exe that tests the library, and runs
a test on everything.

So... This exercise you will need to:
  1. get cmake on your system
  2. mkdir build
  3. cd build
  4. cmake ..
  5. make all
  6. make test
  7. now you will notice that one of the tests fails,
     you should now:
     1. cd ..
     2. rm -rf build
     3. mkdir build
     4. uncomment the debug option in the cmake file
     5. cd build
     6. cmake ..
     7. make
     8. gdb test_me
     9. set args 6120110403 3 
    10. b main
    11. figure out what's broken





