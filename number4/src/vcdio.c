/*
  Title: vcdio.c
  Purpose: A library to trace events in a program.
           Events a immediately tracked in memory. When
           the vcd_io_close() call is made all recorded
           events are written out to a Value Change Dump
           (VCD) file.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "vcdio.h"

static char *_int_to_bits(unsigned int val);

/*
    Title: vcdio_create()
    Purpose: create a vcdio object.
*/
vcdio *vcdio_create()
{
  vcdio *vcdio_ptr;


  vcdio_ptr = malloc(sizeof(vcdio));
  if (vcdio_ptr == 0)
  {
    printf("ERROR, Unable to allocate memory. %s(%d)\b", __FILE__, __LINE__);
    exit(1);
  }

  memset(vcdio_ptr, 0, sizeof(vcdio));
  return(vcdio_ptr);
}


/*
    Title: vcdio_create_stream(vcdio vcdio_obj, char *name, int type, int event_size)
    Purpose: create a vcdio stream. This will create a buffer of event_size
             events. A good number to start with would be in the range of a
             couple Million. (If an event is logged every 20 usecs, this
             would record data for 20 seconds if 1 million events were chosen).
             If a value of 0 is given, space for 100,000 events will be
             allocated.
    Returns: Returns the id of the stream. This is actually the 1+index into
             the array of streams maintained by the vcdio_ptr.
*/
int vcdio_create_stream(vcdio *vcdio_ptr, char *name, vcdio_type type, int event_size)
{
  vcdio_stream *stream_ptr;

  if (vcdio_ptr->stream_cnt++)
    vcdio_ptr->streams = realloc(vcdio_ptr->streams, sizeof(vcdio_stream)*vcdio_ptr->stream_cnt);
  else
    vcdio_ptr->streams = malloc(sizeof(vcdio_stream));

  if (vcdio_ptr->streams == 0)
  {
    printf("ERROR, Unable to allocate memory. %s(%d)\b", __FILE__, __LINE__);
    exit(1);
  }

  stream_ptr = &vcdio_ptr->streams[vcdio_ptr->stream_cnt-1];
  memset(stream_ptr, 0, sizeof(vcdio_stream));
  stream_ptr->name = strdup(name);
  stream_ptr->type = type;
  if (event_size == 0)
    event_size = VCDIO_DEFAULT_EVENT_COUNT;

  stream_ptr->events = malloc(event_size*sizeof(vcdio_event));
  if (stream_ptr->events == 0)
  {
    printf("ERROR, Unable to allocate memory. %s(%d)\b", __FILE__, __LINE__);
    exit(1);
  }

  stream_ptr->vcd_symbol = malloc(2);
  stream_ptr->vcd_symbol[0] = VCDIO_START_SYMBOL+vcdio_ptr->stream_cnt-1;
  stream_ptr->vcd_symbol[1] = '\0';
  stream_ptr->total_event_cnt = event_size;
  return(vcdio_ptr->stream_cnt);
}


/*
    Title: vcdio_start(vcdio *vcdio_ptr, char *name, int type, int event_size)
    Purpose: Starts the base for all the times in all the streams.
*/
int vcdio_start(vcdio *vcdio_ptr)
{
#ifdef Linux
  clock_gettime(0, &vcdio_ptr->os_start_time);
#else
# ifdef Darwin
  gettimeofday(&vcdio_ptr->os_start_time, 0);
# endif /* Darwin */
#endif /* Linux */

  return(0);
}

/*
    Title: vcdio_add(vcdio *vcdio_ptr, int id, unsigned int value)
    Purpose: This routine adds the specified value into the
             event buffer for the specified stream.
*/
int vcdio_add(vcdio *vcdio_ptr, int id, unsigned int value)
{
  vcdio_event *event_ptr;
  vcdio_stream *stream_ptr;

  if ((id > vcdio_ptr->stream_cnt)||(id == 0))
  {
    printf("WARNING, stream of id '%d' does not exist\n", id);
    return(1);
  }

  stream_ptr = &vcdio_ptr->streams[id-1];
  if (stream_ptr->event_cnt >= stream_ptr->total_event_cnt)
    return(1);

  event_ptr = &stream_ptr->events[stream_ptr->event_cnt++];
  event_ptr->value.uint_val = (unsigned int)value;
#ifdef Linux
  {
    struct timespec my_time;
    int secs_diff;
    long long nsec_diff;
    

    clock_gettime(0, &my_time);
    secs_diff = my_time.tv_sec - vcdio_ptr->os_start_time.tv_sec;
    event_ptr->timestamp = secs_diff;
    event_ptr->timestamp *= VCDIO_TIMESTAMP_UNITS_IN_A_SEC;

    nsec_diff = my_time.tv_nsec - vcdio_ptr->os_start_time.tv_nsec;
    if ((nsec_diff%10) >= 5)
    {
      nsec_diff /= 10;
      nsec_diff += 1;
    }
    else
      nsec_diff /= 10;

    event_ptr->timestamp += nsec_diff;
  }
#else
# ifdef Darwin
  {
    struct timeval my_time;
    int secs_diff;
    long long usec_diff;
    

    gettimeofday(&my_time, 0);
    secs_diff = my_time.tv_sec - vcdio_ptr->os_start_time.tv_sec;
    event_ptr->timestamp = secs_diff;
    event_ptr->timestamp *= VCDIO_TIMESTAMP_UNITS_IN_A_SEC;

    usec_diff = my_time.tv_usec - vcdio_ptr->os_start_time.tv_usec;
    usec_diff *= VCDIO_TIMESTAMP_UNITS_IN_A_USEC;
    event_ptr->timestamp += usec_diff;
  }
# endif /* DARWIN */
#endif /* LINUX */

  return(0);
}



