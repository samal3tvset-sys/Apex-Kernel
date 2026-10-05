#include <stdint.h>

#define FS_MAX_FILES 128
#define FS_NAME_LEN 32
#define FS_BLOCK_SIZE 512

typedef struct {
    char name[FS_NAME_LEN];
    uint32_t size;
    uint32_t start_block;
    uint32_t used;
} fs_file_t;

static fs_file_t fs_table[FS_MAX_FILES];

static uint8_t fs_storage[FS_MAX_FILES * FS_BLOCK_SIZE];

static uint32_t fs_file_count = 0;

int fs_init() {
    for (uint32_t i = 0; i < FS_MAX_FILES; i++) {
        fs_table[i].name[0] = 0;
        fs_table[i].size = 0;
        fs_table[i].start_block = 0;
        fs_table[i].used = 0;
    }

    fs_file_count = 0;

    for (uint32_t i = 0; i < sizeof(fs_storage); i++) {
        fs_storage[i] = 0;
    }

    return 0;
}

int fs_create(const char *name, uint32_t size) {
    if (fs_file_count >= FS_MAX_FILES) {
        return -1;
    }

    fs_file_t *f = &fs_table[fs_file_count];

    uint32_t start = fs_file_count * FS_BLOCK_SIZE;

    for (int i = 0; i < FS_NAME_LEN - 1 && name[i]; i++) {
        f->name[i] = name[i];
    }

    f->size = size;
    f->start_block = start;
    f->used = 1;

    fs_file_count++;

    return 0;
}

void* fs_read(const char *name) {
    for (uint32_t i = 0; i < fs_file_count; i++) {
        if (fs_table[i].used) {
            int match = 1;

            for (int j = 0; j < FS_NAME_LEN; j++) {
                if (fs_table[i].name[j] != name[j]) {
                    match = 0;
                    break;
                }
                if (name[j] == 0) break;
            }

            if (match) {
                return &fs_storage[fs_table[i].start_block];
            }
        }
    }

    return 0;
}

int fs_write(const char *name, const void *data, uint32_t size) {
    for (uint32_t i = 0; i < fs_file_count; i++) {
        if (fs_table[i].used) {
            int match = 1;

            for (int j = 0; j < FS_NAME_LEN; j++) {
                if (fs_table[i].name[j] != name[j]) {
                    match = 0;
                    break;
                }
                if (name[j] == 0) break;
            }

            if (match) {
                uint8_t *dst = &fs_storage[fs_table[i].start_block];

                for (uint32_t k = 0; k < size; k++) {
                    dst[k] = ((uint8_t*)data)[k];
                }

                fs_table[i].size = size;
                return 0;
            }
        }
    }

    return -1;
}