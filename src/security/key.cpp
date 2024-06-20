// key.cpp
#include "key.hpp"
#include <iomanip>

Key::Key() {
    generateRandomKey();
}

Key::Key(const std::string& password) {
    loadFromString(password);
}

Key::Key(const char* filename) {
    loadFromFile(filename);
}

const unsigned char* Key::get() const {
    return key.data();
}

int Key::len() const {
    return static_cast<int>(key.size());
}

Key::~Key() {
    // nothing to do
}

void Key::out() const {
    std::cout << "Key: ";
    for (auto byte : key) {
        std::cout << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(byte);
    }
    std::cout << std::dec << std::endl; // 16進数表示後は10進数に戻す
}

void Key::gen() const {
    std::ofstream file(LAYLA_OUTPUT_KEYNAME, std::ios::binary);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(key.data()), key.size());
        file.close();
    } else {
        std::cerr << "Failed to open file for writing." << std::endl;
    }
}

void Key::generateRandomKey() {
    key.resize(32);
    RAND_bytes(key.data(), key.size());
}

void Key::loadFromString(const std::string& str) {
    key.clear();
    key.reserve(32);
    for (size_t i = 0; i < str.size() && i < 32; ++i) {
        key.push_back(static_cast<unsigned char>(str[i]));
    }
    // 鍵の長さが32に満たない場合は0で埋める
    while (key.size() < 32) {
        key.push_back(0x00);
    }
}

void Key::loadFromFile(const char* filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file for key generation: " << filename << std::endl;
        generateRandomKey();  // ファイルが開けない場合はランダムな鍵を生成
        return;
    }
    char buffer;
    key.clear();
    key.reserve(32);
    while (file.read(&buffer, 1) && key.size() < 32) {
        key.push_back(static_cast<unsigned char>(buffer));
    }
    file.close();
    // 鍵の長さが32に満たない場合は0で埋める
    while (key.size() < 32) {
        key.push_back(0x00);
    }
}