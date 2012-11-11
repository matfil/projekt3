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

int main ()

{

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
      fgets(inp,128,stdin);
      prepare(inp,128);
      a = atoi(inp);
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
    break;
    case 3: /* PRINT'owanie całego drzewa */
      printf("Wylistować bazę sortując rosnąco czy malejąco?\n");
      printf("Zostanie wczytany 1 znak. Dozwolone odpowiednio: r m \n");
      fgets(inp,128,stdin);
      znak = inp[0];
      if (exitfound(inp))
      { return 0; }
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
      printf("Który wpis chcesz edytować?\n");
      fgets(inp,128,stdin);
      prepare(inp,128);
      a = atoi(inp);
      a1 = a;
      hold = treesearch (root,a);
      if (hold != NULL)
      {

        printsingle (hold);

        printf ("Czy chcesz zmienić nazwę macierzy? (t/n) ");
        fgets (inp,128,stdin);
        znak = inp[0];
        if (znak == 't')
        {
          printf ("Podaj nową nazwę.\n");
          fgets(name,16,stdin);
          for(i=0;i<16;i++){hold->record->name[i] = name[i];}
        } /* if (znak == 't') */
        printf ("Czy chcesz zmienić index macierzy? (t/n) ");
        fgets (inp,128,stdin);
        znak = inp[0];
        if (znak == 't')
        {
          removefromlist(indexlist, a);/* usuń zmieniany index z listy */
          do
          {
            printf ("Podaj nowy index. ");
            fgets(inp,128,stdin);
            prepare(inp,128);
            a = atoi(inp);/* zapytaj o nowy */
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
