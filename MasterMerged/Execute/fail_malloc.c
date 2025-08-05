#include "execute.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static bool g_should_fail = false;
static const char *g_fail_file = NULL;
static int g_fail_line = -1;

// Call this to make the NEXT malloc fail after a specific line
void trigger_malloc_fail_next(const char *file, int line) {
    g_should_fail = true;
    g_fail_file = file;
    g_fail_line = line;
}

// The actual malloc wrapper
void *fail_malloc(size_t size, const char *file, int line) {
    // Check if we're AFTER the trigger line
    if (g_should_fail && g_fail_file && strcmp(file, g_fail_file) == 0 && line > g_fail_line) {
        fprintf(stderr, "[FAIL_MALLOC] Forced fail at %s:%d (size=%zu)\n", file, line, size);
        g_should_fail = false; // Reset after failing once
        return NULL;
    }

    // Otherwise, call the real malloc
#undef malloc
    void *ptr = malloc(size);
#define malloc(size) fail_malloc(size, __FILE__, __LINE__)
    return ptr;
}
