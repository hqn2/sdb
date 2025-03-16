#include "freespace.h"
#include <assert.h>

void FreeSpace::push(Buffer& buffer)
{
    _spaces.clear();

    uint32_t* buf = (uint32_t*)buffer.get();
    uint32_t sz = buffer.size() / sizeof(uint32_t);

    for (auto p = buf, end = buf + sz; p < end; p += 2) {
        auto it = _spaces.find(*p);
        if (it == _spaces.end()) {
            _spaces.insert({ *p, { *(p + 1) } });
        } else {
            it->second.push_back(*(p + 1));
        }
    }
}

Buffer FreeSpace::pop()
{
    uint32_t count = 0;
    for (auto& kv : _spaces)
        count += kv.second.size();
    count *= 2 * sizeof(uint32_t);

    Buffer buf(count);

    uint32_t* p = (uint32_t*)buf.get();
    for (auto& s : _spaces) {
        for (auto& i : s.second) {
            *(p++) = s.first;
            *(p++) = i;
        }
    }

    return buf;
}

Sector FreeSpace::get(uint32_t size)
{
    auto it = _spaces.lower_bound(size);
    if (it == _spaces.end())
        return { 0, 0 };

    auto sz = it->first;
    auto& v = it->second;
    assert(!v.empty());
    auto of = v.back();

    if (v.size() > 1) {
        v.pop_back();
    } else {
        _spaces.erase(it);
    }

    return { of, sz };
}

void FreeSpace::set(const Sector& sector)
{
    auto it = _spaces.find(sector.size);
    if (it == _spaces.end()) {
        _spaces.insert({ sector.size, { sector.offset } });
    } else {
        it->second.push_back(sector.offset);
    }
}