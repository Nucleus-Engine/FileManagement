#include "FileWrapper.h"

FileWrapper::FileWrapper() : m_fileStream(), m_fileName(), m_mutex(), m_cout(std::cout)
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
    {
        return false;
    }

    m_cout << "Opening file\n";
    m_fileStream.open(fileName, std::ios::in | std::ios::app);
    m_fileName = fileName;
    return m_fileStream.is_open();
}

void FileWrapper::closeFile()
{
    std::lock_guard<std::mutex> guard(m_mutex);
    if (isOpen())
    {
        m_fileStream.close();
        m_fileName = "";
    }
}

bool FileWrapper::isOpen()
{
    return m_fileStream.is_open();
}

const std::string& FileWrapper::getFileName()
{
    std::lock_guard<std::mutex> guard(m_mutex);
    return m_fileName;
}
