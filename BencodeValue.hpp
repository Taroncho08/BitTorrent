#pragma once
#include <variant>
#include <string>
#include <vector>
#include <unordered_map>

struct BencodeValue;

using BencodeVariant = std::variant<int64_t, std::string, std::vector<BencodeValue>, std::unordered_map<std::string, BencodeValue>>;

struct BencodeValue : public BencodeVariant
{
    using BencodeVariant::BencodeVariant;
};