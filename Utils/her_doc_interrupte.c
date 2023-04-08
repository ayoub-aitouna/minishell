#include"./utils.h"

int interrupted(int value)
{
	static int interrupted;

	if(value != -1)
		interrupted = value;
	return (interrupted);
}

void set_interrupted(int value)
{
	interrupted(value);
}

int is_interrupted(void)
{
	return interrupted(-1);
}
