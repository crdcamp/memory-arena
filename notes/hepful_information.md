# "Address Of" & Operator

The C "address of" operator `&` creates a pointer. In this example, the expression `&x` creates a pointer to the location holding the object indicated by variable `x`. You can also cast types using the `&` operator, as we do with the cast `(byte_pointer) &x` in the following code.

**The casts shown here do not change the actual pointer**, they simply direct the compiler to refer to the data being pointed to according to the new data type:

```c
#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
    int i;
    for (i = 0; i < len; i++)
    printf(" %.2x", start[i]);
    printf("\n");
}

void show_int(int x) {
    show_bytes((byte_pointer) &x, sizeof(int));
}

void show_float(float x) {
    show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void *x) {
    show_bytes((byte_pointer) &x, sizeof(void *));
}
```

For clarity in the arena code, you might also want to consider using `typedef unsigned char *byte_pointer` in your code as well.

# Generating an ASCII Table

You can display a table showing the ASCII character codes with:

```bash
man ascii
```
