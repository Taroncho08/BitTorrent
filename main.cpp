#include "Parse.cpp"
#include <fstream>
#include <sstream>

int main() {

    std::ifstream file("debian-12.8.0-amd64-netinst.iso.torrent");
    
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    
    Bencode_Parser parser;
    BencodeValue val = parser.parse(content);

    printBencodeValue(val);

}