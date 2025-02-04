#include "TrackerConnection.hpp"

void TrackerConnection::sendRequest(const TorrentFile& file) {
    resolve_tracker(file);
}

void TrackerConnection::resolve_tracker(const TorrentFile& file) {
    if (file.getMainTracker().getHost().empty()) {
        std::cerr << "Error: Tracker host is empty!" << std::endl;
        return;
    }
    resolver.async_resolve(boost::asio::ip::tcp::v4(), file.getMainTracker().getHost(), std::to_string(file.getMainTracker().getPort()), [this, &file](boost::system::error_code ec, boost::asio::ip::tcp::resolver::iterator endpoint) {
        std::cout << "resolve" << std::endl;
        if (!ec) {
            for (auto it = endpoint; it != boost::asio::ip::tcp::resolver::iterator(); ++it) {
                std::cout << "Resolved IP: " << it->endpoint().address().to_string() << std::endl;
            }
            connect_to_tracker(endpoint, file);
        }
        else {
            std::cerr << "Resolve error: " << ec.message();
        }
    });
}

void TrackerConnection::connect_to_tracker(boost::asio::ip::tcp::resolver::iterator endpoint, const TorrentFile& file) {
    boost::asio::async_connect(sock, endpoint, [this, &file](const boost::system::error_code& ec, boost::asio::ip::tcp::resolver::iterator connected_endpoint) {
        std::cout << "connect" << std::endl;
        if (!ec) {
            send_request(file);
        }
        else {
            std::cerr << "Connection error: " << ec.message();
        }
    });
}

void TrackerConnection::send_request(const TorrentFile& file) {
    boost::asio::async_write(sock, boost::asio::buffer(file.getMainTracker().buildRequest(file)), [this, &file](boost::system::error_code ec, std::size_t bytes) {
        std::cout << "send" << std::endl;
        if (!ec) {
            read_response(file);
        }
        else {
            std::cerr << "Request sending error: " << ec.message();
        }
    });
}

void TrackerConnection::read_response(const TorrentFile& file) {
    boost::asio::streambuf buf;
    boost::asio::async_read(sock, buf, [this, &file, &buf](boost::system::error_code ec, std::size_t bytes) {
        if (!ec) {
                std::istream response_stream(&buf);
                std::string response((std::istreambuf_iterator<char>(response_stream)), {});
                std::cout << "Tracker Response:\n" << response << std::endl;
            } else {
                std::cerr << "Read error: " << ec.message() << std::endl;
            }
    });
}