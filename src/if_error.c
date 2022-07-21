#include "if_error.h"

void if_error(char *str)
{
  perror(str);
  exit(89);
}

void text_exit(char *str)
{
  write(1, str, std_strlen(str));
  exit(89);
}
