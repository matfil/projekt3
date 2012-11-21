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

void basedump (FILE* file, node* root)
{
  if ( root != NULL )
  {
    int i, j; /* iterators */

    basedump (file, root->right);
    basedump (file, root->left);
    fprintf (file, "%d %d x\n", root->record->key, root->record->index);
    fputs (root->record->name, file);
    fprintf (file, "[");
    for(i=0;i<root->record->size;i++)
    {
      for(j=0;j<root->record->size;j++)
      {
        fprintf(file,"%.0f ",root->record->matrix[i][j]);
      }
      if (i+1 < root->record->size)
        fprintf(file,";");
    }
    fprintf (file, "%c] x\n",8);
    fprintf (file, "%d x\n", root->record->size);

  }
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
  if (root != NULL)
  {
  if (root->record->index == index || root == NULL)
  {
    return root;
  }
  if (index > root->record->index)
  {
    return treesearch (root->right, index);
  }
  if (index < root->record->index)
  {
    return treesearch (root->left, index);
  }
  } /* if (root != NULL) */
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

node* maxvalue (node* root)
{
  if (root->right != NULL)
  { return maxvalue (root->right); }
  else
  { return root; }
}

node* minvalue (node* root)
{
  if (root->left != NULL)
  { return minvalue (root->left); }
  else
  { return root; }
}

node* bstpred (node* what)
{
  node* pred;
  pred = what->up;
  if (what == NULL)
  { return NULL; }
  if (what->left != NULL)
  { return maxvalue(what->left); }
  while(pred != NULL && pred->left == what )
  {
    what = pred;
    pred = pred->up;
  }
  return pred;
}

node* bstsucc (node* what)
{
  node* succ;
  succ = what->up;
  if (what == NULL)
  { return NULL; }
  if (what->right != NULL)
  { return minvalue(what->right); }
  while(succ != NULL && succ->right == what)
  {
    what = succ;
    succ = succ->up;
  }
  return succ;
}

void printsingle (node* what)
{
  int i, j;
  if (what != NULL)
  {
    printf ("klucz: %d \n",what->record->key);
    printf ("index: %d \n",what->record->index);
    printf ("nazwa: ");
    for (i=0;i<16;i++)
    {
      printf ("%c",what->record->name[i]);
    }
    printf("\n");
    for (i=0;i<what->record->size;i++)
    {
      for (j=0;j<what->record->size;j++)
      {
        printf ("%f ",what->record->matrix[i][j]);
      }
      printf ("\n");
    }
    printf("\n");
  }
}

void dprint (node* root) /* nie nadaje się do printowania poddrzew 
                            zawsze wyprintuje całe, bo root 
                            będzie miał rodzica */
{
  node* sth;
  sth = maxvalue (root);
  while ( sth != NULL )
  {
    printsingle (sth);
    sth = bstpred (sth);
  }
}

void uprint (node* root)
{
  node* sth;
  sth = minvalue (root);
  while ( sth != NULL )
  {
    printsingle (sth);
    sth = bstsucc (sth);
  }
}

void transplant (node* u, node* v)
{
  if (u->up == NULL)
  {
    u = v;
    if (v != NULL)
    {
      v->up = NULL;
    }
  }
  else
  {
    if (u == u->up->left)
    {
      u->up->left = v;
    }
    else
    {
      u->up->right = v;
    }
  }
  if (v != NULL)
  {
    v->up = u->up;
  }
}

void nodedelete (node* target)
{
  if (target != NULL)
  {
  node* y;
  if (target->left == NULL)
  {
    transplant(target,target->right);
  }
  else
  {
    if (target->right == NULL)
    {
      transplant(target,target->left);
    }
    else
    {
      y = minvalue(target->right);
      if (y->up != target)
      {
        transplant(y,y->right);
        y->right = target->right;
        y->right->up = y;
      }
      transplant(target,y);
      y->left = target->left;
      y->left->up = y;
    }
  }
  
  free(target);
  }
}


