#pragma once

#include "BencodeValue.hpp"
#include "Encoding.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <stdexcept>

class InfoHashCalculator {
public:
    InfoHashCalculator() = default;

    std::string getInfoHash(const BencodeValue& parsed);
    std::string getUrlSafeInfoHash(const BencodeValue& parsed);

private:
    std::string serialize_list(const std::vector<BencodeValue>& list);
    std::string serialize_dict(const std::unordered_map<std::string, BencodeValue>& dict);
    std::string serialize_bencode(const BencodeValue& value);

private:
    Encoding encoder;
};
