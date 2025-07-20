#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

int main() {
    int a = 12984;
    int b = 23423;

    // Machine code (x86_64): return a + b
    // mov eax, a        (b8 <a 4 bytes>)
    // add eax, b        (05 <b 4 bytes>)
    // ret               (c3)
    unsigned char code[] = {
        0xb8, 0x00, 0x00, 0x00, 0x00, // mov eax, a
        0x05, 0x00, 0x00, 0x00, 0x00, // add eax, b
        0xc3                          // ret
    };

    // Fill in a and b into the machine code
    memcpy(&code[1], &a, 4);
    memcpy(&code[6], &b, 4);

    // Allocate executable memory
    void *mem = mmap(NULL, sizeof(code),
                     PROT_READ | PROT_WRITE | PROT_EXEC,
                     MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

    if (mem == MAP_FAILED) {
        perror("mmap failed");
        return 1;
    }

    // Copy machine code into the memory
    memcpy(mem, code, sizeof(code));

    // Cast memory to function pointer and call it
    int (*calc)() = mem;
    int result = calc();

    printf("Result from memory calculator: %d + %d = %d\n", a, b, result);

    munmap(mem, sizeof(code));
    return 0;
}
