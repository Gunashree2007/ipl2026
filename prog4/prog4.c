#include <stdio.h>

struct Bitfield {
    unsigned int firstbit  : 1; 
    unsigned int smallNum  : 3; 
    unsigned int mediumNum : 4; 
};

int main() {
    // 1. Declare and initialize the structure
    struct Bitfield a;
    
    // 2. Set the first bit as requested
    a.firstbit = 1;
    a.smallNum = 9;     // 5 is 101 in binary (fits in 3 bits)
    a.mediumNum = 10;   // 12 is 1100 in binary (fits in 4 bits)

    printf("--- Normal Assignment ---\n");
    printf("a.firstbit:  %u\n", a.firstbit);
    printf("a.smallNum:  %u\n", a.smallNum);
    printf("a.mediumNum: %u\n", a.mediumNum);

    // 3. Testing Overflow (What happens if we exceed the bit limit?)
    printf("\n--- Testing Overflow ---\n");
    // a.smallNum is 3 bits maximum, meaning its highest possible value is 7 (111).
    // Let's try to assign 8 (1000 in binary).
    a.smallNum = 8; 
    printf("Assigned 8 to a.smallNum (3 bits). Actual stored value: %u\n", a.smallNum);

    // 4. Memory Size Test
    printf("\n--- Memory Consumption ---\n");
    printf("Size of entire structure: %zu bytes\n", sizeof(a));

    return 0;
}
