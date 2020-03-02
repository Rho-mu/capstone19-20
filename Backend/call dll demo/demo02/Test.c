#include <stdio.h>
     
__declspec(dllexport) int sum(int a, int b)
{
   return a + b;
}