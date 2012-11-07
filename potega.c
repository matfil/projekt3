/*
 * potega.c
 *
 *  Created on: 05-11-2012
 *      Author: matfil
 */

/* Mateusz Filipiuk projent nr 1
 * funkcja podnosząca liczbę do potęgi naturalnej */

double potega (double x, int n)
{
  int i;
  double out;

  out = 1;

  if (n == 0) /* w założeniach zadania jest podane, że cokolwiek
                 podniesione do potęgi 0 daje out (out = 1) */
  {
    return out;
  }

  for (i = 1;i < n+1; i = i+1)
  {
    out = out * x; /* wymnażam n razy przez x, out na początku było 1*/
  }

  return out;
}

