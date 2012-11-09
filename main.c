/* Mateusz Filipiuk projekt nr 3 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h"
#include "bstree.h"
#include "command.h"
#include "invert.h"
#include "list.h"
#include "input.h"

int main ()

{

  int a, exit, i, j, index, key, st;
  st = 1;
  char znak;
  char inp[128];
  char name[16];
  double matrix[10][10];
  database* build;
  node* root;  
  list* indexlist; /* lista indexów */

  root = NULL;
  indexlist = NULL;

  root = createnode(createrecord(0));
  root->record->index=0;

  key = 1; /* inicjacja klucza */
  exit = 0;
  
  srand ( time(NULL) ); /* inicjacja generatora liczb losowych */

  while (exit != 1)
  {
    printf("Podaj komendę. \n");
    switch ( getcommand() )  /* pobranie komendy */
    {
    case 0: /* wyświetlanie HELP'a */
      printhelp();
    break;
    case 1: /* ERASE usuwanie macierzy */
    break;
    case 2: /* ADD dodawanie macierzy */
      fgets(inp,128,stdin);
      a = buildmatrix(inp, matrix);/*pobierz*/
      if (a <= 0) /*sprawdzenie poprawności*/
      {
        printf("Macierz niepoprawna. Spróbuj jeszcze raz.\n");
        break;
      }
      build = NULL;
      build = createrecord(key);
      key++;
      do
      { 
        index = rand() % 10000;
      }while(checkindex(indexlist, index));
      build->index = index;
      printf("Podaj nazwę dla tej macierzy. Do 16 znaków: ");
      /*flush(stdin);*/
      for(i=0;i<16;i++){name[i]=' ';}
      fgets(name,16,stdin);
      build->size = a;
      for(i=0;i<16;i++){build->name[i] = name[i];}
      for(i=0;i<10;i++){for(j=0;j<10;j++)
      {build->matrix[i][j]=matrix[i][j];}}/* Przepisanie macierzy. */
      addnode (createnode(build), root);
      addtolist(indexlist, createelement (index));
      if (st)
      {root=root->right; root->up=NULL; st=0;}
    break;
    case 3: /* PRINT'owanie całego drzewa */
      printf("Wylistować bazę sortując rosnąco czy malejąco?\n");
      printf("Zostanie wczytany 1 znak. Dozwolone odpowiednio: r m \n");
      scanf("%c",&znak);
      if (znak == 'm')
      { dprint (root); }
      else
      { uprint (root); }
    break;
    case 4: /* SHOW */
      if(scanf("%d",&i))
      {
          
      }
    break;
    case 5: /* EDIT */
    break;
    case 6: /* INVERT */
    break;
    case 7: /* EXIT wyjście z programu */
      exit = 1;
    break;
    default:
      printf("Nie podano zrozumiałej komendy. Spróbuj help.");
    break;
    } /* switch ( getcommand() ) */
  } /* while (exit != 1) */
  return 0; 
}
