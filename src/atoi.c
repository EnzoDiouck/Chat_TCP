/*
** Enzo PFEIFFER diouck
** enzo.pfeiffer - <enzo.pfeiffer@ecole-89.com>
**
** atoi.c - 2021
*/

#include "atoi.h"

int	std_atoi(const char *str)
{
  int resultat;
  int comp;
  int neg;
  int started;

  comp = 0;
  resultat = 0;
  neg = 1;
  started = 0;
  while (str[comp] == '-' || (str[comp] != '\0' && str[comp] >= 48 && str[comp] <= 57))
    {
      if (str[comp] == '-')
	{
	  if (started != 0)
	    return(resultat/10*neg);
	  neg = -1;
	  comp++;
	}
      else
	{
	  resultat = resultat + str[comp] - 48;
	  resultat = resultat * 10;
	  comp++;
	}
      started++;
    }
  resultat = resultat / 10;
  resultat *= neg;
  return (resultat);
}
