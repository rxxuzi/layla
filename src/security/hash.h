#ifndef HASH_H
#define HASH_H
# ifdef  __cplusplus
extern "C" {
# endif
    char* SHA256(char* data);
    char* SHA256F(char *file_path);
# ifdef  __cplusplus
}
#endif
#endif //HASH_H
