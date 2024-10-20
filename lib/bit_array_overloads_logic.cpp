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
        return false;
    }
}

bool operator!=(const BitArray &a, const BitArray &b)
{
    bool flag = !(a == b);
    return flag;
}

BitArray operator&(const BitArray &b1, const BitArray &b2)
{
    BitArray res(b1);

    for (int i = 0; i < res.size(); ++i)
    {
        res.set(i, res[i] && b2[i]);
    }

    return res;
}

BitArray operator|(const BitArray &b1, const BitArray &b2)
{
    BitArray res(b1);

    for (int i = 0; i < res.size(); ++i)
    {
        res.set(i, res[i] || b2[i]);
    }

    return res;
}

BitArray operator^(const BitArray &b1, const BitArray &b2)
{
    BitArray res(b1);

    for (int i = 0; i < res.size(); ++i)
    {
        res.set(i, res[i] != b2[i]);
    }

    return res;
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
    }
    else
    {
        perror("The length of the arrays is different\n");
    }

    return *this;
}

BitArray &BitArray::operator|=(const BitArray &b)
{
    if (this->count_bit == b.count_bit)
    {
        for (int i = 0; i < this->bit_arr.size(); ++i)
            this->bit_arr[i] |= b.bit_arr[i];
    }
    else
    {
        perror("The length of the arrays is different\n");
    }

    return *this;
}

BitArray &BitArray::operator^=(const BitArray &b)
{
    if (this->count_bit == b.count_bit)
    {
        for (int i = 0; i < this->bit_arr.size(); ++i)
        {
            this->bit_arr[i] ^= b.bit_arr[i];
        }
    }
    else
    {
        perror("The length of the arrays is different\n");
    }

    return *this;
}

BitArray &BitArray::operator>>=(int n)
{
    for (int i = this->size() - 1; i >= n; --i)
        this->set(i, (*this)[i - n]);

    for (int i = 0; i < n; ++i)
        this->set(i, 0);

    return *this;
}

BitArray &BitArray::operator<<=(int n)
{
    for (int i = 0; i < this->size() - n; ++i)
        this->set(i, (*this)[i + n]);

    for (int i = this->size() - 1; i > this->size() - 1 - n; --i)
        this->set(i, 0);

    return *this;
}

BitArray BitArray::operator>>(int n) const
{
    BitArray b(*this);

    for (int i = this->size() - 1; i >= n; --i)
        b.set(i, (*this)[i - n]);

    for (int i = 0; i < n; ++i)
        b.set(i, 0);

    return b;
}

BitArray BitArray::operator<<(int n) const
{
    BitArray b(*this);

    for (int i = 0; i < this->size() - n; ++i)
        b.set(i, (*this)[i + n]);

    for (int i = this->size() - 1; i > this->size() - 1 - n; --i)
        b.set(i, 0);

    return b;
}

bool BitArray::operator[](int i) const
{
    try
    {
        ulong res = bit_arr.at(i / dim) & (1UL << (63 - i));
        return res == 0 ? false : true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Caught: " << e.what() << std::endl;
        std::cerr << "Type: " << typeid(e).name() << std::endl;
        return false;
    }
}
