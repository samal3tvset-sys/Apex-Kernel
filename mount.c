#include <stdint.h>

#define MAX_MOUNTS 32

typedef struct {
    uint32_t device_id;
    uint32_t type;
    uint32_t flags;
    void* data;
} mount_entry_t;

static mount_entry_t mount_table[MAX_MOUNTS];

static uint32_t mount_count = 0;

int mount_init() {
    for (uint32_t i = 0; i < MAX_MOUNTS; i++) {
        mount_table[i].device_id = 0;
        mount_table[i].type = 0;
        mount_table[i].flags = 0;
        mount_table[i].data = 0;
    }
    mount_count = 0;
    return 0;
}

int mount_device(uint32_t device_id, uint32_t type, uint32_t flags, void* data) {
    if (mount_count >= MAX_MOUNTS) {
        return -1;
    }

    mount_table[mount_count].device_id = device_id;
    mount_table[mount_count].type = type;
    mount_table[mount_count].flags = flags;
    mount_table[mount_count].data = data;

    mount_count++;
    return 0;
}

int unmount_device(uint32_t device_id) {
    for (uint32_t i = 0; i < mount_count; i++) {
        if (mount_table[i].device_id == device_id) {
            for (uint32_t j = i; j + 1 < mount_count; j++) {
                mount_table[j] = mount_table[j + 1];
            }
            mount_count--;
            return 0;
        }
    }
    return -1;
}