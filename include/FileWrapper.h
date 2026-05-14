#ifndef FILE_WRAPPER_H
#define FILE_WRAPPER_H

#include <fstream>
#include <mutex>
#include <iostream>

class FileWrapper
{
  public:
    /**
     * @brief Construct a new File Wrapper object
     */
    FileWrapper();

    /**
     * @brief Destroy the File Wrapper object
     */
    virtual ~FileWrapper();

    bool openFile(const std::string& fileName);
    void closeFile();

    bool isOpen();

    const std::string& getFileName();

    template <typename T>
    FileWrapper& operator<<(const T &x)
    {
      if (isOpen())
      {
        std::lock_guard<std::mutex> lock(m_mutex);
        std::cout << "Writing " << x << " to file\n";
        m_fileStream << x;
      }
      return *this;
    }

  private:
    /**
     * @brief Deleted copy constructor to prevent copy
     */
    FileWrapper(const FileWrapper& other) = delete;

    /**
     * @brief Assignment operator deleted to prevent assignment
     */
    FileWrapper& operator=(const FileWrapper& other) = delete;

    std::fstream m_fileStream;  //!< File stream for reading/writing
    std::string m_fileName;     //!< Name of the file open
    std::mutex  m_mutex;        //!< Mutex for thread-safety
};

#endif // FILE_WRAPPER_H
