#ifndef lang_primitives_bool_h
#define lang_primitives_bool_h

#include "object.h"

extern object_api_t bool_api;
extern const object_t* lang_true;
extern const object_t* lang_false;

bool_t is_true(const object_t* obj);
int lp_bool_prepare(void);

#endif // lang_primitives_bool_h