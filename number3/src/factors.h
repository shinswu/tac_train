/*
    Title: factors.h
    Purpose: Include file for finding factors of a 64bit number.
*/

struct afactor_struct;
struct afactor_struct
{
  unsigned long long factor;
  struct afactor_struct *nxt;
};

struct afactor_struct *factors_find(unsigned long long the_num, int io_flag);
void factors_free(struct afactor_struct *afptr);
