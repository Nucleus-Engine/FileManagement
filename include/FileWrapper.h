#ifndef FILE_WRAPPER_H
#define FILE_WRAPPER_H

#include <fstream>
#include <mutex>
#include <string>
#include <iostream>

class FileWrapper
{
public:
    FileWrapper();
    virtual ~FileWrapper();

    bool openFile(const std::string& fileName);
    void closeFile();

    bool isOpen() const;

    const std::string& getFileName();

    template <typename T>
    FileWrapper& operator<<(const T &x)
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        if (isOpen())
        {
            m_fileStream << x << '\n';
        }
        return *this;
    }

private:
    FileWrapper(const FileWrapper& other) = delete;
    FileWrapper& operator=(const FileWrapper& other) = delete;

    std::fstream    m_fileStream;
    std::string     m_fileName;
    std::mutex      m_mutex;
};

#endif // FILE_WRAPPER_H