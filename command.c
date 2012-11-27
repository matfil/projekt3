/*
 * command.c
 *
 *  Obsługa komend wydawanych programowi przez użyszkodnika.
 *
 *  Created on: 05-11-2012
 *      Author: Mateusz Filipiuk
 */

#include <stdio.h>
int getcommand ()
{
	char inp[128];
	int i;

	fgets(inp,128,stdin);

	for (i = 0;i < 124;i++)
	{
		if (inp[i] == 'h' && inp[i+1] == 'e' && inp[i+2] == 'l' && inp[i+3] == 'p')
		{
			return 0;
		}
		if (inp[i] == 'e' && inp[i+1] == 'r' && inp[i+2] == 'a' && inp[i+3] == 's' && inp[i+4] == 'e')
		{
			return 1;
		}
		if (inp[i] == 'a' && inp[i+1] == 'd' && inp[i+2] == 'd')
		{
			return 2;
		}
		if (inp[i] == 'p' && inp[i+1] == 'r' && inp[i+2] == 'i' && inp[i+3] == 'n' && inp[i+4] == 't')
		{
			return 3;
		}
		if (inp[i] == 's' && inp[i+1] == 'h' && inp[i+2] == 'o' && inp[i+3] == 'w')
		{
			return 4;
		}
		if (inp[i] == 'e' && inp[i+1] == 'd' && inp[i+2] == 'i' && inp[i+3] == 't')
		{
			return 5;
		}
		if (inp[i] == 'i' && inp[i+1] == 'n' && inp[i+2] == 'v' && inp[i+3] == 'e' && inp[i+4] == 'r' && inp[i+5] == 't')
		{
			return 6;
		}
		if (inp[i] == 'e' && inp[i+1] == 'x' && inp[i+2] == 'i' && inp[i+3] == 't')
		{
			return 7;
		}
    if (inp[i] == 's' && inp[i+1] == 'a' && inp[i+2] == 'v' && inp[i+3] == 'e')
    {
      return 8;
    }
    if (inp[i] == 'l' && inp[i+1] == 'o' && inp[i+2] == 'a' && inp[i+3] == 'd')
    {
      return 9;
    }
    if (inp[i] == 'a' && inp[i+1] == 'p' && inp[i+2] == 'p' && inp[i+3] == 'e' && inp[i+4] == 'n' && inp[i+5] == 'd')
    {
      return 10;
    }
	    if (inp[i] == 'r' && inp[i+1] == 'e' && inp[i+2] == 'a' && inp[i+3] == 'd')
    {
      return 11;
    }
 }
	return -1;
}

void printhelp()
{
	printf("Lista możliwych poleceń: \n help \n add \n erase \n show \n print \n edit \n invert \n exit\n save\n load\n append\n read\n");
}



