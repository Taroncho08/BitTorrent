#pragma once
#include "Parse.hpp"
#include "TorrentFile.hpp"
#include "TorrentFileBuilder.hpp"
#include <fstream>
#include <sstream>

class BitTorrent {
public:
    BitTorrent() = default;
    BitTorrent(const std::string& path) {
        init_file(path);
    }

private:
    void init_file(const std::string& path) {
        std::ifstream file(path);
        std::string content{std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};

        BencodeValue parsed_value = parser.parse(content);
        files.push_back(builder.build(parsed_value));
    }     

    void request_to_tracker() {
        
    }


private:
    Bencode_Parser parser;
    TorrentFileBuilder builder;
    std::vector<TorrentFile> files;
};