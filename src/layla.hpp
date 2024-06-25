// layla.hpp
#ifndef LAYLA_HPP
#define LAYLA_HPP

#include "security/cipher.hpp"
#include "security/hash.h"
#include "security/key.hpp"

#define LAYLA_VERSION "0.2"
#define OK 0
#define ENCRYPT_MODE true
#define DECRYPT_MODE false

class Layla {
public:
    Layla(const std::string& file_path, bool encrypt_mode, bool recursive);
    Layla(const std::string &file_path, bool encrypt_mode);

    void update(const std::string& path, bool recursive);
    void display() const;
    bool enc();
    bool dec();

private:
    std::string input;
    std::vector<std::string> file_list;
    std::vector<std::string> layla_list;
    bool encrypt_mode;
    bool status;
};

bool enc(Cipher& cipher);
bool dec(Cipher& cipher);

#endif //LAYLA_HPP
