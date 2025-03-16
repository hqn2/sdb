#ifndef BUFFER_H
#define BUFFER_H

#include <cstdint>

///////////////////////////////

struct Buffer {
    Buffer(uint32_t size)
    {
        if (!size)
            return;
        _buffer = new char[size];
        _size = size;
    }

    ~Buffer()
    {
        delete[] _buffer;
        _buffer = nullptr;
        _size = 0;
    }

    char* get() { return _buffer; }
    uint32_t size() { return _size; }

private:
    char* _buffer = nullptr;
    uint32_t _size = 0;
};

///////////////////////////////

struct BufferSync {
    BufferSync(const char* path);
    ~BufferSync();

    Buffer get();
    bool set(Buffer& buffer);

private:
    int _fd = -1;
};

#endif // BUFFER_H