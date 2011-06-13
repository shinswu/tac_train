Here is an example OpenGL app.
This app draws a cube, then rotates
the cube. A nice exercise here would
be to use the vcdio library and time
the OpenGL timer (No you really won't
find out anything interesting, but you
will know you got things right when
gtkwave reports back a correct timer value).
Now there are many ways to pull the
vcdio library in to this example. Try one
or two.

Note: look at the CMAKE file. See how platform
dependencies are handled.
Add a test to the code and CMAKE files to run through
10 seconds of cubing.
