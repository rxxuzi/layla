#ifndef SECURE_IO_H
#define SECURE_IO_H

#ifdef __cplusplus
extern "C" {
#endif
    #include <stddef.h> // for size_t
    // write to file securely
    int s_w2f(const char *filename, const unsigned char *data, size_t data_size);
    // read from file securely
    int s_r2f(const char *filename, unsigned char **data, size_t *data_size);
    // copy file securely
    int s_cpf(const char *src_path, const char *dst_path);

#ifdef __cplusplus
}
#endif

#endif // SECURE_IO_H

