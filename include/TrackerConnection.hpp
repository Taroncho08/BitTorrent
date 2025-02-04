#pragma once
#include <iostream>
// #include "Tracker.hpp"
#include "TorrentFile.hpp"
#include <boost/asio.hpp>

class TrackerConnection {
public:
    TrackerConnection(boost::asio::io_context& context) : io_context{context}, resolver(context), sock{io_context} {}

    void sendRequest(const TorrentFile& file);

private:
    void resolve_tracker(const TorrentFile& file);
    void connect_to_tracker(boost::asio::ip::tcp::resolver::iterator endpoint, const TorrentFile& file);
    void send_request(const TorrentFile& file);
    void read_response(const TorrentFile& file);

private:
    boost::asio::io_context& io_context;
    boost::asio::ip::tcp::resolver resolver;
    boost::asio::ip::tcp::socket sock;
    
};