#include <gtest/gtest.h>
#include "../include/FileWrapper.h"
#include <thread>
#include <vector>
#include <filesystem>
#include <fstream>
#include <set>

namespace fs = std::filesystem;

class FileWrapperTest : public ::testing::Test
{
protected:
    std::string testFile = "test_output.txt";

    void TearDown() override
    {
        if (fs::exists(testFile))
            fs::remove(testFile);
    }
};

// ==================== BASIC TESTS ====================

TEST_F(FileWrapperTest, CanOpenAndCloseFile)
{
    FileWrapper file;
    EXPECT_TRUE(file.openFile(testFile));
    EXPECT_TRUE(file.isOpen());
    file.closeFile();
    EXPECT_FALSE(file.isOpen());
}

TEST_F(FileWrapperTest, WritesSingleValueCorrectly)
{
    FileWrapper file;
    file.openFile(testFile);

    file << 42;

    file.closeFile();

    std::ifstream in(testFile);
    std::string content((std::istreambuf_iterator<char>(in)),
                        std::istreambuf_iterator<char>());

    EXPECT_EQ(content, "42\n");
}

// ==================== MULTI-THREADED TESTS ====================

TEST_F(FileWrapperTest, ThreadSafeWriting)
{
    FileWrapper file;
    file.openFile(testFile);

    const int numThreads = 50;
    const int writesPerThread = 20;

    std::vector<std::thread> threads;

    for (int t = 0; t < numThreads; ++t)
    {
        threads.emplace_back([&, t]() {
            for (int i = 0; i < writesPerThread; ++i)
            {
                file << (t * 1000 + i);
            }
        });
    }

    for (auto& th : threads)
        th.join();

    file.closeFile();

    // Verify all values were written
    std::set<int> writtenValues;
    std::ifstream in(testFile);
    int value;

    while (in >> value)
    {
        writtenValues.insert(value);
    }

    EXPECT_EQ(writtenValues.size(), numThreads * writesPerThread);
}

// Add more tests: large data, concurrent open/close attempts, etc.