#include "stdafx.h"
#include "hijacklib.h"

HIJACKLIB_API void dummyfn()
{
}

int myhookfoo(int a)
{
	return 5 * a;
}