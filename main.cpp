#include <stdio.h>
#include "hijacklib.h"
extern "C" int printf(const char* fmt, ...);

__declspec(noinline)
int foo(int a)
{
	if (a > 5)
		return 5 * a + a*a + 3 * a*a*a - a*a*a*a*a;
	else
		return 3 * a + a*a + -1 * a*a*a + a*a*a*a*a;
}

int main(int argc, const char* argv[])
{
	dummyfn();
	printf("I'm still here\n");
	return foo(argc);
}