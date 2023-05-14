#ifndef BFLOAT_H
#define BFLOAT_H

#include <bitset>
#include <iostream>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <string>
#include <cfenv>
#include <climits>
#include <chrono>
#include <map>

class Bitset_Float
{
    std::bitset<32> bfloat_num;

public:
    Bitset_Float(std::bitset<32> bfloat = 0);

    Bitset_Float(int num);

    Bitset_Float(float num);

    Bitset_Float(double num);

    Bitset_Float *Clone()
    {
        return new Bitset_Float(*this);
    }
    bool is_zero() const;
    static unsigned long pow_of_two(int n);
    float to_float() const;

    friend std::ostream &operator<<(std::ostream &os, const Bitset_Float &num);
    friend std::istream &operator>>(std::istream &is, Bitset_Float &num);

    std::bitset<8> get_exponent_bits() const;
    std::bitset<23> get_fractional_bits() const;

    unsigned get_sign_bit() const;
    uint32_t get_fractional() const;
    int32_t get_exponent() const;

    uint32_t get_fractional_size() const;
    uint32_t get_exponent_size() const;

    void get_result(uint32_t frac, int32_t exp, uint32_t sign, uint32_t nbits, uint32_t esbits);
    
};

#endif /* BFLOAT_H */
