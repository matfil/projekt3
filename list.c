/*
 * list.c
 *
 *  Created on: 05-11-2012
 *      Author: matfil
 */

#include <stdio.h>
#include "structures.h"

list* create_element (int a)
{
  list* newone; /* wskaźnik */
  newone = malloc (sizeof(list)); /* przydziel pamięć */
  newone->index = a; /* ustaw wartość */
  return newone; /* zwróć wskaźnik */
}

int check_index (list* first, int a) /* sprawdza czy w liście jest
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
      return check_index (first->forward, a);
    }
  }
  else
  {
    return 0; /* nie znalazłem indexu == a w liście */
  }
}

void add_to_list (list* first, list* what)
{
  if (first->forward == NULL)
  {
    first->forward = what;
  }
  else
  {
    add_to_list (first->forward, what);
  }
}

void remove_from_list(list* first, int index)
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
      remove_from_list(first->forward, index);
    }
  }
  else
  {
    printf("W liście nie ma index'u %d", index);
  }

}

