#include "stdio.h"
#include "structures.h"

void basedump (FILE* file, node* root)
{
  if ( root != NULL )
  {
    int i, j; /* iterators */

    basedump (file, root->right);
    basedump (file, root->left);
    fprintf (file, "%d %d\n", root->record->key, root->record->index);
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

