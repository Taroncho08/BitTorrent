#include "Tracker.hpp"
#include "TorrentFile.hpp"

const std::string& Tracker::getHost() const { 
    return host; 
}

void Tracker::setHost (const std::string& addr) {
    host = addr; 
}

void Tracker::setAddress(const std::string& addr) {
    parseAddress(addr);
}

u_int16_t Tracker::getPort() const {
    return port;
}

void Tracker::setPort(u_int16_t val) {
    port = val;
}

std::string Tracker::buildRequest(const TorrentFile& file) const {
    std::string path = second_part + "?info_hash=" + file.getUrlSafeInfoHash() + "&peer_id=" + file.getPeerId() 
     + "&port=" + std::to_string(port) + "&uploaded=0" + "&downloaded=0" + "&left=0" + "&compact=1";

    std::string request = 
    "GET " + path + " HTTP/1.1\r\n" +
    "Host: " + host + "\r\n" + 
    "User-Agent: " "BitTorrent/1.0\r\n" + 
    "Accept: */*\r\n" +
    "Connection: close\r\n\r\n";

    return request;
}

void Tracker::parseAddress(const std::string& addr) {
    std::regex pattern(R"(^(https?:\/\/)?([^\/:]+)(:(\d+))?(\/.*)?$)");
    std::smatch match;

    if (std::regex_match(addr, match, pattern)) {
        host = match[2].str();  // Extract hostname
        port = match[4].str().empty() ? 80 : std::stoi(match[4].str());  // Extract port (default: 80)
        second_part = match[5].str().empty() ? "/announce" : match[5].str();  // Extract path (default: "/announce")
    }
}