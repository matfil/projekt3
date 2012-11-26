#include <stdio.h>
#include "input.h"
#include "structures.h"

void basedump (FILE* file, node* root)
{
  if ( root != NULL )
  {
    int i, j; /* iterators */

    basedump (file, root->right);
    basedump (file, root->left);
    fprintf (file, "%d %d \n", root->record->key, root->record->index);
    fputs (root->record->name, file);
    fprintf (file, "[");
    for(i=0;i<root->record->size;i++)
    {
      for(j=0;j<root->record->size;j++)
      {
        fprintf(file,"%g ",root->record->matrix[i][j]);
      }
      if (i+1 < root->record->size)
        fprintf(file,";");
    }
    fprintf (file, "] \n");
    fprintf (file, "%d \n", root->record->size);

  }
}

int getrecord (FILE* file, database* build)
  {
    char inp[128];
    char name[16];
    int i;
    fgets(inp,128,file);
    for(i=0;i<128;i++){printf("%c",inp[i]);}printf("\n");
    rewrite(inp, name);
    printf("%d\n",atoi(name));
    rewrite(inp, name);
    printf("%d\n",atoi(name));
    for(i=0;i<128;i++){printf("%c",inp[i]);}printf("\n");
    fgets(name,128,file);
    for(i=0;i<16;i++){printf("%c",name[i]);}printf("\n");
    fgets(inp,128,file);
    for(i=0;i<128;i++){printf("%c",inp[i]);}printf("\n");
    fgets(inp,128,file);
    for(i=0;i<128;i++){printf("%c",inp[i]);}printf("\n");
  }
