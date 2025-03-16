#include <gtest/gtest.h>
#include <string>

#include "../src/freespace.h"

using namespace std;

class FreeSpaceSuite : public ::testing::Test {
};

TEST_F(FreeSpaceSuite, PushAndPop)
{
    FreeSpace fs;

    Buffer buffer(sizeof(uint32_t) * 10);

    uint32_t data[10] = { 1, 10, 2, 20, 3, 20, 4, 40, 5, 50 };

    memmove(buffer.get(), data, sizeof(data));

    fs.push(buffer);

    auto buf2 = fs.pop();

    EXPECT_EQ(buffer.size(), buf2.size());

    auto cmp = memcmp(buffer.get(), buf2.get(), buffer.size());
    EXPECT_EQ(cmp, 0);
}

TEST_F(FreeSpaceSuite, SetAndPop)
{
    FreeSpace fs;

    fs.set({ 1, 10 });
    fs.set({ 2, 20 });
    fs.set({ 3, 20 });
    fs.set({ 4, 40 });
    fs.set({ 5, 50 });

    auto buf = fs.pop();

    uint32_t data[10] = { 10, 1, 20, 2, 20, 3, 40, 4, 50, 5 };

    EXPECT_EQ(buf.size(), sizeof(data));

    uint32_t* p = (uint32_t*)buf.get();

    for (uint32_t i = 0; i < 10; ++i, ++p) {
        EXPECT_EQ(*p, data[i]) << "Mismatch at index " << i;
    }
}

TEST_F(FreeSpaceSuite, GetAndPop)
{
    FreeSpace fs;

    fs.set({ 1, 10 });
    fs.set({ 2, 20 });
    fs.set({ 3, 20 });
    fs.set({ 4, 40 });
    fs.set({ 5, 50 });

    auto sec = fs.get(20);

    EXPECT_EQ(sec.offset == 2 || sec.offset == 3, true);
    EXPECT_EQ(sec.size, 20);

    uint32_t data[8] = { 10, 1, 20, 2, 40, 4, 50, 5 };

    data[3] = sec.offset == 2 ? 3 : 2;

    auto buf = fs.pop();

    EXPECT_EQ(buf.size(), sizeof(data));

    uint32_t* p = (uint32_t*)buf.get();

    for (uint32_t i = 0; i < 8; ++i, ++p) {
        EXPECT_EQ(*p, data[i]) << "Mismatch at index " << i;
    }
}

TEST_F(FreeSpaceSuite, GetAproximateValueAndPop)
{
    FreeSpace fs;

    fs.set({ 1, 10 });
    fs.set({ 2, 20 });
    fs.set({ 3, 20 });
    fs.set({ 4, 40 });
    fs.set({ 5, 50 });

    auto sec = fs.get(30);

    EXPECT_EQ(sec.offset, 4);
    EXPECT_EQ(sec.size, 40);

    uint32_t data[8] = { 10, 1, 20, 2, 20, 3, 50, 5 };

    auto buf = fs.pop();

    EXPECT_EQ(buf.size(), sizeof(data));

    uint32_t* p = (uint32_t*)buf.get();

    for (uint32_t i = 0; i < 8; ++i, ++p) {
        EXPECT_EQ(*p, data[i]) << "Mismatch at index " << i;
    }
}