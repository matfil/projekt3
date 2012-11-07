/* Mateusz Filipiuk projekt nr 3 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h"
#include "bstree.h"
#include "command.h"
#include "invert.h"
#include "list.h"

int main ()

{

  int a, exit, i, index, key;
  char inp[128];
  char name[16];
  double matrix[10][10];
  database* build;
  node* root;  
  list* indexlist; /* lista indexów */

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
    case 1: /* usuwanie macierzy */
    break;
    case 2: /* dodawanie macierzy */
      fgets(inp,128,stdin);
      a = buildmatrix(inp, matrix);/*pobierz*/
      if (a <= 0) /*sprawdzenie poprawności*/
      {
        printf("Macierz niepoprawna. Spróbuj jeszcze raz.");
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
      printf("Podaj nazwę dla tej macierzy. Do 16 znaków.");
      fgets(name,16,stdin);
      for(i=0;i<16;i++){build->name[i] = name[i];}
      addnode (createnode(build), root);
    break;
    case 3: /**/
    break;
    case 4: /**/
    break;
    case 5: /**/
    break;
    case 6: /**/
    break;
    case 7: /**/
      exit = 1;
    break;
    default:
      printf("Nie podano zrozumiałej komendy. Spróbuj help.");
    break;
    } /* switch ( getcommand() ) */
  } /* while (exit != 1) */
  return 0; 
}
