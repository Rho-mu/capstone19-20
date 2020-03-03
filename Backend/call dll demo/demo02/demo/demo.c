#include <stdio.h>
#include <string.h>

__declspec(dllexport) char* Hello(char* input)
{
	static char str1[16];
	static char str2[16];
	strcpy(str1, "Hello ");
	strcpy(str2, input);
	strcat(str1, str2);
	return ("%s", str1);
}

__declspec(dllexport) int sum(int a, int b)
{
	return (a + b);
}