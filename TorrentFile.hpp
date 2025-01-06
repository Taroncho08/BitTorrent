#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "Parse.hpp"
#include "FileItem.hpp"


class TorrentFile {
public:
    TorrentFile() = default;
    TorrentFile(const std::string& announce,
                 const std::vector<std::string>& announce_list,
                 const std::string& created_by,
                 int64_t creation_date,
                 const std::string& encoding,
                 const std::string& comment,
                 const std::string& name,
                 const std::vector<FileItem>& files,
                 const std::string& name_of_directory,
                 int64_t piece_length, 
                 const std::string& info_hash)
        : announce(announce),
          announce_list(announce_list),
          created_by(created_by),
          creation_date(creation_date),
          encoding(encoding),
          comment(comment),
          files(files),
          name(name),
          name_of_directory(name_of_directory),
          piece_length(piece_length),
          info_hash(info_hash) {}

    const std::string& getAnnounce() const { return announce; }
    void setAnnounce(const std::string& value) { announce = value; }

    const std::vector<std::string>& getAnnounceList() const { return announce_list; }
    void setAnnounceList(const std::vector<std::string>& value) { announce_list = value; }

    const std::string& getCreatedBy() const { return created_by; }
    void setCreatedBy(const std::string& value) { created_by = value; }

    int64_t getCreationDate() const { return creation_date; }
    void setCreationDate(int64_t value) { creation_date = value; }

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

    int64_t getPieceLength() const { return piece_length; }
    void setPieceLength(int64_t value) { piece_length = value; }

    void setInfoHash(const std::string& hash) { info_hash = hash; }
    const std::string& getInfoHash() const { return info_hash; }

    void setUrlSafeInfoHash(const std::string& hash) { url_safe_info_hash = hash; }
    const std::string& getUrlSafeInfoHash() const { return url_safe_info_hash; }


private:
    std::string announce;
    std::vector<std::string> announce_list;
    std::string name;
    std::string created_by;
    int64_t creation_date;

    std::string encoding;
    std::string comment;

    std::vector<FileItem> files;
    std::string name_of_directory;

    int64_t piece_length;

    std::string info_hash;
    std::string url_safe_info_hash;

};

