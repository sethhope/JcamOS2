#ifndef _OPENMATH_
#define _OPENMATH_
#include <math.h>

typedef struct
{
	float SIN[91];
} TABLES;

TABLES *genTables(TABLES *tab);
float getSin(unsigned int val, TABLES *tab);
float getCos(unsigned int val, TABLES *tab);
#endif
