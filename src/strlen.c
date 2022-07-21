/*
** Enzo PFEIFFER diouck
** enzo.pfeiffer - <enzo.pfeiffer@ecole-89.com>
**
** strlen.c  - 2021
*/

#include "strlen.h"

size_t	std_strlen(const char *str)
{
  int	taille;

  taille = 0;
  while (str[taille] != '\0')
    taille++;
  return (taille);
}
