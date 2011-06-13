/*
  Title: vcdio.h
  Purpose: Include file for vcdio functionality
*/

#define VCDIO_DEFAULT_EVENT_COUNT          100000
#define VCDIO_START_SYMBOL                 33
#define VCDIO_END_SYMBOL                   126
#define VCDIO_TIMESTAMP_UNITS_IN_A_SEC     100000000  /* 10nsec resolution */
#define VCDIO_TIMESTAMP_UNITS_IN_A_USEC    100        /* 10nsec resolution */

typedef enum
{
  vcdio_uint_type=1,
  vcdio_int_type=2,
  vcdio_float_type=3
} vcdio_type;


typedef union
{
  unsigned int uint_val;
  int int_val;
  float float_val;
}  vcdio_val;

typedef struct
{
  unsigned long long timestamp;      /* Timestamp is kept in units of 10 ns */
  vcdio_val value;
} vcdio_event;

typedef struct
{
  char *name;
  vcdio_type type;
  char *vcd_symbol;    /* characters that range from ascii 33 - 126 */
  unsigned int event_cnt;
  unsigned int total_event_cnt;
  unsigned int playback_event;
  vcdio_event *events;
} vcdio_stream;

typedef struct
{
  int stream_cnt;
  vcdio_stream *streams;
#ifdef Linux
  struct timespec os_start_time;
#else
# ifdef Darwin
  struct timeval os_start_time;
# else
  AN_OS_OTHER_THEN_LINUX_OR_MAC_IS_NOT_SUPPORTED
# endif /* Darwin */
#endif /* Linux */
} vcdio;


#ifdef TO_SPEEDUP_VCD_GENERATION
typedef struct
{
  vcdio_stream *stream_ptr;
  vcdio_event *event_ptr;
  playback_event *nxt;
  playback_event *prv;
} playback_event;
#endif /* TO_SPEEDUP_VCD_GENERATION */

/* Public Functions */
vcdio *vcdio_create();
int vcdio_create_stream(vcdio *vcdio_ptr, char *name, vcdio_type type, int event_size);
int vcdio_start(vcdio *vcdio_ptr);
int vcdio_add(vcdio *vcdio_ptr, int id, unsigned int value);
int vcdio_close(vcdio *vcdio_ptr, char *fname);
