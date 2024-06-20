#include "secure_io.h"
#include <stdio.h>
#include <windows.h>

// Function to securely copy a file from source to destination using Windows API
int s_cpf(const char *src_path, const char *dst_path) {
    BOOL result = CopyFile(src_path, dst_path, FALSE);  // FALSE to overwrite if file exists
    if (result == 0) {
        DWORD error = GetLastError();
        fprintf(stderr, "Failed to copy file: %lu\n", error);
        return -1;
    }
    return 0;
}
