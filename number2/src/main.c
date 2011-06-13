/*
    Title: test_me.c
    Purpose: Find all factors of a given number.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "divide_me.h"

static char *_parse_args(int arg_cnt, char **arg_list, char *string, int arg_var);

int main(int argc, char **argv)
{
  unsigned long long answer;
  unsigned long long the_answer;
  unsigned long long the_divisor;
  unsigned long long the_num;

  if ((argc != 4)||(_parse_args(argc, argv, "-h", 0)))
  {
    printf("Usage: %s <number> <divisor> <answer>\n", argv[0]);
    printf("Test out our advanced division library.\n");
    return(0);
  }

  the_num = (unsigned long long)strtoul(_parse_args(argc, argv, 0, 2), 0, 10);
  the_divisor = (unsigned long long)strtoul(_parse_args(argc, argv, 0, 1), 0, 10);
  the_answer = (unsigned long long)strtoul(_parse_args(argc, argv, 0, 0), 0, 10);

  answer = divide_me(the_num, the_divisor);
  if (answer != the_answer)
  {
    fprintf(stderr, "ERROR, Division test failed expected %llu\n", the_answer);
    fprintf(stderr, "       got %llu\n", answer);
    return(1);
  }

  return(0);
}

static char *_parse_args(int arg_cnt, char **arg_list, char *string, int arg_var)
{
  int ii;
  int length;
  static char tmp_str[256];

#ifdef DEBUG
  printf("DEBUG: _parse_args();\n");
#endif
  /* lets look for the specified string */
  if (string)
  {
    length = strlen(string);
    for (ii = 0; ii < arg_cnt; ++ii)
    {
      if (strncmp(arg_list[ii], string, length) == 0)
      {
        if (string[length - 1] == '=')
        {
          strcpy(tmp_str, &arg_list[ii][length]);
          return(tmp_str);
        }
        else
        {
          if (arg_list[ii][length] == '\0')
          {
            strcpy(tmp_str, string);
            return(tmp_str);
          }
        }
      }
    }
    return(0);                     /* error, we must match the whole string */
  }
  else
  {
    if (arg_var > (arg_cnt - 1))
      return(0);
    else
      strcpy(tmp_str, &arg_list[arg_cnt - 1 - arg_var][0]);
  }

  return(tmp_str);
}


