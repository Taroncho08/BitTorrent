#pragma once
#include <string>

class FileItem {
public:
    FileItem() = default;
    FileItem(const std::string& name, const std::string& path, int64_t length, int64_t mdSum);

    const std::string& getPath() const;
    void setPath(const std::string& value);

    int64_t getLength() const;
    void setLength(int64_t value);

private:
    std::string path;
    int64_t length;
};
