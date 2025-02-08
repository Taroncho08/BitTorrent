#include "TrackerConnection.hpp"

BencodeValue TrackerConnection::updatePeerList(const TorrentFile& file) {
    std::string response = resolve_tracker(file);

    // std::cout << response << std::endl;

    BencodeValue parsed = parser.parse(response);

    return parsed;
}

std::string TrackerConnection::resolve_tracker(const TorrentFile& file) {
    boost::asio::ip::tcp::resolver::iterator ep;
    try {
        if (file.getMainTracker().getHost().empty()) {
            std::cerr << "Error: Tracker host is empty!" << std::endl;
            return "";
        }
        boost::asio::ip::tcp::resolver::query resolver_query(file.getMainTracker().getHost(), std::to_string(file.getMainTracker().getPort()), boost::asio::ip::tcp::resolver::query::numeric_service);

        boost::system::error_code ec;
        ep = resolver.resolve(resolver_query);

        if (ec) {
            std::cout << "resolver error" << ec.message();
            return "";
        }

    } 
    catch (boost::system::system_error& e) {
        std::cout << e.what() << std::endl;
    }

    return connect_to_tracker(ep, file);
}

std::string TrackerConnection::connect_to_tracker(boost::asio::ip::tcp::resolver::iterator endpoint, const TorrentFile& file) {
    try{
        boost::asio::connect(sock, endpoint);
    
    }
    catch (boost::system::system_error& e) {
        std::cout << e.what() << std::endl;
    }
    
    return send_request(file);
}

std::string TrackerConnection::send_request(const TorrentFile& file) {
    try{
        boost::asio::write(sock, boost::asio::buffer(file.getMainTracker().buildRequest(file)));
    }
    catch (boost::system::system_error& e) {
        std::cout << e.what() << std::endl;
    }
    
    return read_header(file);

}

std::string TrackerConnection::read_header(const TorrentFile& file) {
    std::size_t content_length = 0;
    try {
        boost::asio::read_until(sock, response_buffer, "\r\n\r\n");

        std::istream response_stream(&response_buffer);
        std::string header;
        std::string line;

        while (std::getline(response_stream, line) && line != "\r") {
            if (line.find("Content-Length") == 0) {
                content_length = std::stoi(line.substr(15));
            }
            header += line += '\n';
        }            
        // std::cout << header << std::endl; 
        
    
    }
    catch (boost::system::system_error& e) {
        std::cout << e.what() << std::endl;
    }
    
    return read_body(file, content_length);

}

std::string TrackerConnection::read_body(const TorrentFile& file, std::size_t bytes) {
    std::string body;
    try {
        boost::system::error_code ec;
        boost::asio::read(sock, response_buffer, boost::asio::transfer_exactly(bytes), ec);

        if (!ec || ec == boost::asio::error::eof) {
            std::istream str(&response_buffer);
            body = {(std::istreambuf_iterator<char>{str}), {}};

        }
        
    }
    catch (boost::system::system_error& e) {
        std::cout << e.what();
    }

    return body;
}

