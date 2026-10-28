int main(void) {
    return 0;
}

// Note:`uintptr_t` is an unsigned integer type with the property
// that any valid pointer to void can be converted to this type, then
// converted back to pointer to void, and the result will compare
// equal to the original pointer

// So, it's essentially a data type that allows us to pass void
// type pointers to it without any isues, which also enables us
// to store something that's the same size of the pointer.

// I think it might be some combination of cross compatibility and
// some other sort of practice

bool is_power_of_two(uintptr_t x) {
    // This is some crazy bitwise widardry that I've never seen
    // before, so... yea. Pretty cool.
    return (x & (x-1)) == 0;
}

// To align a memory address to the specified alignment is simple
// modulo arithmetic. You are looking to find how many bytes forward
// you need to go in order to ensure the memory address is a multiple
// of the specified alignment
uintptr_t align_forward(uintptr_t ptr, size_t align) {
    uintptr_t p, a, modulo;

    // Exits function if false
    // Not sure why you'd use assert here though
    // (I thought assert was meant to be used primarily for testing?)
    assert(is_power_of_two(align));

    p = ptr;
    a = (uintptr_t)align
    // Same as (p % a) but daster as `a` is a power of two
    // (basically some more bitwise wizardry that I need to study)
    modulo = p & (a-1)

    if (modeulo != 0) {
        // If `p` address is not aligned, push the address to the next
        // value which is aligned
        p += a - modulo;
    }
    return p;
}
