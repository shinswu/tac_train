/*
    Title: main.c
    Purpose: Find all factors of a given number.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "factors.h"

static char *_parse_args(int arg_cnt, char **arg_list, char *string, int arg_var);

int main(int argc, char **argv)
{
  unsigned long long the_num;
  struct afactor_struct **fc_ptr;
  struct afactor_struct *factor_chain;

  if ((argc != 2)||(_parse_args(argc, argv, "-h", 0)))
  {
    printf("Usage: %s <number>\n", argv[0]);
    printf("Find the largest prime factor of the specified number.\n");
    return(0);
  }

  the_num = strtoull(_parse_args(argc, argv, 0, 0), 0, 10);

  factor_chain = factors_find(the_num, 1);
  fc_ptr = &factor_chain;
  while (fc_ptr)
  {
    fprintf(stderr, "%llu\n", (*fc_ptr)->factor);
    if ((*fc_ptr)->nxt)
      fc_ptr = &((*fc_ptr)->nxt);
    else
      break;
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


