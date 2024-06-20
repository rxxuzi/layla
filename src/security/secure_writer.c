// secure_writer.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "secure_io.h"

// write to file securely
int s_w2f(const char *filename, const unsigned char *data, size_t data_size) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Failed to open file");
        return -1;
    }

    size_t written = fwrite(data, 1, data_size, file);
    if (written != data_size) {
        perror("Failed to write all data to file");
        fclose(file);
        return -1;
    }
    fclose(file);
    return 0;
}
