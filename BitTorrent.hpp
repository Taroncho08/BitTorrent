#include "Parse.hpp"
#include "TorrentFile.hpp"

class BitTorrent {
public:
    BitTorrent() = default;
    

private:
    Bencode_Parser parser;
    std::vector<TorrentFile> files;
};