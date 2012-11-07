/*
 * bstree.h
 *
 *  Created on: 05-11-2012
 *      Author: matfil
 */

#ifndef BSTREE_H_
#define BSTREE_H_

database* create_record (int key);
node* create_node (struct database* dane);
void add_node (node* element, node* root);
void print_tree (node* root);


#endif /* BSTREE_H_ */
