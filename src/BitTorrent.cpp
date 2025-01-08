#include "BitTorrent.hpp"

BitTorrent::BitTorrent(const std::string& path) {
    init_file(path);
}

void BitTorrent::init_file(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open the file: " + path);
    }

    std::string content{std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
    file.close();

    BencodeValue parsed_value = parser.parse(content);
    files.push_back(builder.build(parsed_value));
}
