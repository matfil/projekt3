#ifndef SAVE_H_
#define SAVE_H_

void basedump (FILE* file, node* root);
database* getrecord (FILE*);
int saverecord (FILE*,database*); 

#endif

