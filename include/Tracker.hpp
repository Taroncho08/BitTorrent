#pragma once
#include <string>
#include <regex>
//#include "TorrentFile.hpp"

class TorrentFile;

class Tracker {
public:
    Tracker() = default;
    Tracker(const std::string& addr, u_int16_t port = 80) : port{port} {
        setAddress(addr);
    }

    void setAddress(const std::string& addr);

    const std::string getAddress() const {
        return host + second_part;
    }

    const std::string& getHost() const;
    void setHost(const std::string& addr);

    u_int16_t getPort() const;
    void setPort(u_int16_t val);

    std::string buildRequest(const TorrentFile& file) const;

private:
    void parseAddress(const std::string& addr);
private:
    std::string host;
    std::string second_part;
    u_int16_t port;
};