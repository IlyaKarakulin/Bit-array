#include <gtest/gtest.h>
#include "../lib/bit_array.hpp"

BitArray a(65, UL_MAX);

TEST(ConTest, constructor)
{
    BitArray a(65, UL_MAX);

    EXPECT_EQ(a.size(), 65);
    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[63], 1);
    EXPECT_EQ(a[64], 0);

    BitArray b(a);

    EXPECT_EQ(b.size(), 65);
    EXPECT_EQ(b[0], 1);
    EXPECT_EQ(b[63], 1);
    EXPECT_EQ(b[64], 0);
}

TEST(ConTest, bit_operation)
{
    BitArray a(5, 0b10101);
    BitArray a(5, 0b10101);
}