void prepare (char inp[],int n)
{
  int d, i;
  for(i = 0; i < n; i++)
  {
    if ( (inp[i]>47 && inp[i]<58) || inp[i]==45 )
    {
      d = 1;
    }
    else
    {
      inp[i] = ' ';
    }
    if (d && (inp[i]<48 || inp[i]>57))
    {
      break;
    }
  }
  for( ; i<n ; i++)
  {
    inp[i] = ' ';
  }
}
/*teraz atoi() z stdlib.h*/

void clear (char inp[128])
{
  int i;
  for (i = 0; i < 128; i++)
  {
    inp[i] = ' ';
  }
}
