#ifndef c_decimal_h
#define c_decimal_h


typedef struct {
    long _scalar: 55;
    long _exponent: 8; // from pow(scalar, -256) to pow(scalar, 255)
    long _isNegative: 1;
} decimal_t;


decimal_t decimal_from_int(int raw);
decimal_t decimal_from_uint(int raw);
decimal_t decimal_from_long(int raw);
decimal_t decimal_from_ulong(int raw);
decimal_t decimal_from_float(int raw);
decimal_t decimal_from_double(int raw);


#endif // c_decimal_h