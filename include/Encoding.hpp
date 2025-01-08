#pragma once

#include <openssl/sha.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <cctype>

class Encoding {
public:
    Encoding() = default;

    std::string compute_SHA1(const std::string& input);
    std::string urlEncode(const std::string& value);
};
