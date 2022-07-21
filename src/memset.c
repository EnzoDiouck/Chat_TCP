#include "memset.h"

void *std_memset(void *s, int c, size_t n)
{
  int comp;
  char *str;

  comp = 0;
  str = s;
  while (comp < (int)n)
    {
      str[comp] = c;
      comp++;
    }
  s = str;
  return s;
}
