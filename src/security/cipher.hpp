#ifndef Cipher_HPP
#define Cipher_HPP

#ifdef __cplusplus
#include <string>
#include <vector>
#include "key.hpp"
extern "C" {
#endif

#include <stddef.h>  // for size_t

int s_w2f(const char *filename, const unsigned char *data, size_t data_size);

#ifdef __cplusplus
}

#define LAYLA_EXT ".layla"

class Cipher {
public:
    Cipher(std::string file_name, const unsigned char* key, int key_size);
    Cipher(std::string file_name, Key& key);

    ~Cipher();

    bool encrypt();
    bool decrypt();
    bool read();
    bool write();

    std::string file_name;

private:
    unsigned char* key;
    int key_size;
    std::vector<unsigned char> data;
    std::vector<unsigned char> enc;
    std::size_t data_size;
    bool is_encrypted;
    [[nodiscard]] bool is_file_encrypted() const;
};

bool enc(Cipher& cipher);
bool dec(Cipher& cipher);
#endif // __cplusplus

#endif // Cipher_HPP

