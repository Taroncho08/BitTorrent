#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
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
                 const std::string& info_hash,
                 const std::string& peer_id);

    const std::string& getAnnounce() const;
    void setAnnounce(const std::string& value);

    const std::vector<std::string>& getAnnounceList() const;
    void setAnnounceList(const std::vector<std::string>& value);

    const std::string& getCreatedBy() const;
    void setCreatedBy(const std::string& value);

    int64_t getCreationDate() const;
    void setCreationDate(int64_t value);

    const std::string& getEncoding() const;
    void setEncoding(const std::string& value);

    const std::string& getComment() const;
    void setComment(const std::string& value);

    const std::vector<FileItem>& getFiles() const;
    void setFiles(const std::vector<FileItem>& value);

    const std::string& getNameOfDirectory() const;
    void setNameOfDirectory(const std::string& value);

    const std::string& getName() const;
    void setName(const std::string& value);

    int64_t getPieceLength() const;
    void setPieceLength(int64_t value);

    void setInfoHash(const std::string& hash);
    const std::string& getInfoHash() const;

    void setUrlSafeInfoHash(const std::string& hash);
    const std::string& getUrlSafeInfoHash() const;

    void setPeerId(const std::string& id);
    const std::string& getPeerId() const;

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
    std::string peer_id;
};
