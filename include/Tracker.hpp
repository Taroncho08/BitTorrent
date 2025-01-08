#pragma once
#include <string>

class Tracker {
public:
    Tracker(const std::string& addr) : address{addr} {}

    const std::string& getAddress() const { return address; }
    void setAddress(const std::string& addr) { address = addr; }


private:
    std::string address;
};