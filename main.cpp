#include <fstream>
#include <cerrno>
#include <stdexcept>
#include <cstring>
#include <vector>
#include <stdint.h>
#include <iostream>

int main()
{
    // Which disk?
    char diskName[] = "/dev/sdb";
    std::string diskError = std::string() + diskName + ": ";

    // Open device file
    std::ifstream disk(diskName, std::ios_base::binary);

    if(!disk)
    throw(std::runtime_error(diskError + std::strerror(errno)));

    //85142960
    uint64_t sector = 85141960;
    // Seek to 54321'th sector

    std::vector<char> buffer(512);
    while(disk) {
    disk.seekg(512 * sector);
        if(!disk) {
            throw(std::runtime_error(diskError + std::strerror(errno)));
        }
        disk.read(&buffer[0], 512);
        if(!disk) {
            throw(std::runtime_error(diskError + std::strerror(errno)));
        }
        std::cout << "Reading sector " << sector << "\r" << std::flush;
        ++sector;
    }
}
