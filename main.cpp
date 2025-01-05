#pragma once
#include "Parse.hpp"
#include "BitTorrent.hpp"
#define ASIO_STANDALONE
#include "TorrentFile.hpp"
#include <fstream>
#include <sstream>
#include <thread>
#include <functional>
#include <boost/asio.hpp>
#include "InfoHashCalculator.hpp"

void printBencodeValue(const BencodeValue& value, int indent = 0) {
    std::string indentation(indent, ' ');

    std::visit([&](const auto& v) {
        using T = std::decay_t<decltype(v)>;
        if constexpr (std::is_same_v<T, int64_t>) {
            std::cout << indentation << v << '\n';
        } else if constexpr (std::is_same_v<T, std::string>) {
            std::cout << indentation << '"' << v << '"' << '\n';
        } else if constexpr (std::is_same_v<T, std::vector<BencodeValue>>) {
            std::cout << indentation << "[\n";
            for (const auto& item : v) {
                printBencodeValue(item, indent + 2); 
            }
            std::cout << indentation << "]\n";
        } else if constexpr (std::is_same_v<T, std::unordered_map<std::string, BencodeValue>>) {
            std::cout << indentation << "{\n";
            for (const auto& [key, val] : v) {
                std::cout << indentation << "  \"" << key << "\": ";
                printBencodeValue(val, indent + 2);
            }
            std::cout << indentation << "}\n";
        }
    }, value);
}

int main() {

    std::ifstream file("/home/taron/Desktop/torrent_files/debian-12.8.0-amd64-netinst.iso.torrent");
    
    std::string content{std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
    
    Bencode_Parser parser;

    InfoHashCalculator calc;

    std::cout << calc.getInfoHash(parser.parse(content));
    

}