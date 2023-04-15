#include "primitives.h"


object_t* number_literals[5];
double number_literal_values[5] = { 4.0,5.0,1.0,19.0,2.0, };

int prepare(void)
{
	for (long i = 0; i < 5; i++)
	{
		number_literals[i] = number_api._create(number_literal_values + i);
	}

	return 0;
}

void clean_literals(void)
{
	for (long i = 0; i < 5; i++)
	{
		obj_free(number_literals[i]);
	}
}

int main(void)
{
	prepare();
	object_t* temp0 = number_api._ops.multiply(number_literals[0], number_literals[1]);

	object_t* x = temp0;
	object_t* temp1 = number_api._ops.subtract(x, number_literals[2]);

	object_t* y = temp1;
	bool_t temp2 = number_api._ops.cmp_eq(y, number_literals[3]);

	object_t* temp3 = number_api._ops.divide(x, number_literals[4]);

	object_t* z = temp3;
	
	if (temp2) {
		object_t* z = temp3;
	}

	obj_free(temp0);
	obj_free(temp1);
	obj_free(temp3);
	clean_literals();	

	return 0;
}

