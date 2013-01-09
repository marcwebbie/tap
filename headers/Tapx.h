/*
This file is part of Tap.

    Tap is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Tap is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Tap.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TAPX_H
#define TAPX_H

#include <cmath>
#include <cstring>
#include <vector>
#include <deque>
#include <string>


// Converter Class
// ===============================================>

class Converter{
    typedef unsigned char Byte;
public:
    static void to_base_destination(std::vector<Byte> source_digits,
                                    std::vector<Byte>& destination_digits,
                                    const int& source_base,
                                    const int& destination_base)
    {
        std::vector<Byte>& result = destination_digits;
        result.clear(); // make sure that the destination is empty
        unsigned divisor = destination_base;

        // Convert from src base to dest_base
        while (source_digits.size()){
            // division and modulo
            std::vector<Byte> dividend;

            unsigned remainder_divmod_long = 0;

            for(unsigned digit : source_digits) {
                unsigned e = (digit + remainder_divmod_long * source_base) / divisor;
                remainder_divmod_long = (digit + remainder_divmod_long * source_base) % divisor;
                if (dividend.size() || e) dividend.push_back(e);
            }

            source_digits = dividend;
            result.push_back(remainder_divmod_long);
        }
    }

    static std::string to_string_base(std::vector<Byte> source_digits,
                                      std::vector<Byte> destination_vector,
                                      const int& source_base,
                                      const int& base_for_string)
    {
        Converter::to_base_destination(source_digits, destination_vector, source_base, base_for_string);

        static const char* digit_table = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        std::string string_final = "";

        for (size_t i = 0; i < destination_vector.size(); ++i) {
            string_final = digit_table[destination_vector[i]] + string_final;
        }

        return string_final;
    }
};



// Tapx Class
// ===============================================>
class Tapx{
    typedef unsigned char Byte;
    const static unsigned int BASE = (1L<<8);

public:
    Tapx();
    Tapx(const char* entree, int n_base=10);
    std::string to_s(int base_to_print=10) const;
    size_t len() const;

private:
    void normalize();

    // Friend operators section
    friend Tapx operator+ (const Tapx& x, const Tapx& y);

    // Data section
    std::vector<Byte> data;
};



// Global Operators
// ===============================================>
Tapx operator+ (const Tapx& x, const Tapx& y)
{
    size_t x_size = x.len();
    Tapx result_tapx;
    result_tapx.data.resize(x_size);

    // Sum computing
    unsigned int carry = 0;
    for (size_t i = 0; i < x_size; ++i) {
        carry = (x.data[i] + y.data[i] + carry);
        result_tapx.data[i] = carry % Tapx::BASE;
        carry /= Tapx::BASE;
    }
    if(carry) {
        result_tapx.data.resize(x_size+1, carry);
    }

    return result_tapx;
}



Tapx::Tapx() :
    data(0)
{
    //this->data[0] = 0;
}



Tapx::Tapx(const char* source_string, int src_base) :
    data(std::strlen(source_string) * std::log2(src_base)/8)
{
    std::vector<Byte> src_digits(std::strlen(source_string));
    for (unsigned i=0; i != src_digits.size(); ++i) {
        src_digits[i] = source_string[i] - '0';
    }

    Converter::to_base_destination(src_digits, this->data, src_base, this->BASE);

    this->normalize();
}



// Return a string representation of the instance in the chosen base
std::string Tapx::to_s(int base_to_print) const
{
    std::vector<Byte> string_vector;
    return Converter::to_string_base(this->data, string_vector, this->BASE, base_to_print);

    /*
    Converter::to_base_destination(this->data, string_vector, this->BASE, base_to_print);

    static const char* digit_table = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string string_final = "";

    for (size_t i = 0; i < string_vector.size(); ++i) {
        string_final = digit_table[string_vector[i]] + string_final;
    }

    return string_final;
    */
}



inline size_t Tapx::len() const
{
    return this->data.size();
}



void Tapx::normalize()
{
    size_t i = 0;

    while( this->data[i] == 0 ) {
        ++i;
    }

    // if zeroes were found ahead number
    if (i > 0) {
        this->data = std::vector<Byte>(this->data.begin()+i, this->data.end());
    }
    else {
        return ;
    }
}



#endif // TAPX_H
