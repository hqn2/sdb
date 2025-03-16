#include <gtest/gtest.h>
#include <string>

#include "../src/buffer.h"

using namespace std;

class BufferTestSuite : public ::testing::Test {
};

TEST_F(BufferTestSuite, CreateAndUseBuffer)
{
    Buffer buffer(10);
    memmove(buffer.get(), "123456789", 10);

    string a { buffer.get() };
    string b { "123456789" };
    EXPECT_EQ(a, b);
}

TEST_F(BufferTestSuite, CreateAndUseBufferSync)
{
    Buffer buffer(10);
    memmove(buffer.get(), "123456789\n", 10);

    BufferSync sync("btest");
    auto ok = sync.set(buffer);
    EXPECT_EQ(ok, true);

    auto buf2 = sync.get();
    EXPECT_EQ(buffer.size(), buf2.size());

    auto cmp = memcmp(buffer.get(), buf2.get(), buffer.size());
    EXPECT_EQ(cmp, 0);
}
