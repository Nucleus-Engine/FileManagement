#include "FileWrapper.h"

FileWrapper::FileWrapper() : m_fileName(), m_fileStream(), m_mutex()
{
}

FileWrapper::~FileWrapper()
{
    closeFile();
}

bool FileWrapper::openFile(const std::string& fileName)
{
    if (m_fileStream.is_open())
    {
        return false;
    }

    m_fileStream.open(fileName, std::ios::in | std::ios::out);
    m_fileName = fileName;
    return m_fileStream.is_open();
}

void FileWrapper::closeFile()
{
    if (m_fileStream.is_open())
    {
        m_fileStream.close();
    }
}

bool FileWrapper::isOpen()
{
    return false;
}

const std::string& FileWrapper::getFileName()
{
    return m_fileName;
}
