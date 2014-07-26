#include "OpenMath.h"


TABLES *genTables(TABLES *tab)
{
	TABLES *t = malloc(sizeof(*t));
	for(int i = 0; i < 91; i++)
	{	
		t->SIN[i] = sin(i);
	}
	tab = t;
	free(t);
	return tab;
}
float getSin(unsigned int val, TABLES *tab)
{
	if(val <= 90)
	{
		return tab->SIN[val];
	}else if(val > 90 && val <= 180)
	{
		return tab->SIN[90-(val-90)];
	}else if(val > 180 && val <= 270)
	{
		return -tab->SIN[val-180];
	}else if(val > 270)
	{
		return -tab->SIN[90-(val-270)];
	}
	return sin(val);
}

float getCos(unsigned int val, TABLES *tab)
{
	if(val < 270)
	{
		return getSin(val+90, tab);
	}else
	{
		return getSin(val-270, tab);
	}
	return cos(val);
}
