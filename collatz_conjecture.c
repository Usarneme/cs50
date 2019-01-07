#include <stdio.h>

int collatz(int n, int count);

int main(void) {
  printf("Hello World\n");

  for (int i=1; i<31; i++)
  {
    printf("%i steps %i\n", i, collatz(i, 0));
  }

  return 0;
}

int collatz(int n, int count)
{
  if (n == 1) 
  {
    return count;
  }
  if (n % 2 == 0)
  {
    n = n / 2;
    count++;
    count = collatz(n, count);
  }
  else
  {
    n = (3 * n) + 1;
    count++;
    count = collatz(n, count);
  }
  return count;
}

