#include "TorrentFile.hpp"

TorrentFile::TorrentFile(const std::string& announce,
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
                         const std::string& peer_id)
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
      info_hash(info_hash),
      peer_id(peer_id) {}

const std::string& TorrentFile::getAnnounce() const {
    return announce;
}

void TorrentFile::setAnnounce(const std::string& value) {
    announce = value;
}

const std::vector<std::string>& TorrentFile::getAnnounceList() const {
    return announce_list;
}

void TorrentFile::setAnnounceList(const std::vector<std::string>& value) {
    announce_list = value;
}

const std::string& TorrentFile::getCreatedBy() const {
    return created_by;
}

void TorrentFile::setCreatedBy(const std::string& value) {
    created_by = value;
}

int64_t TorrentFile::getCreationDate() const {
    return creation_date;
}

void TorrentFile::setCreationDate(int64_t value) {
    creation_date = value;
}

const std::string& TorrentFile::getEncoding() const {
    return encoding;
}

void TorrentFile::setEncoding(const std::string& value) {
    encoding = value;
}

const std::string& TorrentFile::getComment() const {
    return comment;
}

void TorrentFile::setComment(const std::string& value) {
    comment = value;
}

const std::vector<FileItem>& TorrentFile::getFiles() const {
    return files;
}

void TorrentFile::setFiles(const std::vector<FileItem>& value) {
    files = value;
}

const std::string& TorrentFile::getNameOfDirectory() const {
    return name_of_directory;
}

void TorrentFile::setNameOfDirectory(const std::string& value) {
    name_of_directory = value;
}

const std::string& TorrentFile::getName() const {
    return name;
}

void TorrentFile::setName(const std::string& value) {
    name = value;
}

int64_t TorrentFile::getPieceLength() const {
    return piece_length;
}

void TorrentFile::setPieceLength(int64_t value) {
    piece_length = value;
}

void TorrentFile::setInfoHash(const std::string& hash) {
    info_hash = hash;
}

const std::string& TorrentFile::getInfoHash() const {
    return info_hash;
}

void TorrentFile::setUrlSafeInfoHash(const std::string& hash) {
    url_safe_info_hash = hash;
}

const std::string& TorrentFile::getUrlSafeInfoHash() const {
    return url_safe_info_hash;
}

void TorrentFile::setPeerId(const std::string& id) {
    peer_id = id;
}

const std::string& TorrentFile::getPeerId() const {
    return peer_id;
}
