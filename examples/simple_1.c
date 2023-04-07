#include "object.h"
#include "primitives.h"

// run {

//    n1 = 400;
//    
//    return n1 / 3;

// }


void run()
{
    double val_1 = 400;
    double val_2 = 3;

    object_t* var_n1 = create_number(&val_1);
    object_t* literal_1 = create_number(&val_2);

    return number_api._ops.divide(var_n1, literal_1);
}