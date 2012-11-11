/*
 * list.c
 *
 *  Created on: 05-11-2012
 *      Author: matfil
 */

#include <stdio.h>
#include "structures.h"

list* createelement (int a)
{
  list* newone; /* wskaźnik */
  newone = malloc (sizeof(list)); /* przydziel pamięć */
  newone->index = a; /* ustaw wartość */
  newone->forward = NULL; /* następnego nie ma (jeszcze) */
  return newone; /* zwróć wskaźnik */
}

int checkindex (list* first, int a) /* sprawdza czy w liście jest
                                       element z indexem a*/
{
  if (first != NULL)
  {
    if (first->index == a)
    {
      return 1; /* znalazłem index == a */
    }
    else
    {
      return checkindex (first->forward, a);
    }
  }
  else
  {
    return 0; /* nie znalazłem indexu == a w liście */
  }
}

void addtolist (list* first, list* what)
{
  if (first == NULL)
  {
    first = what;
  }
  else
  {
  if (first->forward == NULL)
  {
    first->forward = what;
  }
  else
  {
    addtolist (first->forward, what);
  }
  }
}

void removefromlist(list* first, int index)
{
  list* a;
  a = NULL;

  if (first != NULL)
  {
    if (first->index == index)
    {
      a = first->forward;
       free(first);
      first = a;
    }
    else
    {
      removefromlist(first->forward, index);
    }
  }
  else
  {
   
  }

}

