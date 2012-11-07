/*
 * invert.c
 *
 *  Created on: 05-11-2012
 *      Author: matfil
 */

#include <stdio.h>
#include "potega.h"
#include "wyznacznik.h"

void removex (double inp[10][10], double minor[10][10], int a, int b)
{
  int i1, i2, i3, i4;

  for(i1 = 0;i1 < 10;i1++) /* przepisanie macierzi inp */
  {
    for(i2 = 0;i2 < 10;i2++)
    {
      minor[i1][i2] = inp[i1][i2];
    }
  }

  for(i3 = a;i3<10;i3++)
  {
    for(i4 = 0;i4 < 10;i4++)
    {
      minor[i3][i4] = minor[i3+1][i4];
    }
  }

  for(i4 = b;i4 < 10;i4++)
  {
    for(i3 = 0;i3 < 10;i3++)
    {
      minor[i3][i4] = minor[i3][i4+1];
    }
  }
}

void transponuj (double inp[10][10], double out[10][10])
{
  int i1, i2;
  for(i1 = 0;i1 < 10;i1++) /* kolumna i1 staje się wierszem i2 */
  {
    for(i2 = 0;i2 < 10;i2++)
    {
      out[i1][i2] = inp[i2][i1];
    }
  }
}

int inverter (double inp[10][10], double out[10][10], int n )
{
  int i1, i2;
  double detinp,  minor[10][10]; /* tu będzie składowany minor */

  detinp = det(inp, n);

  if (detinp == 0)
  {
    return 0; /* macierz jest nieodwracalna */
  }

  for (i1 = 0;i1<10;i1++)
  {
    for (i2 = 0;i2<10;i2++)
    {
      removex(inp,minor,i1,i2);/*tworzenie minorów*/
      out[i1][i2]=potega(-1,i1+i2)*det(minor,n-1);/*obliczanie dopełnienia*/
    }
  }

  printf("To jest macierz dopełnień algebraicznych wprowadzonej macierzy.\n");
  showarray(out,n);

  transponuj(out,minor);

  for(i1 = 0;i1<10;i1++)
  {
    for(i2 = 0;i2<10;i2++)
    {
      out[i1][i2] = (1/detinp)*minor[i1][i2];/*obliczanie właściwej macierzy*/
    }
  }
  return 0;
}

