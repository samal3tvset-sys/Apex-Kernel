#include <stdint.h>

#define MAX_MODULES 64

typedef struct {
    uint32_t id;
    uint32_t status;
    void (*entry)(void);
} module_t;

static module_t modules[MAX_MODULES];

static uint32_t module_count = 0;

int register_module(uint32_t id, void (*entry)(void)) {
    if (module_count >= MAX_MODULES) {
        return -1;
    }

    for (uint32_t i = 0; i < module_count; i++) {
        if (modules[i].id == id) {
            return -2;
        }
    }

    modules[module_count].id = id;
    modules[module_count].status = 0;
    modules[module_count].entry = entry;

    module_count++;

    return 0;
}

int init_module(uint32_t id) {
    for (uint32_t i = 0; i < module_count; i++) {
        if (modules[i].id == id) {
            if (modules[i].entry == 0) {
                return -1;
            }

            modules[i].entry();
            modules[i].status = 1;

            return 0;
        }
    }

    return -2;
}

int check_module(uint32_t id) {
    for (uint32_t i = 0; i < module_count; i++) {
        if (modules[i].id == id) {
            return modules[i].status;
        }
    }

    return -1;
}

int protect_init_system() {
    for (uint32_t i = 0; i < module_count; i++) {
        modules[i].status = 0;
    }

    return 0;
}