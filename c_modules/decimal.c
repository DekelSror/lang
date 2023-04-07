#include "decimal.h"


decimal_t decimal_from_int(int raw) {
    decimal_t res = {
        ._scalar = (long)raw,
        ._exponent = 1,
        ._isNegative = raw <= 0
    };

    return res;
}



decimal_t decimal_from_uint(unsigned int raw)
{
    decimal_t res = {
        ._scalar = (long)raw,
        ._exponent = 1,
        ._isNegative = 0
    };

    return res;
}

decimal_t decimal_from_long(long raw)
{
    // 
}

decimal_t decimal_from_ulong(unsigned long raw);
decimal_t decimal_from_float(float raw);
decimal_t decimal_from_double(double raw);