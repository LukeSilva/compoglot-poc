#include <stdio.h>
#include <limits.h>
void warn(const char * message, const char * fallback){
  printf("Warning:\n");
  printf("%s\n%s\n",message,fallback);
}

#define PO10_LIMIT (INT_MAX/10)

int nDigits(int i)
{
  int n,po10;

  if (i < 0) i = -i;
  n=1;
  po10=10;
  while(i>=po10)
  {
    n++;
    if (po10 > PO10_LIMIT) break;
    po10*=10;
  }
  return n;
}
