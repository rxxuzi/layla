// fis.c
#include "fis.h"
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void FISDestroy(FIS *fs) {
    for (size_t i = 0; i < fs->size; ++i) {
        free(fs->filepaths[i]);
    }
    free(fs->filepaths);
    fs->filepaths = NULL;
    fs->size = 0;
}

void FISAddFile(FIS *fs, const char *file_path) {
    if (fs->size % 100 == 0) {  // 100要素ごとに容量を増やす
        char **new_filepaths = realloc(fs->filepaths, (fs->size + 100) * sizeof(char*));
        if (!new_filepaths) {
            // realloc に失敗した場合のエラーハンドリング
            perror("Failed to reallocate memory");
            return;  // ここで処理を中断
        }
        fs->filepaths = new_filepaths;  // realloc 成功時にのみポインタを更新
    }

    fs->filepaths[fs->size] = malloc(strlen(file_path) + 1);
    if (!fs->filepaths[fs->size]) {
        perror("Failed to allocate memory for new file path");
        return;  // mallocに失敗した場合のエラーハンドリング
    }
    strcpy(fs->filepaths[fs->size], file_path);
    fs->size++;
}

void FISListRecursive(FIS *fs, const char *path) {
    DIR *dir;
    struct dirent *entry;
    char full_path[1024];
    struct stat statbuf;

    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        if (stat(full_path, &statbuf) == -1) {
            continue; // エラーがあればスキップ
        }

        if (S_ISREG(statbuf.st_mode)) {
            FISAddFile(fs, full_path);
        } else if (fs->recursive && S_ISDIR(statbuf.st_mode)) {
            FISListRecursive(fs, full_path);
        }
    }

    closedir(dir);
}

void FISInit(FIS *fs, const char *path, bool recursive) {
    struct stat path_stat;
    stat(path, &path_stat);
    fs->recursive = recursive;
    if (S_ISREG(path_stat.st_mode)) {
        fs->is_dir = false;
        FISAddFile(fs, path);
    } else if (S_ISDIR(path_stat.st_mode)) {
        fs->is_dir = true;
        FISListRecursive(fs, path);
    } else {
        printf("\"%s\" is neither a file nor a directory.\n", path);
    }
}

FIS *newFIS(const char *path, bool recursive) {
    FIS *fs = malloc(sizeof(FIS));
    if (fs == NULL) {
        perror("Failed to allocate memory for FIS");
        return NULL;
    }

    *fs = (FIS){0};
    FISInit(fs, path, recursive);
    return fs;
}