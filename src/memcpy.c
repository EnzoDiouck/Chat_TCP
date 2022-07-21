#include "memcpy.h"

void *std_memcpy(void *dest,
		 const void *src,
		 size_t n)
{
  char *temp_src;
  char *temp_dest;
  int comp;

  temp_dest = (char*)dest;
  temp_src = (char*)src;
  comp = 0;
  while (n > 0)
    {
      temp_dest[comp] = temp_src[comp];
      comp++;
      n--;
    }
  return dest;
}
