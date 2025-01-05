#pragma once

#include "BencodeValue.hpp"
#include "TorrentFile.hpp"
#include "Encoding.hpp"
#include <sstream>

class InfoHashCalculator {
public:
    InfoHashCalculator() = default;

    std::string getInfoHash(const BencodeValue& parsed) {
        auto dict = std::get<std::unordered_map<std::string, BencodeValue>>(parsed);
        return encoder.compute_SHA1(serialize_bencode(std::get<std::unordered_map<std::string, BencodeValue>>(dict["info"])));
    }
private:   
    std::string serialize_list(std::vector<BencodeValue> list) {
        std::ostringstream oss;

        oss << "l";
        for (const auto& i : list) {
            oss << serialize_bencode(i);
        }
        oss << "e";

        return oss.str();
    }

    std::string serialize_dict(std::unordered_map<std::string, BencodeValue> dict) {
        std::ostringstream oss;

        oss << "d";
        for (auto [key, value] : dict) {
            oss << key << ":";
            oss << serialize_bencode(value);
        }
        oss << "e";

        return oss.str();
    }

    std::string serialize_bencode(const BencodeValue& value) {
        std::ostringstream oss;


        if (std::holds_alternative<int64_t>(value)) {
            oss << "i" << std::get<int64_t>(value) << "e";
        } else if (std::holds_alternative<std::string>(value)) {
            std::string tmp = std::get<std::string>(value);
            oss << tmp.size() << ":" << tmp;
        } else if (std::holds_alternative<std::vector<BencodeValue>>(value)) {
            oss << serialize_list(std::get<std::vector<BencodeValue>>(value));
        } else if (std::holds_alternative<std::unordered_map<std::string, BencodeValue>>(value)) {
            oss << serialize_dict(std::get<std::unordered_map<std::string, BencodeValue>>(value));
        } else {
            throw std::runtime_error("Wrong type");
        }

        return oss.str();
    }

private:
    Encoding encoder;
    
};