// key.hpp
#ifndef KEY_HPP
#define KEY_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <openssl/rand.h>

#define LAYLA_OUTPUT_KEYNAME "layla.key"

class Key {
public:
    // 空コンストラクタ：ランダムに鍵を生成
    Key();

    // 文字列から鍵を生成
    explicit Key(const std::string& password);

    // ファイルから鍵を生成
    explicit Key(const char* filename);

    // 鍵を取得する
    [[nodiscard]] const unsigned char* get() const;
    void out() const; // 鍵を16進数で出力するメソッド
    void gen() const; // 鍵をファイルに保存するメソッド
    [[nodiscard]] int len() const;  // 鍵の長さを取得
    ~Key();


private:
    std::vector<unsigned char> key;
    void loadFromString(const std::string& str);
    void loadFromFile(const char* filename);
    void generateRandomKey();
};

#endif //KEY_HPP
