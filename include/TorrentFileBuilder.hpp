#pragma once

#include "BencodeValue.hpp"
#include "TorrentFile.hpp"
#include "InfoHashCalculator.hpp"
#include "FileItem.hpp"
#include <unordered_map>
#include <string>
#include <vector>
#include <random>
#include <stdexcept>

class TorrentFileBuilder {
public:
    TorrentFile build(const BencodeValue& parsed, const std::string& client_id = "TR", const std::string& version = "0001");

private:
    std::vector<FileItem> getAllFiles(const std::vector<BencodeValue>& file_list);
    std::string generatePeerId(const std::string& client_id, const std::string& version);

private:
    InfoHashCalculator hash_info_calc; // Utility for calculating info hashes
};
