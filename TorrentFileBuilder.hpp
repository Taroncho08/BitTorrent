#pragma once
#include "Encoding.hpp"
#include "TorrentFile.hpp"
#include "InfoHashCalculator.hpp"

class TorrentFileBuilder {
public:
    TorrentFile build(const BencodeValue& parsed) {
        std::unordered_map<std::string, BencodeValue> dict = std::get<std::unordered_map<std::string, BencodeValue>>(parsed);

        TorrentFile torrent_file;

        torrent_file.setAnnounce(std::get<std::string>(dict["announce"]));

        hash_info_calc.getInfoHash(parsed);
        
        if (dict.count("announce_list")) {
            auto tmp_list = std::get<std::vector<BencodeValue>>(dict["announce_list"]);
            std::vector<std::string> tmp_vec;

            for (auto &i : tmp_list) {
                tmp_vec.push_back(std::get<std::string>(i));
            }

            torrent_file.setAnnounceList(tmp_vec);
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

        std::unordered_map<std::string, BencodeValue> info = std::get<std::unordered_map<std::string, BencodeValue>>(dict["info"]);

        torrent_file.setName(std::get<std::string>(info["name"]));
        torrent_file.setPieceLength(std::get<int64_t>(info["piece length"]));

        
        if (info.count("files")) {
            torrent_file.setNameOfDirectory(std::get<std::string>(info["name"]) + '/');
            auto file_list = std::get<std::vector<BencodeValue>>(info["files"]);

            torrent_file.setFiles(getAllFiles(file_list));

        }

        return torrent_file;
    }

    std::vector<FileItem> getAllFiles(const std::vector<BencodeValue>& file_list) {
        std::vector<FileItem> tmp_file_list;
        for (auto &i : file_list) {
            FileItem tmp;

            std::string path;
            for (auto &j : std::get<std::vector<BencodeValue>>(std::get<std::unordered_map<std::string, BencodeValue>>(i).at("path"))) {
                path += std::get<std::string>(j);
                path += '/';
            }

            tmp.setPath(path);
            tmp.setLength(std::get<int64_t>(std::get<std::unordered_map<std::string, BencodeValue>>(i).at("length")));

            tmp_file_list.push_back(tmp);

        }

        return tmp_file_list;
    }

private:
    InfoHashCalculator hash_info_calc;
    
};