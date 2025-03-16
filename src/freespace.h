#ifndef FREE_SPACE_H
#define FREE_SPACE_H

#include "buffer.h"
#include <map>
#include <vector>

struct Sector {
    uint32_t offset = 0;
    uint32_t size = 0;
};

struct FreeSpace {
    void push(Buffer& buffer);
    Buffer pop();

    Sector get(uint32_t size);
    void set(const Sector& sector);

private:
    std::map<uint32_t, std::vector<uint32_t>> _spaces; // free space into the file
};

#endif // FREE_SPACE_H