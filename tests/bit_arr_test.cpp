#include <gtest/gtest.h>
#include "../lib/bit_array.hpp"

TEST(ConTest, constructor)
{
    BitArray a(65, UL_MAX);
    BitArray b(a);
    BitArray d(5, 0b10101);

    EXPECT_EQ(a.size(), 65);
    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[63], 1);
    EXPECT_EQ(a[64], 0);

    try
    {
        EXPECT_EQ(a[65], 0);
    }
    catch (const std::range_error &e)
    {
        std::cerr << e.what();
    }

    EXPECT_EQ(b.size(), 65);
    EXPECT_EQ(b[0], 1);
    EXPECT_EQ(b[63], 1);
    EXPECT_EQ(b[64], 0);

    EXPECT_EQ(d.size(), 5);
    EXPECT_EQ(d[0], 1);
    EXPECT_EQ(d[1], 0);
    EXPECT_EQ(d[2], 1);
}

TEST(ConTest, throw_constructor)
{
    try
    {
        BitArray c(10, 0b1100110101111);
        EXPECT_EQ(c.size(), 10);
        EXPECT_EQ(c[0], 1);
        EXPECT_EQ(c[1], 1);
        EXPECT_EQ(c[8], 0);
        EXPECT_EQ(c[9], 1);
    }
    catch (const std::range_error &e)
    {
        std::cerr << e.what();
    }
}

TEST(ConTest, metods)
{
    BitArray a(65, UL_MAX);
    BitArray d(5, 0b10101);

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
    a.clear();
    EXPECT_EQ(a.empty(), 0);

    d.push_back(1);
    EXPECT_EQ(d.size(), 66);
    EXPECT_EQ(d[65], 1);

    d.set(65, 0);
    EXPECT_EQ(d[65], 0);

    try
    {
        d.set(66, 0);
        EXPECT_EQ(d[66], 0);
    }
    catch (const std::range_error &e)
    {
        std::cerr << e.what();
    }

    EXPECT_EQ(d[23], 1);
    d.reset(23);
    EXPECT_EQ(d[23], 0);

    d.reset();
    EXPECT_EQ(d.none(), 1);
    EXPECT_EQ(d.any(), 0);

    d.set(65, 1);
    EXPECT_EQ(d.none(), 0);
    EXPECT_EQ(d.any(), 1);
}

TEST(ConTest, operators)
{
    BitArray a(5, 0b10101);
    BitArray b(5, 0b01011);
    BitArray c(6, 0b011011);

    try
    {
        a & c;
    }
    catch (const diff_length_of_bit_arr &e)
    {
        std::cerr << e.what();
    }

    EXPECT_EQ((a & b).to_string(), "00001");
    EXPECT_EQ((a | b).to_string(), "11111");
    EXPECT_EQ((a ^ b).to_string(), "11110");

    a >>= 2;
    b <<= 2;
    EXPECT_EQ(a.to_string(), "00101");
    EXPECT_EQ(b.to_string(), "01100");
    EXPECT_EQ((a >> 1).to_string(), "00010");
    EXPECT_EQ((b << 1).to_string(), "11000");

    b = ~b;
    EXPECT_EQ(b.to_string(), "10011");

    a >>= 20;
    EXPECT_EQ(a.to_string(), "00000");
}