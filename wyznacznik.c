/*
 * wyznacznik.c
 *
 *  Created on: 05-11-2012
 *      Author: matfil
 */

/* Mateusz Filipiuk projekt nr 2
 * Funkcja det obliczająca wartość wyznacznika macierzy kwadratowej
 * korzystając z rozwinięcia Laplace'a*/

#include "potega.h"
#include <stdio.h>

void showarray(double tab[10][10],int n)
{
  int i, j;
  for(i = 0; i < n; i++)
  {
    for(j = 0; j < n; j++)
    {
      printf("%f ",tab[i][j]);
    }
    printf("\n");
  }
}


double det (double matrix[10][10],int n)
{

  int i, j, k;
  double out, sub;
  double passed[10][10]; /*tablica przekazywana do następnego wywołania
                         rekurencyjnego funkcji*/

  out = 0;

  /*showarray(matrix, n+1); stary debug*/

   if (n == 1) /*jeżeli macierz jest 1x1 to zwróć wartość z pozycji 0,0*/
  {
    return matrix[0][0];
  }

  if (n == 2) /*jeżeli macierz jest 2x2 to oblicz wartość korzystając
                ze znanego wzoru.*/
  {
    out = matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];
    return out;
  }

  if (n >= 3) /*obliczanie wyznacznika z rozwinięcia Laplace'a*/
  {


    for (i = 0;i < n;i++) /*rozwinięcie względem wiersza 0*/
    {
      for (j = 1;j<n;j++)
      {
        for (k = 0; k<n;k++)
        {
          passed[j-1][k]=matrix[j][k];
        }
      }
      for (j = i;j<n;j++)
      {
        for (k = 0;k<n-1;k++)
        {
          passed[k][j]=passed[k][j+1];
        }
      }
    /*
    printf("%d\n",n);
    showarray(passed, n);
    stary debug
    */
      sub = det(passed,n-1);

      out = out + matrix[0][i] * potega(-1,0+i) * sub;
    }
  }
  return out;
}

