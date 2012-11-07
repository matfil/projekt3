/*
 * structures.h
 *
 *  Created on: 05-11-2012
 *      Author: matfil
 */

#ifndef STRUCTURES_H
#define STRUCTURES_H 1
#include <stdlib.h>

typedef struct database
{
  int key;
  int index;
  char name[16];
  double matrix[10][10];
} database;

typedef struct bst_node
{
  struct database* record;
  struct bst_node* up;
  struct bst_node* left;
  struct bst_node* right;
} node;

typedef struct simple_list
{
  int index;
  struct simple_list* forward;
} list;

#endif
