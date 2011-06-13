/*
    Title: factors.c
    Purpose: Find all factors of a given number.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "factors.h"

inline struct afactor_struct *new_afactor(unsigned long long factor);
static unsigned long long _my_sqrt(unsigned long long val);

struct afactor_struct *factors_find(unsigned long long the_num, int io_flag)
{
  unsigned long long ii;
  unsigned long long first_factor = 0;
  unsigned long long max_factor = 0;
  unsigned long long max_possible_factor = 0;
  struct afactor_struct *factor_chain;
  struct afactor_struct **fc_ptr;
  unsigned long long first_factor_limit;
  
  /* lets find the first factor of 'the_num' */
  /* 3000000000 is a good start to search for the first factor */
  /* but.... this is an ERROR for bigger numbers so.... */
  max_possible_factor = _my_sqrt(the_num);
  for (ii = 2; ii < max_possible_factor; ++ii)
  {
    if ((the_num%ii) == 0)
    {
      first_factor = ii;
      max_factor = the_num/ii;
      break;
    }
  }

  fc_ptr = &factor_chain;
  *fc_ptr = new_afactor(1);
  fc_ptr = &((*fc_ptr)->nxt);
  *fc_ptr = new_afactor(the_num);

  if (first_factor)
  {
    fc_ptr = &((*fc_ptr)->nxt);
    *fc_ptr = new_afactor(first_factor);
    fc_ptr = &((*fc_ptr)->nxt);
    *fc_ptr = new_afactor(max_factor);
    fc_ptr = &((*fc_ptr)->nxt);
    for (ii = first_factor+1; ii < max_possible_factor; ++ii)
    {
      unsigned long long val;

      val = the_num/ii;
      if (val*ii == the_num)
      {
        if (io_flag)
        {
          fprintf(stderr, ".");
          fflush(stderr);
        }

        *fc_ptr = new_afactor(ii);
        fc_ptr = &((*fc_ptr)->nxt);
        *fc_ptr = new_afactor(val);
        fc_ptr = &((*fc_ptr)->nxt);
      }
    }

    if (io_flag)
    {
      fprintf(stderr, ".\n");
      fflush(stderr);
    }
  }

  return(factor_chain);
}


void factors_free(struct afactor_struct *afptr)
{
  struct afactor_struct *nxt_afptr;

  while (afptr)
  {
    nxt_afptr = afptr->nxt;
    free(afptr);
    afptr = nxt_afptr;
  }
}

inline struct afactor_struct *new_afactor(unsigned long long factor)
{
  struct afactor_struct *ptr;

  ptr = malloc(sizeof(struct afactor_struct));
  if (ptr == 0)
  {
    fprintf(stderr, "ERROR, Unable to allocate memory. %s(%d)\n", __FILE__, __LINE__);
    return(0);
  }

  ptr->factor = factor;
  ptr->nxt = 0;
  return(ptr);
}



static unsigned long long _my_sqrt(unsigned long long val)
{
  long double tmp;

  tmp = val;
  tmp = sqrtl(tmp);
  return(ceill(tmp));  
}

