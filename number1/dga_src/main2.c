#include <stdio.h>
#include <stdlib.h>

static unsigned long long _fib(unsigned long long prev, unsigned long long accumulator, unsigned int num)
{
  if (num == 0)
    return(accumulator);
  else
    return(_fib(accumulator, accumulator+prev, num-1));
}

int main(int argc, char **argv)
{
  unsigned int num;
  unsigned long long ans;

  if (argc != 2)
  {
    printf("ERROR, \n");
    return(1);
  }

  num = atoi(argv[1]);
  ans = _fib((unsigned long long)0, (unsigned long long)1, num-1);

  printf("ans = %llu(0x%llx)\n", ans, ans);
}

