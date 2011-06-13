#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "vcdio.h"

int main(int argc, char **argv)
{
  vcdio *vcdio_ptr;
  int streams[5];
  char name[16];
  int ii;
  int zz;

  if ((argc != 2)||(strcmp(argv[1], "-h") == 0))
  {
    fprintf(stderr, "Usage: %s <vcd filename output>\n", argv[0]);
    fprintf(stderr, "       This application tests the vcdio library\n");
    return(0);
  }

  vcdio_ptr = vcdio_create();
  for (ii = 0; ii < sizeof(streams)/sizeof(int); ++ii)
  {
    sprintf(name, "fred_%d", ii);
    streams[ii] = vcdio_create_stream(vcdio_ptr, name, vcdio_uint_type, 0);
  }

  vcdio_start(vcdio_ptr);

  for (zz = 0; zz < 5; ++zz)
  {
    for (ii = 0; ii < sizeof(streams)/sizeof(int); ++ii)
    {
      vcdio_add(vcdio_ptr, streams[ii], ((zz<<8)+ii));
    }

    usleep(100);
  }

  vcdio_close(vcdio_ptr, "foobar.vcd");
  return(0);
}
