/*
* list.c
*
* Created on: 05-11-2012
* Author: matfil
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


void showlist (list* first)
{
  list* hold;
  hold = first;
  while(hold != NULL)
  {
    printf(" %d ",hold->index);
    hold = hold->forward;
  }
  printf("\n");
}

int checkindex (list* first, int a) /* sprawdza czy w liście jest
                                       element z indexem a*/
{
  list* hold;
  hold = first;
  while (hold != NULL)
  {
    if (hold->index == a)
      return 1;
    else
      hold = hold->forward;/* sprawdźmy następny element listy */
  }
  return 0;
}
               

void addtolist (list* first, list* what)
{
  if (first != NULL)
  {

  list* hold;
  hold = first;
  while(hold->forward != NULL)
  {
    hold = hold->forward;
  }
  hold->forward = what;
  }/* if (first != NULL) */
  else
  {
    first = what;
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
