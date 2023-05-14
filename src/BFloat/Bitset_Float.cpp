#include "Bitset_Float.h"

Bitset_Float::Bitset_Float(std::bitset<32> bfloat /* 0 */) : bfloat_num(bfloat)
{
}

Bitset_Float::Bitset_Float(int num)
{
    float n = (float)num;
    std::bitset<sizeof(float) * 8> res(*reinterpret_cast<unsigned long *>(&n));
    bfloat_num = res;
}

Bitset_Float::Bitset_Float(float num)
{
    std::bitset<sizeof(float) * 8> res(*reinterpret_cast<unsigned long *>(&num));
    bfloat_num = res;
}

Bitset_Float::Bitset_Float(double num)
{
    float n = (float)num;
    std::bitset<sizeof(float) * 8> res(*reinterpret_cast<unsigned long *>(&n));
    bfloat_num = res;
}

bool Bitset_Float::is_zero() const
{
    return to_float() == 0;
}

unsigned long Bitset_Float::pow_of_two(int n)
{
    return 1UL << n;
}

unsigned Bitset_Float::get_sign_bit() const
{
    return bfloat_num[32 - 1];
}

float Bitset_Float::to_float() const
{
    unsigned int x = static_cast<unsigned int>(bfloat_num.to_ulong());
    float y = *(float *)&x;
    return y;
}

std::ostream &operator<<(std::ostream &os, const Bitset_Float &num)
{
    os << "Float representation: " << num.to_float() << ";\n Binary representation: " << num.get_sign_bit() << " " << num.get_exponent_bits() << " " << num.get_fractional_bits();
    return os;
}

std::istream &operator>>(std::istream &is, Bitset_Float &num)
{
    int choice;
    std::cout << "You wish to enter BFloat number as: " << std::endl;
    std::cout << "1: Binary; 2: Int; 3: Double; Anything else: Double" << std::endl;
    is >> choice;
    if (choice == 1)
    {
        std::cout << "Enter binary number:" << std::endl;
        std::bitset<32> input;
        if (is >> input)
        {
            num = Bitset_Float(input);
        }
    }
    else if (choice == 2)
    {
        int f;
        std::cout << "Enter int number:" << std::endl;
        is >> f;
        num = Bitset_Float(f);
        return is;
    }
    else if (choice == 3)
    {
        double d;
        std::cout << "Enter double number:" << std::endl;
        is >> d;
        num = Bitset_Float(d);
        return is;
    }
    else
    {
        double d;
        std::cout << "Enter double bfloat_num:" << std::endl;
        is >> d;
        num = Bitset_Float(d);
        return is;
    }
    return is;
}

std::bitset<8> Bitset_Float::get_exponent_bits() const
{
    std::bitset<8> exponent;

    for (size_t i = 0; i < 8; i++)
    {
        exponent[i] = this->bfloat_num[23 + i];
    }

    return exponent;
}

std::bitset<23> Bitset_Float::get_fractional_bits() const
{

    std::bitset<23> mantissa;

    for (size_t i = 0; i < 23; i++)
    {
        mantissa[i] = this->bfloat_num[i];
    }

    return mantissa;
}

uint32_t Bitset_Float::get_fractional() const
{
    std::bitset<23> mantissa;

    for (size_t i = 0; i < 23; i++)
    {
        mantissa[i] = this->bfloat_num[i];
    }

    return mantissa.to_ulong();
}

int32_t Bitset_Float::get_exponent() const
{
    std::bitset<8> exponent;

    for (size_t i = 0; i < 8; i++)
    {
        exponent[i] = this->bfloat_num[23 + i];
    }

    return exponent.to_ulong();
}

uint32_t Bitset_Float::get_fractional_size() const
{
    return 23;
}
uint32_t Bitset_Float::get_exponent_size() const
{
    return 8;
}

void Bitset_Float::get_result(uint32_t frac, int32_t exp, uint32_t sign, uint32_t nbits, uint32_t esbits)
{
    if (frac == 0 && exp == 0 && sign == 0)
    {
        bfloat_num = std::bitset<32>(0);
    }
    else
    {
        exp = exp - 127;
        bfloat_num = std::bitset<32>(std::to_string(sign) + std::bitset<8>(exp).to_string() + std::bitset<23>(frac).to_string());
    }
}
