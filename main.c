/* Mateusz Filipiuk projekt nr 3 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h"

int main ()

{

  int a, exit, index, key;
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
    switch ( get_command() )  /* pobranie komendy */
    {
    case 0: /* wyświetlanie HELP'a */
      print_help();
    break;
    case 1: /* usuwanie macierzy */
    break;
    case 2: /* dodawanie macierzy */
      fgets(inp,128,stdio);
      a = buildmatrix(inp, matrix);/*pobierz*/
      if (a <= 0) /*sprawdzenie poprawności*/
      {
        printf("Macierz niepoprawna. Spróbuj jeszcze raz.");
        break;
      }
      build = NULL;
      build = create_record(key);
      key++;
      do
      { 
        index = rand() % 10000;
      }while(check_index(first, index));
      build->index = index;
      printf("Podaj nazwę dla tej macierzy. Do 16 znaków.");
      fgets(name,16,stdio);
      build->name = name;
      add_node (create_node(build), root);
    break;
    case 3: /**/
    break;
    case 4; /**/
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
    } /* switch ( get_command() ) */
  } /* while (exit != 1) */
  return 0; 
}
