#include <stdint.h>

#define SANDBOX_MEM_SIZE 4096

static uint8_t sandbox_mem[SANDBOX_MEM_SIZE];

static uint32_t sandbox_ptr = 0;

void sandbox_reset() {
    sandbox_ptr = 0;
    for (uint32_t i = 0; i < SANDBOX_MEM_SIZE; i++) {
        sandbox_mem[i] = 0;
    }
}

void* sandbox_alloc(uint32_t size) {
    if (sandbox_ptr + size > SANDBOX_MEM_SIZE) {
        return (void*)0;
    }

    void* addr = &sandbox_mem[sandbox_ptr];
    sandbox_ptr += size;
    return addr;
}

uint8_t sandbox_read(uint32_t offset) {
    if (offset >= SANDBOX_MEM_SIZE) {
        return 0;
    }
    return sandbox_mem[offset];
}

void sandbox_write(uint32_t offset, uint8_t value) {
    if (offset >= SANDBOX_MEM_SIZE) {
        return;
    }
    sandbox_mem[offset] = value;
}