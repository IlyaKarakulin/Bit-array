#include <string>
#include <vector>
#include <iterator>
#include <cmath>
#include <limits>
#include <exception>
#include <stdexcept>
#include <iostream>

#define UL_MAX 0xffffffffffffffff
typedef unsigned long ulong;

class BitArray
{
private:
    std::vector<ulong> bit_arr;
    int count_bit;
    int dim = sizeof(ulong) * 8;

    int count_unit(int n) const;

public:
    BitArray();
    ~BitArray();

    explicit BitArray(int num_bits, ulong value = 0);
    BitArray(const BitArray &b);

    BitArray &operator=(const BitArray &b);
    BitArray &operator&=(const BitArray &b);
    BitArray &operator|=(const BitArray &b);
    BitArray &operator^=(const BitArray &b);

    BitArray &operator<<=(int n);
    BitArray &operator>>=(int n);
    BitArray operator<<(int n) const;
    BitArray operator>>(int n) const;
    BitArray operator~() const;
    bool operator[](int i) const;

    BitArray &set(int n, bool val = true);
    BitArray &reset(int n);
    BitArray &reset();

    void swap(BitArray &b);
    void resize(int num_bits, bool value = false);
    void clear();
    void push_back(bool bit);

    bool any() const;
    bool none() const;
    int count() const;
    int size() const;
    bool empty() const;

    std::string to_string() const;
};

bool operator==(const BitArray &a, const BitArray &b);
bool operator!=(const BitArray &a, const BitArray &b);

BitArray operator&(const BitArray &b1, const BitArray &b2);
BitArray operator|(const BitArray &b1, const BitArray &b2);
BitArray operator^(const BitArray &b1, const BitArray &b2);