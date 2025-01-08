#pragma once

#include <iostream>
#include <string>
#include <variant>
#include <unordered_map>
#include <vector>
#include "BencodeValue.hpp"

class Bencode_Parser {
public:
    BencodeValue parse(const std::string& input);

private:
    BencodeValue parseValue(const std::string& input);
    int64_t parseInt(const std::string& input);
    std::vector<BencodeValue> parseList(const std::string& input);
    std::unordered_map<std::string, BencodeValue> parseDict(const std::string& input);
    std::string parseString(const std::string& input);

private:
    std::size_t pos = 0;
};
