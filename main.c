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
#include "reader.h" 
#include "wyznacznik.h"

int main ()

{
  printf("Program obsługujący bazę danych macierzy odwracalnych. \nAutor: Mateusz Filipiuk\n");
  int a, a1, exit, i, j, k, index, key, s, st;
  st = 1;
  char znak;
  char inp[128];
  char name[16];
  double matrix[10][10];
  database* build;
  node* hold;  
  node* root;
  list* indexlist; /* lista indexów */

  root = NULL;
  indexlist = NULL;

  root = createnode(createrecord(0));
  root->record->index=0;
  
  indexlist = createelement(0);

  key = 1; /* inicjacja klucza */
  exit = 0;
  
  srand ( time(NULL) ); /* inicjacja generatora liczb losowych */

  while (exit != 1)
  {
    fflush(stdin);
    printf("Podaj komendę. \n");
    switch ( getcommand() )  /* pobranie komendy */
    {
    case 0: /* wyświetlanie HELP'a */
      printhelp();
    break;
    case 1: /* ERASE usuwanie macierzy */
      fflush(stdin);
      fgets(inp,128,stdin);
      if (exitfound(inp))
      { return 0; }
      prepare(inp,128);
      a = atoi(inp);
      clear(inp);
      nodedelete(treesearch(root,a));
      removefromlist(indexlist,a);
      printf("usunięto wpis o indeksie: %d \n", a);
      if (root == NULL)
      {
        root = createnode(createrecord(0));
        root->record->index=0;
        st = 1;
      }
    break;
    case 2: /* ADD dodawanie macierzy */
      fflush(stdin);
      printf("Format wejścia: [a b c;d e f;g h i]\n");
      clear(inp);
      fgets(inp,128,stdin);
      printf("here");
      if (exitfound(inp))
      { return 0; }
      printf("here");
      a = buildmatrix(inp, matrix);/*pobierz*/
      printf("here");
      clear(inp);
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
        printf("%d %d",index,checkindex(indexlist,index));
      }while(checkindex(indexlist, index));
      build->index = index;
      printf("Podaj nazwę dla tej macierzy. Do 16 znaków: ");
      for(i=0;i<16;i++){name[i]=' ';}
      fgets(name,16,stdin);
      build->size = a;
      for(i=0;i<16;i++){build->name[i] = name[i];}
      for(i=0;i<10;i++){for(j=0;j<10;j++)
      {build->matrix[i][j]=matrix[i][j];}}/* Przepisanie macierzy. */
      addnode (createnode(build), root);
      addtolist(indexlist, createelement (index));
      if (st)/*bo dodawanie do drzewa działa dobrze 
               z conajmniej 1 elementem*/
      { 
        hold = root;
        root=root->right; 
        root->up=NULL; 
        st=0;
        free (hold);
      }
      printf("wpisowi nadano klucz %d i index %d.\n", key-1, index); 
    break;
    case 3: /* PRINT'owanie całego drzewa */
      printf("Wylistować bazę sortując rosnąco czy malejąco?\n");
      printf("Zostanie wczytany 1 znak. Dozwolone odpowiednio: r m \n");
      fgets(inp,128,stdin);
      znak = inp[0];
      if (exitfound(inp))
      { return 0; }
      clear(inp);
      if (znak == 'm')
      { dprint (root); }
      else
      { 
        if (znak != 'r')
        {
          printf("\"nie wiem\" znaczy wylistować rosnąco\n");
        }
        uprint (root); 
      }
    break;
    case 4: /* SHOW */
      printf("Podaj indeks macierzy, którą chcesz wyświetlić. ");
      fgets(inp,128,stdin);
      if (exitfound(inp))
      { return 0; }
      prepare(inp,128);
      a = atoi(inp);
      clear(inp);
      printsingle(treesearch(root,a));
      break;
    case 5: /* EDIT */
      printf("Który wpis chcesz edytować?\n");
      fgets(inp,128,stdin);
      if (exitfound(inp))
      { return 0; }
      prepare(inp,128);
      a = atoi(inp);
      clear(inp);
      a1 = a;
      hold = treesearch (root,a);
      if (hold != NULL)
      {

        printsingle (hold);

        printf ("Czy chcesz zmienić nazwę macierzy? (t/n) ");
        fgets (inp,128,stdin);
        if (exitfound(inp))
        { return 0; }
        znak = inp[0];
        clear(inp);
        if (znak == 't')
        {
          printf ("Podaj nową nazwę.\n");
          fgets(name,16,stdin);
          for(i=0;i<16;i++){hold->record->name[i] = name[i];}
        } /* if (znak == 't') */
        printf ("Czy chcesz zmienić index macierzy? (t/n) ");
        fgets (inp,128,stdin);
        if (exitfound(inp))
        { return 0; }
        znak = inp[0];
        clear(inp);
        if (znak == 't')
        {
          removefromlist(indexlist, a);/* usuń zmieniany index z listy */
          do
          {
            fflush(stdin);
            printf ("Podaj nowy index. ");
            fgets(inp,128,stdin);
            if (exitfound(inp))
            { return 0; }
            prepare(inp,128);
            a = atoi(inp);/* zapytaj o nowy */
            clear(inp);
            i = checkindex (indexlist,a);
          }while (checkindex(indexlist, a));/* sprawdź czy już jest */
          addtolist(indexlist, createelement(a)); /* dodaj do listy */
          if (a != hold->record->index)
          {
            k = hold->record->key;
            s = hold->record->size;
            for(i=0;i<16;i++){name[i] = hold->record->name[i];}
            for(i=0;i<10;i++){for(j=0;j<10;j++)
            {matrix[i][j]=hold->record->matrix[i][j];}}/* Przepisanie macierzy. */
            nodedelete(treesearch (root, a1));/* niszczę stary który mógłby 
                                    psuć strukturę drzewa */
            if (root == NULL)
            {
              root = createnode(createrecord(0));
              root->record->index=0;
              st=1;
            }
            build = createrecord(k);/* klucz */
            build->index = a; /* index */
            build->size = s; /* size */
            for(i=0;i<16;i++){build->name[i] = name[i];} /* name */
	          for(i=0;i<10;i++){for(j=0;j<10;j++)
            {build->matrix[i][j]=matrix[i][j];}}/* Przepisanie macierzy. */
            addnode(createnode(build),root);
            if(st)
            {
              hold = root; 
              root=root->right;
              root->up = NULL; 
              st=0; 
              free(hold);
            }
          }
          /* ELSE nic nie rób */
        }/* if (znak == 't') */
      }/* if (hold != NULL) */
      else
      { printf("Nie ma takiego numeru. \n"); }
    break;
    case 6: /* INVERT */
      fflush(stdin);
      printf("Podaj indeks macierzy do odwrócenia ");
      fgets(inp,128,stdin);
      if (exitfound(inp))
      { return 0; }
      prepare(inp,128);
      a = atoi(inp);/* parsowanie */
      clear(inp);
      hold = treesearch(root,a);
      if (hold != NULL)
      {
      inverter(hold->record->matrix,matrix,hold->record->size);
      printf("To jest macierz odwrotna\n");
      showarray(matrix,hold->record->size);
      }
    break;
    case 7: /* EXIT wyjście z programu */
      exit = 1;
    break;
    default:
      printf("Nie podano zrozumiałej komendy. Spróbuj help.\n");
    break;
    } /* switch ( getcommand() ) */
  } /* while (exit != 1) */
  return 0; 
}
