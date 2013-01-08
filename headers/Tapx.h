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


class Convert{
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

            for(unsigned digit : source_digits){
                unsigned e = (digit + remainder_divmod_long * source_base) / divisor;
                remainder_divmod_long = (digit + remainder_divmod_long * source_base) % divisor;
                if (dividend.size() || e) dividend.push_back(e);
            }

            source_digits = dividend;
            result.push_back(remainder_divmod_long);
        }
    }
};



class Tapx{
    typedef unsigned char Byte;
    const static unsigned int BASE = (1L<<8);
    std::vector<Byte> data;

public:
    //Tapx(const char* entree);
    Tapx(const char* entree, int n_base=10);
    std::string to_s(int base=10) const;

private:
    Tapx();
    void normalize();

};

/*
Tapx::Tapx(const char* source_string)
{
    this->data = Tapx(source_string, 10).data;
}*/

Tapx::Tapx(const char* source_string, int src_base) :
    data(std::strlen(source_string) * std::log2(src_base)/8)
{
    std::vector<Byte> src_digits(std::strlen(source_string));
    for(unsigned i=0; i != src_digits.size(); ++i){
        src_digits[i] = source_string[i] - '0';
    }

    Convert::to_base_destination(src_digits, this->data, src_base, this->BASE);

    this->normalize();
}


void Tapx::normalize()
{
    size_t i = 0;

    while( this->data[i] == 0 ) {
        ++i;
    }

    // if zeroes were found ahead number
    if(i > 0){
        this->data = std::vector<Byte>(this->data.begin()+i, this->data.end());
    }
    else{
        return ;
    }
}



#endif // TAPX_H
