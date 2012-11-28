/* Mateusz Filipiuk projekt nr 3 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include "structures.h"
#include "bstree.h"
#include "command.h"
#include "invert.h"
#include "list.h"
#include "input.h"
#include "reader.h"
#include "save.h"
#include "wyznacznik.h"


int main ()

{


  printf("Program obsługujący bazę danych macierzy odwracalnych. \nAutor: Mateusz Filipiuk\n");


  int a, a1, exit, i, j, k, index, key, s, st;
  st = 1;
  char znak;
  char inp[128]; 
  char b[40];
  char name[16];
  double matrix[10][10];
  database* build;
  node* hold;
  node* root;
  list* indexlist; /* lista indexów */

  FILE* file;
  FILE* dump;

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
    fgets(inp,128,stdin);
    switch ( getcommand(inp) )  /* pobranie komendy */
    {
    case 0: /* wyświetlanie HELP'a */
      printhelp();
    break;
    /* -------------------------------------------------------------------------------1 */
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
    /* -------------------------------------------------------------------------------2 */
    case 2: /* ADD dodawanie macierzy */
      fflush(stdin);
      printf("Format wejścia: [a b c;d e f;g h i]\n");
      clear(inp);
      fgets(inp,128,stdin);
      if (exitfound(inp))
      { return 0; }
      a = buildmatrix(inp, matrix);/*pobierz*/
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
    /* -------------------------------------------------------------------------------3 */
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
    /* -------------------------------------------------------------------------------4 */
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
    /* -------------------------------------------------------------------------------5 */
    case 5: /* EDIT */
      printf("Który wpis chcesz edytować?\n");
      fgets(inp,128,stdin);
      if (exitfound(inp)) /* wyjście ewakuacyjne */
      { return 0; }
      prepare(inp,128);
      a = atoi(inp);
      clear(inp);
      a1 = a;
      hold = treesearch (root,a); /* o czym my właściwie mówimy? */
      if (hold != NULL) /* czy mamy o czym rozmawiać? */
      {

        printsingle (hold); /* wiemy co to jest */

        printf ("Czy chcesz zmienić nazwę macierzy? (t/n) ");
        fgets (inp,128,stdin);
        if (exitfound(inp)) /* wyjście ewakuacyjne */
        { return 0; }
        znak = inp[0];
        clear(inp);
        if (znak == 't') /* jak tak to łatwo podmieniamy nazwę */
        {
          printf ("Podaj nową nazwę.\n");
          fgets(name,16,stdin);
          for(i=0;i<16;i++){hold->record->name[i] = name[i];}
          for(i=0;i<16;i++){name[i] = ' ';}
        } /* if (znak == 't') */
        printf ("Czy chcesz zmienić index macierzy? (t/n) "); /* zaczynają się schody */
        fgets (inp,128,stdin);
        if (exitfound(inp)) /* wyjście ewakuacyjne */
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
            for(i=0;i<16;i++){name[i] = ' ';} /* Czyszczenie name po każdym użyciu */
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
    /* -------------------------------------------------------------------------------6 */
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
      inverter(hold->record->matrix,matrix,hold->record->size);/* co, gdzie zapisać, jakiego rozmiaru to jest */
      printf("To jest macierz odwrotna\n");
      showarray(matrix,hold->record->size);
      }
    break;
    /* -------------------------------------------------------------------------------7 */
    case 7: /* EXIT wyjście z programu */
      exit = 1;
    break;
    /* -------------------------------------------------------------------------------8 */
    case 8: /* save */
      fflush(stdin);
      if (root->record->key == 0)
      {
        printf("Nie należy zapisywać pustej bazy\n");
        break;
      }
      for(i=0;i<16;i++)
      {name[i]=' ';}
      i=0;
      sscanf(inp,"%s %s",b,name); /* pobranie nazwy pliku */
      if (name[0] == 'd' && name[1] == 'u' && name[2] == 'm' && name[3] == 'p' && name[4] == '.' && name[5] == 't' && name[6] == 'x' && name[7] == 't' )
      {
        printf("Ta nazwa jest zabroniona\n");
        fgets(inp,16,stdin);/* usunięcie syfu po scanfie */
        break;
      }
      file = fopen(name, "a");
      basedump(file,root);
      fclose(file);
    break;
    /* -------------------------------------------------------------------------------9 */
    case 9: /* load */

      fflush(stdin);
      for(i=0;i<16;i++)
      {name[i]=' ';}
      i=0;
      sscanf(inp,"%s %s",b,name);/* pobranie nazwy pliku */
      if (name[0] == 'd' && name[1] == 'u' && name[2] == 'm' && name[3] == 'p' && name[4] == '.' && name[5] == 't' && name[6] == 'x' && name[7] == 't' )
      {
        printf("Ta nazwa jest zabroniona\n");
        break;
      }
      file = fopen(name, "a");
      fclose(file); /* tworzenie pliku jeśli go nie ma*/    
      file = fopen(name, "r");
      dump = fopen("dump.txt", "w");/* plik do składowania rekordów
                                       z powtarzającymi się indeksami */
      build = NULL;
      hold = NULL;
      st = root->record->key == 0? 1: 0; /* czy nie wczytujemy bazy 
                                            od nowa? */
      a = 0;/* przechowywanie informacji o powtarzających się
               indeksach */
      while(!(feof(file)))/* dopóki jest co czytać */
      {
         build = getrecord(file);/* pobierz rekord */
         if (build == NULL) /* sprawdź czy się udało */
         {break;}
         if (checkindex(indexlist,build->index))/* czy ten indeks
                                                   już wystąpił? */
          {
            a = 1; /* zapamiętajmy, że coś trafiło do dumpa */
            saverecord (dump, build); /* zapiszmy ten element do dumpa */
          }
         else
         {
           build->key = key; /* przydzielany jest nowy klucz */
           key++; /* inkrementacja */
           addnode (createnode(build), root); /* dodanie do drzewa */
           addtolist(indexlist, createelement(build->index)); /* listy */
           if (st) /* jak dodawany jako węzeł numer 1 to wyrzućmy 
                      strażnika z miejsca roota */
           {
              hold = root;
              root=root->right;
              root->up=NULL;
              st=0;
              free (hold);
           }
         }
      }
      fclose(dump);
      if (a == 1)/* jak coś jest w dumpie */
      {
          printf("Znaleziono wpisy o indexach istniejących w bazie.\nCzy dodać je do bazy z nowymi indexami? (t/n)");
          fgets(inp,128,stdin);
          if (inp[0]=='t')
          {
              dump = fopen("dump.txt","r");/* czytamy z dumpa */
              while(!(feof(dump)))
                {
                  build = getrecord(dump);
                  if (build == NULL)
                  {break;}
                  do
                  {
                    index = rand() % 10000; /* szukamy nowych indexów */
                  }while(checkindex(indexlist, index));
                  build->index = index;
                  build->key=key;/* nadajemy nowy klucz */
                  key++;
                  addnode (createnode(build), root);/* dodajemy do
                                                       drzewa */
                  addtolist(indexlist, createelement(build->index));
                }
          fclose(dump);
          }
      }
      fclose(file);
    break;
    /* -------------------------------------------------------------------------------10 */ 
    case 10: /* append */
      fflush(stdin);
      node* whatusave;
      for(i=0;i<16;i++)
      {name[i]=' ';}
      i=0;
      sscanf(inp,"%s %d %s",b,&i,name);
      whatusave = treesearch(root,i);
      if (whatusave != NULL)
      {      
        if (name[0] == 'd' && name[1] == 'u' && name[2] == 'm' && name[3] == 'p' && name[4] == '.' && name[5] == 't' && name[6] == 'x' && name[7] == 't' )
        {
           printf("Ta nazwa jest zabroniona\n");
           break;
        }
        file = fopen(name, "a");
        saverecord (file,whatusave->record);
        fclose(file);

      }

    break;
    /* -------------------------------------------------------------------------------11 */
    case 11: /* read */
      for(i=0;i<16;i++)
      {name[i]=' ';}
      i=0;
      sscanf(inp,"%s %s",b,name);
      file = fopen(name, "ab");
      fclose(file);
      file = fopen(name, "rb");
      node* whaturead;
      whaturead = malloc(sizeof(node));
      while(!(feof(file)))
      {
      whaturead->record = getrecord(file);
      if (whaturead->record == NULL)
      {break;}
      printsingle(whaturead);
      }
      free(whaturead);
    break;
   /* -------------------------------------------------------------------------------DEFAULT */
    default:
      printf("Nie podano zrozumiałej komendy. Spróbuj help.\n");
    break;
    } /* switch ( getcommand() ) */
  } /* while (exit != 1) */
  return 0;
}
