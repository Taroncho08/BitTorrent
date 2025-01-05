#pragma once
#include <openssl/sha.h>
#include <string>

class Encoding{
public:
    Encoding() = default;
    std::string compute_SHA1(const std::string& input) {
        unsigned char hash[SHA_DIGEST_LENGTH];
        SHA1(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), hash);

        return std::string(reinterpret_cast<char*>(hash), SHA_DIGEST_LENGTH);
    }
};