#pragma once
#include <openssl/sha.h>
#include <string>
#include <iomanip>
#include <sstream>

class Encoding{
public:
    Encoding() = default;
    std::string compute_SHA1(const std::string& input) {
        unsigned char hash[SHA_DIGEST_LENGTH];
        SHA1(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), hash);

        return std::string(reinterpret_cast<char*>(hash), SHA_DIGEST_LENGTH);
    }

    std::string urlEncode(const std::string &value) {
        std::ostringstream escaped;
        escaped.fill('0');
        escaped << std::hex;

        for (char c : value) {
            if (isalnum(static_cast<unsigned char>(c)) || c == '-' || c == '_' || c == '.' || c == '~') {
                escaped << c;
            } else {
                escaped << '%' << std::setw(2) << static_cast<int>(static_cast<unsigned char>(c));
            }
        }

        return escaped.str();
    }
};