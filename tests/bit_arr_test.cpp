#include <gtest/gtest.h>
#include "../lib/bit_array.hpp"

BitArray a(65, UL_MAX);
BitArray b(a);
BitArray d(5, 0b10101);
BitArray c(10, 0b1100110101);

TEST(ConTest, constructor)
{
    EXPECT_EQ(a.size(), 65);
    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[63], 1);
    EXPECT_EQ(a[64], 0);

    EXPECT_EQ(b.size(), 65);
    EXPECT_EQ(b[0], 1);
    EXPECT_EQ(b[63], 1);
    EXPECT_EQ(b[64], 0);

    EXPECT_EQ(d.size(), 5);
    EXPECT_EQ(d[0], 1);
    EXPECT_EQ(d[1], 0);
    EXPECT_EQ(d[2], 1);
}

TEST(ConTest, metods)
{
    a.swap(d);
    EXPECT_EQ(d.size(), 65);
    EXPECT_EQ(d[0], 1);
    EXPECT_EQ(d[63], 1);
    EXPECT_EQ(d[64], 0);

    EXPECT_EQ(a.size(), 5);
    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[1], 0);
    EXPECT_EQ(a[2], 1);

    a.resize(7, true);
    EXPECT_EQ(a[5], 1);
    EXPECT_EQ(a[6], 1);

    a.clear();
    EXPECT_EQ(a.empty(), 0);

    d.push_back(1);
    EXPECT_EQ(d.size(), 66);
    EXPECT_EQ(d[65], 1);

    d.set(65, 0);
    EXPECT_EQ(d[65], 0);

    EXPECT_EQ(d[23], 1);
    d.reset(23);
    EXPECT_EQ(d[23], 0);

    d.reset();

    EXPECT_EQ(d.none(), 1);
    EXPECT_EQ(d.any(), 0);

    d.set(65, 1);
    EXPECT_EQ(d.none(), 0);
    EXPECT_EQ(d.any(), 1);

    EXPECT_EQ(c.to_string(), "11001101 01");
}

BitArray a1(5, 0b10101);
BitArray b1(5, 0b01011);

TEST(ConTest, operators)
{
    EXPECT_EQ((a1 & b1).to_string(), "00001");
    EXPECT_EQ((a1 | b1).to_string(), "11111");
    EXPECT_EQ((a1 ^ b1).to_string(), "11110");

    a1 >>= 2;
    b1 <<= 2;
    EXPECT_EQ(a1.to_string(), "00101");
    EXPECT_EQ(b1.to_string(), "01100");

    EXPECT_EQ((a1 >> 1).to_string(), "00010");
    EXPECT_EQ((b1 << 1).to_string(), "11000");

    b1 = ~b1;
    EXPECT_EQ(b1.to_string(), "10011");
}