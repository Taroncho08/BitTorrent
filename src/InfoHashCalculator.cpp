#include "InfoHashCalculator.hpp"

std::string InfoHashCalculator::getInfoHash(const BencodeValue& parsed) {
    auto dict = std::get<std::unordered_map<std::string, BencodeValue>>(parsed);
    auto info_dict = std::get<std::unordered_map<std::string, BencodeValue>>(dict.at("info"));
    return encoder.compute_SHA1(serialize_bencode(info_dict));
}

std::string InfoHashCalculator::getUrlSafeInfoHash(const BencodeValue& parsed) {
    auto dict = std::get<std::unordered_map<std::string, BencodeValue>>(parsed);
    auto info_dict = std::get<std::unordered_map<std::string, BencodeValue>>(dict.at("info"));
    return encoder.urlEncode(encoder.compute_SHA1(serialize_bencode(info_dict)));
}

std::string InfoHashCalculator::serialize_list(const std::vector<BencodeValue>& list) {
    std::ostringstream oss;
    oss << "l";
    for (const auto& item : list) {
        oss << serialize_bencode(item);
    }
    oss << "e";
    return oss.str();
}

std::string InfoHashCalculator::serialize_dict(const std::unordered_map<std::string, BencodeValue>& dict) {
    std::ostringstream oss;
    oss << "d";
    for (const auto& [key, value] : dict) {
        oss << key.size() << ":" << key;
        oss << serialize_bencode(value);
    }
    oss << "e";
    return oss.str();
}

std::string InfoHashCalculator::serialize_bencode(const BencodeValue& value) {
    std::ostringstream oss;

    if (std::holds_alternative<int64_t>(value)) {
        oss << "i" << std::get<int64_t>(value) << "e";
    } else if (std::holds_alternative<std::string>(value)) {
        const std::string& tmp = std::get<std::string>(value);
        oss << tmp.size() << ":" << tmp;
    } else if (std::holds_alternative<std::vector<BencodeValue>>(value)) {
        oss << serialize_list(std::get<std::vector<BencodeValue>>(value));
    } else if (std::holds_alternative<std::unordered_map<std::string, BencodeValue>>(value)) {
        oss << serialize_dict(std::get<std::unordered_map<std::string, BencodeValue>>(value));
    } else {
        throw std::runtime_error("Unsupported Bencode value type");
    }

    return oss.str();
}
