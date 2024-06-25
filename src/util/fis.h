// fis.h
#include <stdlib.h>
#include <stdbool.h>

#ifndef FIS_H
#define FIS_H
typedef struct {
    bool is_dir;       // パスがディレクトリかファイルか
    bool recursive;    // フォルダ内を再帰的に探索するか
    char **filepaths;  // ファイルパスを格納する配列
    size_t size;       // 格納されたファイルパスの数
} FIS;

FIS *newFIS(const char *path, bool recursive);
void FISDestroy(FIS *fs);
#endif //FIS_H
