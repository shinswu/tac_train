#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  unsigned int num;
  unsigned long long ans;
  unsigned long long prev;
  unsigned int ii;

  if (argc != 2)
  {
    printf("ERROR, \n");
    return(1);
  }

  num = atoi(argv[1]);
  prev = 0;
  ans = 1;
  for (ii = 2; ii <= num; ++ii)
  {
    unsigned long long prev_ans;

    prev_ans = ans;
    ans += prev;
    prev = prev_ans;
  }

  printf("ans = %llu(0x%llx)\n", ans, ans);
}
