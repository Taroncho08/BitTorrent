#include "FileItem.hpp"

FileItem::FileItem(const std::string& name, const std::string& path, int64_t length, int64_t mdSum)
    : path(path), length(length) {}

const std::string& FileItem::getPath() const {
    return path;
}

void FileItem::setPath(const std::string& value) {
    path = value;
}

int64_t FileItem::getLength() const {
    return length;
}

void FileItem::setLength(int64_t value) {
    length = value;
}
