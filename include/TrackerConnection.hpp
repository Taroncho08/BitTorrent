#pragma once
#include <iostream>
// #include "Tracker.hpp"
#include "TorrentFile.hpp"
#include <boost/asio.hpp>
#include "Parser.hpp"


class TrackerConnection {
public:
    TrackerConnection(boost::asio::io_context& context) : io_context{context}, resolver(context), sock{io_context} {}

    BencodeValue updatePeerList(const TorrentFile& file);

private:
    
    std::string resolve_tracker(const TorrentFile& file);
    std::string connect_to_tracker(boost::asio::ip::tcp::resolver::iterator endpoint, const TorrentFile& file);
    std::string send_request(const TorrentFile& file);
    std::string read_header(const TorrentFile& file);
    std::string read_body(const TorrentFile& file, std::size_t bytes);


private:
    boost::asio::io_context& io_context;
    boost::asio::ip::tcp::resolver resolver;
    boost::asio::ip::tcp::socket sock;
    boost::asio::streambuf response_buffer;
    Bencode_Parser parser;
};