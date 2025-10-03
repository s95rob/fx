#include "fx.h"

#include <stdio.h>

#define FX_TEST(case_name, expression) \
    if (!(expression)) { \
        printf("[TEST] %s: FAIL\n", case_name); \
        return -1; \
    } \
    else \
        printf("[TEST] %s: OK\n", case_name);

#define FX32_TEST_APPROX(fx, min, max) \
    (min <= fx32_to_float(fx) && fx32_to_float(fx) <= max)


int main(int argc, char** argv) {
    printf("-- FX TESTS --\n\n");

    printf("FX32 TESTS (8-bit fractional part)\n");

    fx32 fx = fx32_make(1, 250),     // ~1.25
         fx1 = fx32_make(0, 750);   // ~0.75

    FX_TEST("fx32 to integer resolution",
        fx32_resolve(fx) == 1);

    FX_TEST("fx32 to float approx.",
        fx32_to_float(fx32_make(0, 999)) >= 0.99f &&
        fx32_to_float(fx32_make(0, 999)) <= 1.0f);

    FX_TEST("float to fx32",
        fx32_from_float(5.0f) == fx32_make(5, 0));

    FX_TEST("fx32 addition approx.",
        FX32_TEST_APPROX(fx32_add(fx, fx1), 1.99f, 2.00f));

    FX_TEST("fx32 subtraction approx.",
        FX32_TEST_APPROX(fx32_sub(fx, fx1), 0.490f, 0.5f));

    FX_TEST("fx32 multiplication approx.",
        FX32_TEST_APPROX(fx32_mul(fx, fx1), 1.24f * 0.74f, 1.25f * 0.75f));

    fx = fx32_make(5, 0);   // 5.0
    fx1 = fx32_make(2, 0);  // 2.0
    FX_TEST("fx32 division",
        fx32_to_float(fx32_div(fx, fx1)) == (5.0f / 2.0f));

    fx = fx32_make(1, 500); // ~1.5
    FX_TEST("fx32 floor",
        fx32_resolve(fx32_floor(fx)) == 1);

    FX_TEST("fx32 ceil",
        fx32_resolve(fx32_ceil(fx)) == 2);

    return 0;
}