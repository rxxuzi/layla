// cipher.cpp
#include "cipher.hpp"
#include <openssl/aes.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <utility>
#include <openssl/rand.h>
#include <codecvt>

void addPKCS7Padding(std::vector<unsigned char>& data) {
    size_t block_size = AES_BLOCK_SIZE;
    size_t padding_size = block_size - (data.size() % block_size);
    data.insert(data.end(), padding_size, static_cast<unsigned char>(padding_size));
}

void stripPKCS7Padding(std::vector<unsigned char>& data) {
    if (data.empty()) return;
    unsigned char padding_size = data.back();
    if (padding_size > 0 && padding_size <= AES_BLOCK_SIZE) {
        data.resize(data.size() - padding_size);
    }
}

Cipher::Cipher(std::string  file_name, const unsigned char* key, int key_size)
        : file_name(std::move(file_name)), key(new unsigned char[key_size]), key_size(key_size), data_size(0) {
    std::memcpy(this->key, key, key_size);  // std::memcpy を使用
    is_encrypted = is_file_encrypted();
}

Cipher::Cipher(std::string  file_name, Key& key)
        : file_name(std::move(file_name)), key_size(key.len()) {  // key.len() でキーの長さを取得
    this->key = new unsigned char[key_size];  // 鍵サイズに合わせてメモリを確保
    const unsigned char* key_data = key.get();  // Key クラスから鍵データを取得
    std::memcpy(this->key, key_data, key_size);  // std::memcpy を使用してデータをコピー
    is_encrypted = is_file_encrypted();
}

Cipher::~Cipher() {
    delete[] key;
}

bool Cipher::read() {
    std::ifstream file(file_name, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        return false;
    }

    data_size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<unsigned char> buffer(data_size);

    if (!file.read(reinterpret_cast<char*>(buffer.data()), data_size)) {
        return false;
    }

    if (is_encrypted) {
        enc = buffer;
    } else {
        data = buffer;
    }

    file.close();
    return true;
}

bool Cipher::is_file_encrypted() const {
    return file_name.size() >= 6 && file_name.substr(file_name.size() - 6) == ".layla";
}

bool Cipher::write() {
    std::string new_file_name;

    // ファイル名の処理
    if (is_encrypted) {
        size_t last_dot = file_name.rfind('.');
        if (last_dot == std::string::npos) {
            return false;
        } else {
            new_file_name = file_name.substr(0, last_dot);
        }
    } else {
        new_file_name = file_name + LAYLA_EXT;
    }

    // 適切なデータをファイルに書き込む
    std::vector<unsigned char> *data_to_write = is_encrypted ? &data : &enc;
    if (s_w2f(new_file_name.c_str(), data_to_write->data(), data_to_write->size()) != 0) {
        return false;
    }
    return true;
}


bool Cipher::encrypt() {
    if (data.empty()) {
        return false;
    }

    addPKCS7Padding(data);

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        return false;
    }

    unsigned char iv[AES_BLOCK_SIZE];
    RAND_bytes(iv, sizeof(iv));

    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key, iv)) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    std::vector<unsigned char> encrypted_data(data.size() + AES_BLOCK_SIZE + sizeof(iv));
    int len;
    int ciphertext_len;

    memcpy(encrypted_data.data(), iv, sizeof(iv));

    if (1 != EVP_EncryptUpdate(ctx, encrypted_data.data() + sizeof(iv), &len, data.data(), data.size())) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    ciphertext_len = len;

    if (1 != EVP_EncryptFinal_ex(ctx, encrypted_data.data() + sizeof(iv) + len, &len)) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    ciphertext_len += len;
    encrypted_data.resize(sizeof(iv) + ciphertext_len);

    EVP_CIPHER_CTX_free(ctx);
    enc = encrypted_data;

    return true;
}


bool Cipher::decrypt() {
    if (enc.empty()) {
        return false;
    }

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        return false;
    }

    unsigned char iv[AES_BLOCK_SIZE];
    memcpy(iv, enc.data(), sizeof(iv));

    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key, iv)) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    std::vector<unsigned char> decrypted_data(enc.size() - sizeof(iv));
    int len;
    int plaintext_len;

    if (1 != EVP_DecryptUpdate(ctx, decrypted_data.data(), &len, enc.data() + sizeof(iv), enc.size() - sizeof(iv))) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    plaintext_len = len;

    if (1 != EVP_DecryptFinal_ex(ctx, decrypted_data.data() + len, &len)) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    plaintext_len += len;
    decrypted_data.resize(plaintext_len);
    stripPKCS7Padding(decrypted_data);

    data = decrypted_data;
    EVP_CIPHER_CTX_free(ctx);

    return true;
}
