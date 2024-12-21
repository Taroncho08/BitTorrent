// #include "Parse.hpp"
// #include "BitTorrent.hpp"
#include "TorrentFile.hpp"
#include <fstream>
#include <sstream>

int main() {

    std::ifstream file("/home/taron/Desktop/torrent_files/Stalker.torrent");
    
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    
    Bencode_Parser parser;
    auto val = parser.parse(content);

    TorrentFileBuilder builder;

    auto fil = builder.build(val);

    std::cout << "ng";
    

}