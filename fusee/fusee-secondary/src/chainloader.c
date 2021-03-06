#include "chainloader.h"

int g_chainloader_argc = 0;
char g_chainloader_arg_data[CHAINLOADER_ARG_DATA_MAX_SIZE] = {0};
chainloader_entry_t g_chainloader_entries[CHAINLOADER_MAX_ENTRIES] = {0}; /* keep them sorted */
size_t g_chainloader_num_entries = 0;
uintptr_t g_chainloader_entrypoint = 0;

#pragma GCC optimize (3)

static void *xmemmove(void *dst, const void *src, size_t len)
{
    const uint8_t *src8 = (const uint8_t *)src;
    uint8_t *dst8 = (uint8_t *)dst;

    if (dst8 < src8) {
        for (size_t i = 0; i < len; i++) {
            dst8[i] = src8[i];
        }
    } else if (dst8 > src8) {
        for (size_t i = len; len > 0; len--)
            dst8[i - 1] = src8[i - 1];
    }

    return dst;
}

void relocate_and_chainload_main(void) {
    for(size_t i = 0; i < g_chainloader_num_entries; i++) {
        chainloader_entry_t *entry = &g_chainloader_entries[i];
        xmemmove((void *)entry->load_address, (const void *)entry->src_address, entry->size);
    }

    ((void (*)(int, void *))g_chainloader_entrypoint)(g_chainloader_argc, g_chainloader_arg_data);
}
