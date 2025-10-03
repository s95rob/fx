# fx

Header-only fixed-point arithmetic C implementation for embedded systems without a dedicated FPU. Leverages compiler constant folding to initialize fixed-point 
numbers *like* floating-point. Only requires `stdint.h`. 

### Features
+ 32-bit (**Q**23.**8**, adjustable) fixed-point creation and resolution
+ Common arithmetic functions
+ Ceil and floor functions 

### Example
```c
#include "fx.h"

fx32 f = fx32_make(1, 500);             // Create an approximation of 1.5f
f = fx32_mul(f, fx32_make(2, 0));       // Multiply it by 2.0f
int i = fx32_resolve(f)                 // Resolve `f` to 3
```

### Macros

Define these before including `fx.h` to adjust its behavior. 

| Macro | Usage | Example |
|---|---|---|
| `FX_NO_INLINE` | Remove compiler inline hints | `#define FX_NO_INLINE` |
| `FX_FAST` | Avoid mitigating overflow by up-casting during multiplication/division (saves processor cycles) | `#define FX_FAST` |
| `FX32_SHIFT_BITS` | Define the amount of bits used for `fx32` fractional part (default 8 bits) | `#define FX32_SHIFT_BITS 8` |
| `FX32_QUANTIZE_LIMIT` | Define the upper limit of `fx32` fractional part's quantized range (default 1000, avoid exceeding 2^16) | `#define FX32_QUANTIZE_LIMIT 1000` |