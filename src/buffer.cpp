#include "buffer.h"

#include <fcntl.h>
#include <iostream>
#include <unistd.h>

BufferSync::BufferSync(const char* path)
    : _fd(::open(path, O_RDWR | O_CREAT, 0644))
{
}

BufferSync::~BufferSync()
{
    if (_fd != -1)
        close(_fd);
}

Buffer BufferSync::get()
{
    if (_fd != -1) {
        auto len = lseek(_fd, 0, SEEK_END);
        if (len > 0) {
            Buffer buffer(len);
            if (pread(_fd, buffer.get(), len, 0) == len)
                return buffer;
        }
    }
    return Buffer(0);
}

bool BufferSync::set(Buffer& buffer)
{
    if (_fd == -1 || !buffer.size())
        return false;

    ftruncate(_fd, 0);

    if (pwrite(_fd, buffer.get(), buffer.size(), 0) != buffer.size())
        return false;

    fsync(_fd);

    return true;
}
