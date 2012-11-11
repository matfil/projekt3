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
node* maxvalue (node* root);
node* minvalue (node* root);
node* bstpred (node* what);
node* bstsucc (node* what);
void dprint (node* root);
void uprint (node* root);
void transplant (node* u, node* v);
void nodedelete (node* target);
void printsingle (node* what);
#endif /* BSTREE_H_ */
