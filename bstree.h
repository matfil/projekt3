/*
 * bstree.h
 *
 *  Created on: 05-11-2012
 *      Author: matfil
 */

#ifndef BSTREE_H_
#define BSTREE_H_

database* createrecord (int key);
node* createnode (struct database* dane);
void addnode (node* element, node* root);
node* treesearch (node* root, int index);
void printtree (node* root);


#endif /* BSTREE_H_ */
