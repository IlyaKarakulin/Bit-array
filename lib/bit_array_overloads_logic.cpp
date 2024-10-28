#include "bit_array.hpp"

bool operator==(const BitArray &a, const BitArray &b)
{
    if (a.size() == b.size())
    {
        bool flag = true;

        for (int i = 0; i < a.size() && flag; ++i)
        {
            if (a[i] != b[i])
                flag = false;
        }
        return flag;
    }
    else
    {
        throw diff_length_of_bit_arr();
    }
}

bool operator!=(const BitArray &a, const BitArray &b)
{
    bool flag = !(a == b);
    return flag;
}

BitArray operator&(const BitArray &b1, const BitArray &b2)
{
    if (b1.size() == b2.size())
    {
        BitArray res(b1);

        for (int i = 0; i < res.size(); ++i)
        {
            res.set(i, res[i] && b2[i]);
        }

        return res;
    }
    else
    {
        throw diff_length_of_bit_arr();
    }
}

BitArray operator|(const BitArray &b1, const BitArray &b2)
{
    if (b1.size() == b2.size())
    {
        BitArray res(b1);

        for (int i = 0; i < res.size(); ++i)
        {
            res.set(i, res[i] || b2[i]);
        }

        return res;
    }
    else
    {
        throw diff_length_of_bit_arr();
    }
}

BitArray operator^(const BitArray &b1, const BitArray &b2)
{
    if (b1.size() == b2.size())
    {
        BitArray res(b1);

        for (int i = 0; i < res.size(); ++i)
        {
            res.set(i, res[i] != b2[i]);
        }

        return res;
    }
    else
    {
        throw diff_length_of_bit_arr();
    }
}

BitArray BitArray::operator~() const
{
    BitArray b(*this);
    int i = 0;

    for (auto x : this->bit_arr)
    {
        b.bit_arr[i] = ~x;
        ++i;
    }
    return b;
}

BitArray &BitArray::operator=(const BitArray &b)
{
    this->count_bit = b.count_bit;
    std::copy(b.bit_arr.begin(), b.bit_arr.end(), this->bit_arr.begin());

    return *this;
}

BitArray &BitArray::operator&=(const BitArray &b)
{
    if (this->count_bit == b.count_bit)
    {
        for (int i = 0; i < this->bit_arr.size(); ++i)
        {
            this->bit_arr[i] &= b.bit_arr[i];
        }
        return *this;
    }
    else
    {
        throw diff_length_of_bit_arr();
    }
}

BitArray &BitArray::operator|=(const BitArray &b)
{
    if (this->count_bit == b.count_bit)
    {
        for (int i = 0; i < this->bit_arr.size(); ++i)
            this->bit_arr[i] |= b.bit_arr[i];

        return *this;
    }
    else
    {
        throw diff_length_of_bit_arr();
    }
}

BitArray &BitArray::operator^=(const BitArray &b)
{
    if (this->count_bit == b.count_bit)
    {
        for (int i = 0; i < this->bit_arr.size(); ++i)
        {
            this->bit_arr[i] ^= b.bit_arr[i];
        }
        return *this;
    }
    else
    {
        throw diff_length_of_bit_arr();
    }
}

BitArray &BitArray::operator>>=(int n)
{
    if (n > this->count_bit)
    {
        n = this->count_bit;
    }

    for (int i = this->size() - 1; i >= n; --i)
        this->set(i, (*this)[i - n]);

    for (int i = 0; i < n; ++i)
        this->reset(i);

    return *this;
}

BitArray &BitArray::operator<<=(int n)
{
    if (n > this->count_bit)
    {
        n = this->count_bit;
    }

    for (int i = 0; i < this->size() - n; ++i)
        this->set(i, (*this)[i + n]);

    for (int i = this->size() - 1; i > this->size() - 1 - n; --i)
        this->set(i, 0);

    return *this;
}

BitArray BitArray::operator>>(int n) const
{
    if (n > this->count_bit)
    {
        n = this->count_bit;
    }

    BitArray b(*this);

    for (int i = this->size() - 1; i >= n; --i)
        b.set(i, (*this)[i - n]);

    for (int i = 0; i < n; ++i)
        b.set(i, 0);

    return b;
}

BitArray BitArray::operator<<(int n) const
{
    if (n > this->count_bit)
    {
        n = this->count_bit;
    }

    BitArray b(*this);

    for (int i = 0; i < this->size() - n; ++i)
        b.set(i, (*this)[i + n]);

    for (int i = this->size() - 1; i > this->size() - 1 - n; --i)
        b.set(i, 0);

    return b;
}

bool BitArray::operator[](int i) const
{
    if (i >= this->count_bit)
    {
        throw std::range_error("Error: index out of range\n");
    }
    else
    {
        ulong res = bit_arr[i / dim] & (1UL << (63 - i));
        return res == 0 ? false : true;
    }
}
