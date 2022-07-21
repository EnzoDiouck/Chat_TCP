#include "realloc.h"

void *std_realloc(void *ptr, size_t original_size, size_t new_size)
{
  void *new_ptr;
  
  if (new_size == 0)
    {
      free(ptr);
      return NULL;
    }
  else if (new_size <= original_size)
    return ptr;
  else if (ptr == NULL)
    return malloc(new_size);
  else
    {
      new_ptr = malloc(new_size);
      if (new_ptr != NULL)
	{
	  std_memcpy(new_ptr, ptr, original_size);
	  free(ptr);
	}
      return new_ptr;
    }
}
