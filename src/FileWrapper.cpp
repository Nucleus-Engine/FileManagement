#include "FileWrapper.h"

FileWrapper::FileWrapper()
    : m_fileStream()
    , m_fileName()
    , m_mutex()
{
}

FileWrapper::~FileWrapper()
{
    closeFile();
}

bool FileWrapper::openFile(const std::string& fileName)
{
    std::lock_guard<std::mutex> guard(m_mutex);

    if (isOpen())
        return false;

    m_fileStream.open(fileName, std::ios::in | std::ios::app);
    if (m_fileStream.is_open())
    {
        m_fileName = fileName;
        return true;
    }
    return false;
}

void FileWrapper::closeFile()
{
    std::lock_guard<std::mutex> guard(m_mutex);
    if (isOpen())
    {
        m_fileStream.close();
        m_fileName.clear();
    }
}

bool FileWrapper::isOpen() const
{
    return m_fileStream.is_open();
}

const std::string& FileWrapper::getFileName()
{
    std::lock_guard<std::mutex> guard(m_mutex);
    return m_fileName;
}