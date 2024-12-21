#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "Parse.hpp"

class FileItem {
public:
    FileItem() = default;
    FileItem(const std::string& name, const std::string& path, long length, long mdSum)
        : path(path), length(length) {}

    const std::string& getPath() const { return path; }
    void setPath(const std::string& value) { path = value; }

    long getLength() const { return length; }
    void setLength(long value) { length = value; }

private:
    std::string path;
    long length;
};

class TorrentFile {
public:
    TorrentFile() = default;
    TorrentFile(const std::string& announce,
                 const std::vector<std::string>& announce_list,
                 const std::string& created_by,
                 long creation_date,
                 const std::string& encoding,
                 const std::string& comment,
                 const std::string& name,
                 const std::vector<FileItem>& files,
                 const std::string& name_of_directory,
                 long piece_length)
        : announce(announce),
          announce_list(announce_list),
          created_by(created_by),
          creation_date(creation_date),
          encoding(encoding),
          comment(comment),
          files(files),
          name(name),
          name_of_directory(name_of_directory),
          piece_length(piece_length) {}

    const std::string& getAnnounce() const { return announce; }
    void setAnnounce(const std::string& value) { announce = value; }

    const std::vector<std::string>& getAnnounceList() const { return announce_list; }
    void setAnnounceList(const std::vector<std::string>& value) { announce_list = value; }

    const std::string& getCreatedBy() const { return created_by; }
    void setCreatedBy(const std::string& value) { created_by = value; }

    long getCreationDate() const { return creation_date; }
    void setCreationDate(long value) { creation_date = value; }

    const std::string& getEncoding() const { return encoding; }
    void setEncoding(const std::string& value) { encoding = value; }

    const std::string& getComment() const { return comment; }
    void setComment(const std::string& value) { comment = value; }

    const std::vector<FileItem>& getFiles() const { return files; }
    void setFiles(const std::vector<FileItem>& value) { files = value; }

    const std::string& getNameOfDirectory() const { return name_of_directory; }
    void setNameOfDirectory(const std::string& value) { name_of_directory = value; }

    const std::string& getName() const { return name; }
    void setName(const std::string& value) { name = value; }

    long getPieceLength() const { return piece_length; }
    void setPieceLength(long value) { piece_length = value; }


private:
    std::string announce;
    std::vector<std::string> announce_list;
    std::string name;
    std::string created_by;
    long creation_date;

    std::string encoding;
    std::string comment;

    std::vector<FileItem> files;
    std::string name_of_directory;

    long piece_length;

};

class TorrentFileBuilder {
public:
    TorrentFile build(const BencodeValue& parsed) {
        std::unordered_map<std::string, BencodeValue> dict = std::get<std::unordered_map<std::string, BencodeValue>>(parsed);

        TorrentFile torrent_file;

        torrent_file.setAnnounce(std::get<std::string>(dict["announce"]));

        if (dict.count("announce_list")) {
            auto tmp_list = std::get<std::vector<BencodeValue>>(dict["announce_list"]);
            std::vector<std::string> tmp_vec;

            for (auto &i : tmp_list) {
                tmp_vec.push_back(std::get<std::string>(i));
            }

            torrent_file.setAnnounceList(tmp_vec);
        }

        if (dict.count("creation date")) {
            torrent_file.setCreationDate(std::get<long>(dict["creation date"]));
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
        torrent_file.setPieceLength(std::get<long>(info["piece length"]));

        std::vector<FileItem> tmp_file_list;
        if (info.count("files")) {
            torrent_file.setNameOfDirectory(std::get<std::string>(info["name"]) + '/');
            auto file_list = std::get<std::vector<BencodeValue>>(info["files"]);

            for (auto &i : file_list) {
                FileItem tmp;

                std::string path;
                for (auto &j : std::get<std::vector<BencodeValue>>(std::get<std::unordered_map<std::string, BencodeValue>>(i)["path"])) {
                    path += std::get<std::string>(j) += "/";
                }

                tmp.setPath(path);
                tmp.setLength(std::get<long>(std::get<std::unordered_map<std::string, BencodeValue>>(i)["length"]));

                tmp_file_list.push_back(tmp);

            }

            torrent_file.setFiles(tmp_file_list);

        }

        return torrent_file;
    }
private:
    
};