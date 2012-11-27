#include <stdio.h>
#include "bstree.h"
#include "input.h"
#include "reader.h"
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

 database* getrecord (FILE* file)
  {
    char inp[128];
    char name[16];
    double matrix[10][10];
    int i, j;
    database* build;

    fgets(inp,128,file);
    if (feof(file))
    {
      return NULL;
    }    
    rewrite(inp, name);
    build = createrecord(atoi(name));/* przepisany klucz */
    rewrite(inp, name);
    build->index = atoi(name);/* przepisany index */
    for(i=0;i<16;i++)name[i]=' ';
    fgets(inp,128,file);sscanf(inp,"%s ",name);
    for(i=0;i<16;i++){build->name[i] = name[i];} /* name przepisane */
    fgets(inp,128,file);
    cutit(inp);
    i = buildmatrix (inp,matrix);
    build->size = i;
    for(i=0;i<10;i++)
    {
      for(j=0;j<10;j++)
      {
        build->matrix[i][j] = matrix[i][j];
      }
    }    
    fgets(inp,128,file);
    return build;
  }

int saverecord (FILE* file, database* record)
{

    int i, j;
    fprintf (file, "%d %d \n", record->key, record->index);
    fputs (record->name, file);
    fprintf (file, "[");
    for(i=0;i<record->size;i++)
    {
      for(j=0;j<record->size;j++)
      {
        fprintf(file,"%g ",record->matrix[i][j]);
      }
      if (i+1 < record->size)
        fprintf(file,";");
    }
    fprintf (file, "] \n");
    fprintf (file, "%d \n", record->size);
    return 0;
}
