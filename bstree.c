/*
 * bstree.c
 *
 *  Created on: 05-11-2012
 *      Author: matfil
 */

#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

database* createrecord (int key)
{
  int i, j;
  database* newone;
  newone = malloc (sizeof(database));
  newone->key = key;
  newone->index = 0;

  for(i = 0;i < 16;i++)/* zerowanie tablicy name[16] */
  {
    newone->name[i] = ' ';
  }/* for(i = 0;i < 16;i++) */

  for(i = 0;i < 10;i++)/* zerowanie tablicy matrix[10][10] */
  {
    for(j = 0;j < 10;j++)
    {
      newone->matrix[i][j] = 0;
    }
  }/* for(i = 0;i < 10;i++) */

  return newone;
}

node* createnode (struct database* dane)
{
  node* newone;
  newone = malloc (sizeof(node));
  newone -> record = dane; /*  */
  newone -> up = NULL;
  newone -> left = NULL;
  newone -> right = NULL;
  return newone;
}

void addnode (node* element, node* root)
{ 
  if (element->record->index < root->record->index && root->left == NULL)
  {
    root->left = element; /* mniejszy i wolny lewy syn => element
                             staje się lewym synem */
    element->up = root;
  }
  else
  {
    if (element->record->index < root->record->index && root->left != NULL)
    {
      addnode (element, root->left); /* mniejszy i zajęte miejsce
                                         lewego syna => zejdź niżej */
    }
    else
    {  /* wiadomo że index elementu jest większy */
      if (root->right == NULL)
      {
        root->right = element; /* wolny prawy syn => element staje
                                  się prawym synem */
        element->up = root;
      }
      else
      {
        addnode (element,root->right); /* w przeciwnym przypadku idziemy
                                           głębiej w prawo */
      }
    }
  }
  
}

node* treesearch (node* root, int index)
{
  if (root->record->index == index || root == NULL)
  {
    return root;
  }
  if (index > root->record->index)
  {
    treesearch (root->right, index);
  }
  if (index < root->record->index)
  {
    treesearch (root->left, index);
  }
  return NULL;
}

void printtree (node* root)
{
  int i, j;
  if (root != NULL)
  {
    printf ("klucz: %d \n",root->record->key);
    printf ("index: %d \n",root->record->index);
    printf ("nazwa: ");
    for (i=0;i<16;i++)
    {
      printf ("%c",root->record->name[i]);
    }
    printf("\n");
    for (i=0;i<root->record->size;i++)
    {
      for (j=0;j<root->record->size;j++)
      {
        printf ("%f ",root->record->matrix[i][j]);
      }
      printf ("\n");
    }
    printf("\n");
    printtree (root->left);
    printtree (root->right);
  }
}
