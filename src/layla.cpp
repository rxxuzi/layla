#include "layla.hpp"
#include "util/console.h"
#include "security/hash.h"

/*
 * Encrypt function
 * @param cipher: Cipher object
 * @return bool: true if successful, false otherwise
 */
bool enc(Cipher& cipher) {
    if (!cipher.read()) {
        c_err("Error reading file.");
        return false;
    }
    c_M("File read successfully.");
    if (!cipher.encrypt()) {
        c_err("Encryption failed.");
        return false;
    }
    c_M("Encryption successful.");
    if (!cipher.write()) {
        c_err("Error writing encrypted data to file.");
        return false;
    }
    std::cout << "Encryption successful." << std::endl;

    char* hash = SHA256F(const_cast<char*>(cipher.file_name.c_str()));
    if (hash != nullptr) {
        c_info("Hash: %s", hash);
        free(hash);
    } else {
        c_err("Failed to compute SHA256 hash.");
    }
    return true;
}

/*
 * Decrypt function
 * @param cipher : Cipher object
 * @return bool  : true if successful, false otherwise
 */
bool dec(Cipher& cipher) {
    if (!cipher.read()) {
        std::cerr << "Error reading file." << std::endl;
        return false;
    }
    if (!cipher.decrypt()) {
        std::cerr << "Decryption failed." << std::endl;
        return false;
    }
    if (!cipher.write()) {
        std::cerr << "Error writing decrypted data to file." << std::endl;
        return false;
    }
    std::cout << "Decryption successful." << std::endl;
    char* hash = SHA256F(const_cast<char*>(cipher.file_name.c_str()));
    if (hash != nullptr) {
        c_info("Hash: %s", hash);
        free(hash);
    } else {
        c_err("Failed to compute SHA256 hash.");
    }
    return true;
}
