#pragma once

#include "Parser.hpp"
#include "TorrentFile.hpp"
#include "TorrentFileBuilder.hpp"
#include <fstream>
#include <sstream>
#include <vector>

class BitTorrent {
public:
    BitTorrent() = default;
    explicit BitTorrent(const std::string& path);

private:
    void init_file(const std::string& path);

private:
    Bencode_Parser parser;
    TorrentFileBuilder builder;
    std::vector<TorrentFile> files;
};
