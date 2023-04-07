#ifndef lang_primitives_h
#define lang_primitives_h


#include "object.h"
#include "objmem.h"

#include "vector.h"

#include "lp_number.h"
#include "lp_list.h"
#include "lp_string.h"
#include "lp_bool.h"


void prepare_primitives() 
{
    // usertypes has add_attr, primitives use the tables
    lp_number_prepare();
    lp_list_prepare();

}

// end list

#endif // lang_primitives_h