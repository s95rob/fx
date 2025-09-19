# fx

Header-only fixed-point arithmetic C implementation for embedded systems without a dedicated FPU. 

+ Use `#define FX_NO_INLINE` to remove function inline hints. 
+ Use `#define FX32_FRAC_BITS number_of_bits` to define the amount of bits used for the fractional part (default 8 bits).
+ Use `#define FX32_FAST` before including this header to avoid up-casting during multiplication/division operations to mitigate overflow. 