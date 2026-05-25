#include "FileWrapper.h"
#include <thread>
#include <string.h>
#include <math.h>
#include <sstream>
#include <vector>

FileWrapper file;

void task(uint32_t index)
{
    file << index;
}

int main() {
    std::vector<std::thread> _threads;
    const std::string messageTemplate = "Working on file On Thread: ";

    file.openFile("./out.txt");
    for (uint32_t idx = 0U; idx < 1'000U; ++idx)
    {
        std::stringstream message;
        message << messageTemplate << idx;
        _threads.emplace_back(std::thread(task, idx));
    }

    for (auto& th : _threads)
    {
        th.join();
    }

    return 0;
}
