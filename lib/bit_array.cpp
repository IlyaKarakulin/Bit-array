#include "bit_array.hpp"

int BitArray::count() const
{
    int count = 0;

    for (int i = 0; i < this->size(); ++i)
        count += (*this)[i];

    return count;
}

bool BitArray::empty() const
{
    if (this->bit_arr.capacity() == 0)
        return true;
    else
        return false;
}

bool BitArray::any() const
{
    bool flag = false;

    for (int i = 0; (i < this->size()) && !flag; ++i)
    {
        if ((*this)[i])
            flag = true;
    }

    return flag;
}

bool BitArray::none() const
{
    return !(this->any());
}

BitArray &BitArray::reset(int index)
{
    this->set(index, false);
    return *this;
}

BitArray &BitArray::reset()
{
    for (ulong &x : this->bit_arr)
    {
        x = 0;
    }
    return *this;
}

BitArray::~BitArray()
{
    this->bit_arr.clear();
}

int BitArray::size() const
{
    return count_bit;
}

int BitArray::count_unit(int n) const
{
    return ceil((double)n / this->dim);
}

BitArray::BitArray(const BitArray &b)
{
    this->bit_arr.reserve(b.count_unit(b.count_bit));
    this->count_bit = b.count_bit;

    for (int i = 0; i < b.count_unit(b.count_bit); ++i)
    {
        this->bit_arr.insert(this->bit_arr.begin() + i, b.bit_arr.at(i));
    }
}

BitArray::BitArray(int num_bits, ulong value)
{

    ulong mask = UL_MAX;
    int len_value = 0;

    // counting the number of significant bits
    while (mask & value)
    {
        ++len_value;
        mask <<= 1;
    }

    // if there are more significant bits than num_bits, then I raise an exception
    if (len_value > num_bits)
    {
        throw std::range_error("Error: length input value > length bit array\n");
    }
    else
    {
        if (num_bits <= 64)
            value <<= dim - num_bits;

        this->count_bit = num_bits;
        int len_vector{(int)ceil((double)this->count_bit / dim)};

        bit_arr.reserve(len_vector);
        bit_arr.insert(bit_arr.begin(), value);

        for (int i = 1; i < len_vector; ++i)
        {
            bit_arr.push_back(0x0);
        }
    }
}

void BitArray::resize(int num_bits, bool value)
{
    int new_len{this->count_unit(num_bits)};
    int old_count_bit = this->count_bit;
    this->count_bit = num_bits;
    this->bit_arr.resize(new_len, value ? UL_MAX : 0);

    if (old_count_bit < num_bits)
    {
        for (int i = old_count_bit; (i % this->dim != 0) && (i < num_bits); ++i)
        {
            this->set(i, value);
        }
    }
    else
    {
        this->bit_arr.shrink_to_fit();
    }
}

void BitArray::swap(BitArray &b)
{
    b.bit_arr.swap(this->bit_arr);
    std::swap(this->count_bit, b.count_bit);
}

void BitArray::clear()
{
    this->bit_arr.clear();
    this->count_bit = 0;
}

void BitArray::push_back(bool bit)
{
    if (this->count_bit >= (this->bit_arr.size() * this->dim))
    {
        this->bit_arr.resize(bit_arr.size() + 1, bit ? UL_MAX : 0);
    }

    set(this->count_bit++, bit);
}

std::string BitArray::to_string() const
{
    int str_len = this->size() + this->size() / 8;
    std::string bit_str(str_len, '0');
    int count_space = 0;

    for (int i = 0; i < str_len; ++i)
    {
        if ((i + 1) % 9 == 0)
        {
            bit_str[i] = ' ';
            ++count_space;
        }
        else
        {
            if ((*this)[i - count_space])
                bit_str[i] = '1';
        }
    }

    return bit_str;
}

BitArray &BitArray::set(int index, bool value)
{
    if (index >= this->count_bit)
    {
        throw std::range_error("Error: index out of range\n");
    }
    {
        ulong mask = 1UL << ((this->dim - 1) - (index % this->dim));
        int num_unit{index / this->dim};

        if (((bit_arr.at(num_unit) & mask) && 1) != (value && 1))
            bit_arr.at(num_unit) = bit_arr.at(num_unit) ^ mask;

        return *this;
    }
}