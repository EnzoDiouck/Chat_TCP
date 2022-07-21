#include "printbase10.h"

char *std_print_base10(int num)
{
  char nbr[10] = "0123456789";
  char *str;
  char *ptr;
  int comp;
  int comp2;

  str = malloc(sizeof(char) * 20);
  if (str == NULL)
    return str;
  ptr = malloc(sizeof(char) * 20);
  if (ptr == NULL)
    return ptr;
  comp = 0;
  comp2 = 0;
  if (num < 0)
    {
      str[comp++] = '-';
      num *= -1;
    }
  while (num > 0)
    {
      str[comp] =  nbr[(num % 10)];
      num -= (num % 10);
      num /= 10;
      comp++;
    }
  str[comp] = '\0';
  comp = std_strlen(str);
  comp--;
  while (comp2 != (int)std_strlen(str))
    {
      if (str[comp2] == '-')
	{
	  ptr[comp2] = str[comp2];
	  comp2++;
	}
      ptr[comp2] = str[comp];
      comp2++;
      comp--;
    }
  ptr[comp2] = '\0';
  return ptr;
}
