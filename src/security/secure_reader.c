// secure_reader.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// read from file securely
int s_r2f(const char *filename, unsigned char **data, size_t *data_size) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return -1;
    }

    // Move to the end of the file to determine the file size
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the data
    unsigned char *buffer = (unsigned char *)malloc(size);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return -1;
    }

    // Read the file into the buffer
    size_t read = fread(buffer, 1, size, file);
    if (read != size) {
        perror("Failed to read all data from file");
        free(buffer);
        fclose(file);
        return -1;
    }

    fclose(file);
    *data = buffer;
    *data_size = size;
    return 0;
}