/*
    Title: vcdio_close(vcdio *vcdio_ptr, char *fname)
    Purpose: create a vcdio stream. This will create a buffer of event_size
             events. A good number to start with would be in the range of a
             couple Million. (If an event is logged every 20 usecs, this
             would record data for 20 seconds if 1 million events were chosen).
             If a value of 0 is given, space for 100,000 events will be
             allocated.
*/
int vcdio_close(vcdio *vcdio_ptr, char *fname)
{
  FILE *fptr;
  int ii;
  time_t time_of_day;
  vcdio_stream *stream_ptr;
  int timestamp_flag;
  unsigned long long curr_timestamp;
  unsigned long long next_timestamp;
  char *daytime;
  char *ptr;


  /* okay, lets write out the vcd file */
  fptr = fopen(fname, "wb");
  if (fptr == 0)
  {
    printf("ERROR, Unable to open file '%s'\n", fname);
    fptr = fopen("pick_a_better_fname_loser.vcd", "wb");
    if (fptr)
      printf("       I have saved your data to 'pick_a_better_fname_loser.vcd' instead\n");
    else
    {
      printf("       Sorry, All of your data is lost\n");
      return(1);
    }
  }

  /* first lets write out the header */  
  time_of_day = time((time_t)0);
  daytime = ctime(&time_of_day);
  ptr = strchr(daytime, '\n');
  if (ptr)
    *ptr = '\0';
  fprintf(fptr, "$comment\n");
  fprintf(fptr, "/* Created on '%s' */\n", daytime);
  fprintf(fptr, "/*         by 'vcdio' */\n");
  fprintf(fptr, "end\n");
  fprintf(fptr, "$timescale 10ns $end\n");
  fprintf(fptr, "$scope module vcdio $end\n");
  for (ii = 0; ii < vcdio_ptr->stream_cnt; ++ii)
    fprintf(fptr, "$var wire 32 %s %s $end\n", vcdio_ptr->streams[ii].vcd_symbol, vcdio_ptr->streams[ii].name);

  fprintf(fptr, "$upscope $end\n");
  fprintf(fptr, "$enddefinitions $end\n");
    
  for (ii = 0; ii < vcdio_ptr->stream_cnt; ++ii)
    vcdio_ptr->streams[ii].playback_event = 0;

  do
  {
    next_timestamp = -1;
    for (ii = 0; ii < vcdio_ptr->stream_cnt; ++ii)
    {
      stream_ptr = &vcdio_ptr->streams[ii];
      if (stream_ptr->playback_event < stream_ptr->event_cnt)
      {
        curr_timestamp = stream_ptr->events[stream_ptr->playback_event].timestamp;
        if (curr_timestamp <= next_timestamp)
          next_timestamp = curr_timestamp;
      }
    }

    timestamp_flag = 1;
    for (ii = 0; ii < vcdio_ptr->stream_cnt; ++ii)
    {
      stream_ptr = &vcdio_ptr->streams[ii];
      if (stream_ptr->playback_event < stream_ptr->event_cnt)
      {
        curr_timestamp = stream_ptr->events[stream_ptr->playback_event].timestamp;
        if (curr_timestamp == next_timestamp)
	{
          if (timestamp_flag)
	  {
            timestamp_flag = 0;
	    fprintf(fptr, "#%llu\n", curr_timestamp);
	  }

          fprintf(fptr, "b%s %s\n", _int_to_bits(stream_ptr->events[stream_ptr->playback_event].value.uint_val), stream_ptr->vcd_symbol);
          stream_ptr->playback_event += 1;
        }
      }
    }
  } while(next_timestamp != -1);

  return(0);
}


static char *_int_to_bits(unsigned int val)
{
  int ii;
  static char buff[33];
  unsigned int mask;

  memset(buff, '0', sizeof(buff));
  mask = 1<<((8*sizeof(val)) - 1);
  for (ii = 0; ii < (8*sizeof(val)); ++ii)
  {
    if (val&(mask>>ii))
      buff[ii] = '1';
  }

  buff[8*sizeof(val)] = '\0';
  return(buff);
}
