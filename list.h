#ifndef _LIST_H_
#define _LIST_H_

list* createelement (int a);
void showlist (list* first);
int checkindex (list* first, int a);
void removefromlist(list* first, int index);
void addtolist (list* first, list* what);

#endif /* _LIST_H_ */
