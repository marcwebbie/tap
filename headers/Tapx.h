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



class Tapx{
public:
    Tapx(const char* entree);
    explicit Tapx(const char* entree, int n_base);
    //..

private:
    Tapx();
    typedef unsigned char Byte;
    const static unsigned int BASE = (1L<<8);
    std::vector<Byte> data;
};


Tapx::Tapx(const char* source_string)
{
    this->data = Tapx(source_string, 10).data;
}

Tapx::Tapx(const char* source_string, int src_base)
    //data(std::ceil(std::strlen(source_string) * (std::log10(src_base) / std::log10(2)) / (std::log10(this->BASE) / std::log10(2))) )// find the number of digits needed
{
    size_t source_string_size = std::strlen(source_string);
    data.resize(source_string_size * std::log2(src_base)/8);

    const char* p_source_string = source_string;
    std::vector<Byte> src_digits(source_string_size);
    for(unsigned i=0; i != src_digits.size(); ++i){
        src_digits[i] = (*p_source_string++) - '0';
    }

    std::vector<Byte>& result = this->data;
    unsigned divisor = this->BASE;

    // Convert from src base to dest_base
    while (src_digits.size()){

        // division and modulo
        std::vector<Byte> dividend;

        unsigned remainder_divmod_long = 0;

        for(unsigned digit : src_digits){
            unsigned e = (digit + remainder_divmod_long * src_base) / divisor;
            remainder_divmod_long = (digit + remainder_divmod_long * src_base) % divisor;
            if (dividend.size() || e) dividend.push_back(e);
        }

        src_digits = dividend;
        result.push_back(remainder_divmod_long);
    }
}



#endif // TAPX_H
