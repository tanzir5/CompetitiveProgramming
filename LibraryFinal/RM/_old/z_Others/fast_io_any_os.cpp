//FAST IO
//Remember to fix data type
//Doesn't work for negative numbers

int readint()
{
   int cc = getc(stdin);
   for (;cc < '0' || cc > '9';)  cc = getc(stdin);
   int ret = 0;
   for (;cc >= '0' && cc <= '9';)
   {
      ret = ret * 10 + cc - '0';
      cc = getc(stdin);
   }
  return ret;
}
