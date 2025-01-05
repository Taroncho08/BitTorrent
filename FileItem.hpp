#pragma once
#include <string>

class FileItem {
public:
    FileItem() = default;
    FileItem(const std::string& name, const std::string& path, int64_t length, int64_t mdSum)
        : path(path), length(length) {}

    const std::string& getPath() const { return path; }
    void setPath(const std::string& value) { path = value; }

    int64_t getLength() const { return length; }
    void setLength(int64_t value) { length = value; }

private:
    std::string path;
    int64_t length;
};