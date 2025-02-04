#include "TorrentFileBuilder.hpp"

TorrentFile TorrentFileBuilder::build(const BencodeValue& parsed, const std::string& client_id, const std::string& version) {
    std::map<std::string, BencodeValue> dict = std::get<std::map<std::string, BencodeValue>>(parsed);

    TorrentFile torrent_file;

    torrent_file.setAnnounce(std::get<std::string>(dict.at("announce")));
    torrent_file.setMainTracker(Tracker(torrent_file.getAnnounce()));

    torrent_file.setInfoHash(hash_info_calc.getInfoHash(parsed));
    torrent_file.setUrlSafeInfoHash(hash_info_calc.getUrlSafeInfoHash(parsed));
    torrent_file.setPeerId(generatePeerId(client_id, version));

    if (dict.count("announce_list")) {
        auto tmp_list = std::get<std::vector<BencodeValue>>(dict["announce_list"]);
        std::vector<std::string> tmp_vec { torrent_file.getMainTracker().getAddress() };
        std::vector<Tracker> tmp_tracker_list { torrent_file.getMainTracker() };
        for (auto& i : tmp_list) {
            tmp_vec.push_back(std::get<std::string>(i));
            tmp_tracker_list.push_back(Tracker(std::get<std::string>(i)));
        }
        torrent_file.setAnnounceList(tmp_vec);
        torrent_file.setTrackerList(tmp_tracker_list);
    }

    if (dict.count("creation date")) {
        torrent_file.setCreationDate(std::get<int64_t>(dict["creation date"]));
    }

    if (dict.count("created by")) {
        torrent_file.setCreatedBy(std::get<std::string>(dict["created by"]));
    }

    if (dict.count("comment")) {
        torrent_file.setComment(std::get<std::string>(dict["comment"]));
    }

    if (dict.count("encoding")) {
        torrent_file.setEncoding(std::get<std::string>(dict["encoding"]));
    }

    std::map<std::string, BencodeValue> info = std::get<std::map<std::string, BencodeValue>>(dict["info"]);
    torrent_file.setName(std::get<std::string>(info["name"]));
    torrent_file.setPieceLength(std::get<int64_t>(info["piece length"]));

    if (info.count("files")) {
        torrent_file.setNameOfDirectory(std::get<std::string>(info["name"]) + '/');
        auto file_list = std::get<std::vector<BencodeValue>>(info["files"]);
        torrent_file.setFiles(getAllFiles(file_list));
    }

    return torrent_file;
}

std::vector<FileItem> TorrentFileBuilder::getAllFiles(const std::vector<BencodeValue>& file_list) {
    std::vector<FileItem> tmp_file_list;
    for (auto& i : file_list) {
        FileItem tmp;
        std::string path;

        for (auto& j : std::get<std::vector<BencodeValue>>(std::get<std::map<std::string, BencodeValue>>(i).at("path"))) {
            path += std::get<std::string>(j);
            path += '/';
        }

        tmp.setPath(path);
        tmp.setLength(std::get<int64_t>(std::get<std::map<std::string, BencodeValue>>(i).at("length")));
        tmp_file_list.push_back(tmp);
    }
    return tmp_file_list;
}

std::string TorrentFileBuilder::generatePeerId(const std::string& client_id, const std::string& version) {
    if (client_id.size() != 2 || version.size() != 4) {
        throw std::runtime_error("Wrong client_id or version");
    }

    std::string peer_id = "-" + client_id + version + "-";

    static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, sizeof(alphanum) - 2);

    for (int i = 0; i < 12; ++i) {
        peer_id += alphanum[dis(gen)];
    }

    return peer_id;
}
