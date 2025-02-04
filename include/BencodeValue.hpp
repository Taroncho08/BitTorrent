#pragma once
#include <variant>
#include <string>
#include <vector>
#include <map>

struct BencodeValue;

using BencodeVariant = std::variant<int64_t, std::string, std::vector<BencodeValue>, std::map<std::string, BencodeValue>>;

struct BencodeValue : public BencodeVariant
{
    using BencodeVariant::BencodeVariant;
};