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

void printable (char inp[16])
{
  int i;
  for(i=0;i<16;i++)
  {
    if (inp[i]<32 || inp[i]>126)
    {
      inp[i] = ' ';
    }
  }
}

void clear (char inp[128])
{
  int i;
  for (i = 0; i < 128; i++)
  {
    inp[i] = ' ';
  }
}

void cutit (char inp[128])
{
  int i;
  int b;
  b = 0;
  for(i=0;i<128;i++)
  {
    if(b==0 && inp[i]!=']')
    {continue;}
    if(b==0 && inp[i]==']')
    {b=1; continue;}
    inp[i]=' ';
  }
}
