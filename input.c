/*
 * input.c
 *
 *  Created on: 05-11-2012
 *      Author: matfil
 */

/* Mateusz Filipiuk projekt nr 2
 * plik zawierający funkcje konieczne do zapisania macierzy
 * w postaci czytelnej dla komputera*/

#include <stdio.h>
#include <stdlib.h> /* tu jest zawarta funkcja atof() zamieniająca tablice znaków na double */


int exitfound (char inp[128])
{
  int i;
  for (i = 0;i < 125;i++)
  {
    if (inp[i]=='e'&&inp[i+1]=='x'&&inp[i+2]=='i'&&inp[i+3]=='t')/*szukam exit'u*/
    {
      return 1;
    }
  }
  return 0;
}


void smacznego (char inp[128])
{
  int i;
  for (i = 0;i < 128;i++)
  {
    if (inp[i]==';')/* zjadam ; */
    {
      inp[i] = ' ';
      break;
    }
  }
}


void printinput (char inp[128])
{
  int i;
  for (i = 0;i < 128;i++)
  {
    printf ("%c", inp[i] );/* wypisuję input */
  }

  printf ("\n");

}

int lettercheck (char inp[128])
{
  int i;

  for (i = 0; i < 128; i++) /* sprawdzam poprawność ciągu znaków */
  {
    if ((inp[i] == ' '|| inp[i] == '-' || inp[i] == '.' || inp[i] == ';') || (inp[i] >= 48 && inp[i] < 58) )
    {} /* znaki dozwolone */
    else
    {

      return 0; /* zostaje zwrócony FAŁSZ! znaleziono coś różniącego się od ' ' '.' '-' ';' lub cyfry */
    }
  }
  return 1; /* wszystko jest ok */
}

int rewrite (char inp[128], char out[16])
{
  int i, o, dotcount;

  for (i = 0;i<16;i++)
  {
    out[i]=' ';/*czyszczenie tablicy out*/
  }

  o = 0; /* ilość przepisanych znaków */
  dotcount = 0; /* tyle znalazłem kropek przed rozpoczęciem szukania */

  for (i = 0; i < 128; i++)
  {
    if (inp[i] == ' ') /* czy to spacja? */
    {
      continue; /* jak tak to dalej */
    }
    else
    {
      if (o > 15) /* czy liczba nie jest za długa? */
      {
        printf ("liczba o za długiej ilości znaków!!!\n");
        return 0;
      }/* if (o > 15) */
      out[o] = inp[i];
      o++;
      if (inp[i] == '.') /* czy znalazłem kropkę? */
      {
        dotcount++;
      } /* if (inp[i] == '.') */
      inp[i] = ' ';
      if (inp[i+1] == ' ' || inp[i+1] == ';' )
      {
        break;
      } /* if (inp[i+1] == ' ' || inp[i+1] == ';' ) */
    }/* else */
  } /* for (i = 0; i < 128; i++) */
  if (dotcount > 1) /* czy w liczbie była więcej niż jedna kropka? */
  {
    return 0; /* jeśli tak to ŹLE */
  }
  return 1; /* wszystko się udało! */
} /* int rewrite (char inp[128], char out[16]) */

void cutbraces (char inp[128]) /* ta funkcja obcina wszystkie znaki aż do [ ]. Nawiasy też są zamieniane na ' '  */
{
  int i;

  for (i = 0;i < 128;i++) /* czyszczenie początku ciągu */
  {
    if (inp[i] != '[')
    {
      inp[i] = ' ';
    }
    else
    {
      inp[i] = ' ';
      break; /* zakończ działanie pętli gdy [ został znaleziony */
    }
  }

  for (i = 127;i > 0;i--)/* czyszczenie końca ciągu */
  {
    if (inp[i] != ']')
    {
      inp[i] = ' ';
    }
    else
    {
      inp[i] = ' ';
      break; /* zakończ działanie pętli gdy ] został znaleziony */
    }
  }
}

int jesttamkto (char inp[128])
{
  int i;

  for (i = 0; i < 128; i++)
  {
    if (inp[i] >= 48 && inp[i] <= 58) /* jest liczba */
    {
      return 1;
    }
    if (inp[i] == ';' ) /* jest średnik */
    {
      return 2; /* mówimy że był średnik zwracając kod 2 */
    }
  }
  return 0;
}

int buildmatrix (char inp[128], double matrix[10][10])
{
  int a, b, amax, bmax, i;
  char out[16];

  amax = bmax = 0;

  cutbraces(inp); /*obcięcie ciągu do interesującego nas fragmentu */

  if (jesttamkto(inp) == 0)
  {
    printf ("Ciąg nie zawiera liczb zapisanych w odpowiednim formacie\n");
    return 0; /* tego ciągu nie lubimy */
  }

  if (lettercheck(inp) == 0)
  {
    printf ("Ciąg zawiera znaki, które mogą nie zostać obsłużone\n");
    return -2; /* tego ciągu nie lubimy */
  }

  b = 0; /* wiersz 0 */
  a = 0; /* kolumna też 0 */

  for (i = 0; i< 81; i++)
  {


    /* printinput(inp); debug */

    if (rewrite(inp,out) == 0) /* weź jedną liczbę */
    {
      printf("zły format liczby\n");
      return 0;
    }

    matrix[b][a] = atof(out); /* zamiana ciągu znaków na liczbę double */

    /* printinput(inp);
    printf("%f %d %d \n",matrix[b][a], a,b); */

    if (jesttamkto(inp) == 1) /* jest kolejna liczba w tym wierszu */
    {
      a++;
     if (a > amax)
     {amax = a;}
    }
    if (jesttamkto(inp) == 2) /* w dół do następnego wiersza*/
    {
      b++;
      a = 0;
      if (b > bmax)
      {bmax = b;}
      smacznego(inp);
    }
    if (jesttamkto(inp) == 0) /*puk puk... Kto tam? Pusto!*/
    {
      break;
    }
  }

  if (amax == bmax)
  {
    return amax+1; /* macierz jest kwadratowa */
  }
  else
  {
    return -1; /* macierz nie jest kwadratowa */
  }
}

