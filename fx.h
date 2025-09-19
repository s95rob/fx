/*  Fixed-point arithmetic implementation.

    Use `#define FX_NO_INLINE` to remove function inline hints. 

    Use `#define FX32_FRAC_BITS number_of_bits` to define the amount of bits used
    for the fractional part (default 8 bits).

    Use `#define FX32_FAST` before including this header to avoid
    up-casting during multiplication/division operations to
    mitigate overflow. 
*/

#ifndef FX_H
#define FX_H

#include <stdint.h>

#ifndef FX_NO_INLINE
    #define FX_INLINE static inline
#else
    #define FX_INLINE
#endif

#ifndef FX32_FRAC_BITS
    #define FX32_FRAC_BITS 8
#endif

#define FX32_ONE (1 << FX32_FRAC_BITS)
#define FX32_MASK (FX32_ONE - 1)

typedef int32_t fx32;


// Return a fixed-point number from whole part `i` and fractional part `f`
FX_INLINE fx32 fx32_make(int32_t i, uint16_t f) {
    return (fx32)((i << FX32_FRAC_BITS) | f);
}

// Return a fixed-point number from float `f` 
// (slow - uses software implementation for non-FPU systems)
FX_INLINE fx32 fx32_from_float(float f) {
    return (fx32)(f * FX32_ONE);
}

// Return a float from fixed-point number `f`
// (slow - uses software implementation for non-FPU systems)
FX_INLINE float fx32_to_float(fx32 f) {
    return (float)f / FX32_ONE;
}

// Return a standard 32-bit (signed) integer from fixed-point number `f`
FX_INLINE int32_t fx32_resolve(fx32 f) {
    return (f >> FX32_FRAC_BITS);
}

// Add fixed-point number `b` to `a`
FX_INLINE fx32 fx32_add(fx32 a, fx32 b) {
    return (a + b);
}

// Subtract fixed-point number `b` from `a`
FX_INLINE fx32 fx32_sub(fx32 a, fx32 b) {
    return (a - b);
}

// Multiply fixed-point number `a` by `b`
FX_INLINE fx32 fx32_mul(fx32 a, fx32 b) {
    #ifdef FX32_FAST
        return ((a * b) >> FX32_FRAC_BITS);
    #else
        return (fx32)(((uint64_t)a * b) >> FX32_FRAC_BITS);
    #endif
}

// Divide fixed-point number `a` by `b`
FX_INLINE fx32 fx32_div(fx32 a, fx32 b) {
    #ifdef FX32_FAST
        return ((a << FX32_FRAC_BITS) / b);
    #else
        return (fx32)(((uint64_t)a << FX32_FRAC_BITS) / b);
    #endif
}

// Round fixed-point number `f` up
FX_INLINE fx32 fx32_ceil(fx32 f) {
    return ((f + FX32_MASK) & ~FX32_MASK);
}

// Round fixed-point number `f` down
FX_INLINE fx32 fx32_floor(fx32 f) {
    return (f & ~FX32_MASK);
}


#endif // FX_H