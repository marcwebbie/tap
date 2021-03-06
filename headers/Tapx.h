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
        while (source_digits.size()) {
            // division and modulo
            std::vector<Byte> dividend;

            unsigned remainder_divmod_long = 0;

            for (unsigned digit : source_digits) {
                unsigned e = (digit + remainder_divmod_long * source_base) / divisor;
                remainder_divmod_long = (digit + remainder_divmod_long * source_base) % divisor;
                if (dividend.size() || e) {
                    dividend.push_back(e);
                }
            }

            source_digits = dividend;
            result.push_back(remainder_divmod_long);
        }
    }

    static std::string to_string_base(std::vector<Byte> source_vector,
                                      std::vector<Byte> destination_vector,
                                      const int& source_base,
                                      const int& destination_base)
    {
        Converter::to_base_destination(source_vector, destination_vector, source_base, destination_base);

        static const char* digit_table = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        std::string string_final = "";

        for (size_t i = 0; i < destination_vector.size(); ++i) {
            string_final = digit_table[destination_vector[i]] + string_final;
        }

        return string_final;
    }
};


// Base converter using a template namespace
namespace Convert
{
    template<typename Digit_List>
    void incNumberByValue(Digit_List& digits, const int& base, const int& value)
    {
        // The initial overflow is the 'value' to add to the number.
        int overflow = value;
        int sum = 0;

        // Traverse list of digits in reverse order.
        for(size_t i=0; i < digits.size(); ++i) {
            //for(int i=digits.size()-1; i >= 0; --i) {
            // If there is no overflow we can stop overflow propagation to next higher digit(s).
            if (not overflow){
                return ;
            }
            else{
                sum = digits[i] + overflow;
                digits[i] = sum % base;
                overflow = sum / base;
            }
        }
    }

    template<typename Digit_List>
    static void multNumberByValue(Digit_List& digits, const int& base, const int& value)
    {
        int overflow = 0;
        int tmp = 0;

        // Traverse list of digits in reverse order
        for(size_t i=0; i < digits.size(); ++i) {
            //for(int i=digits.size()-1; i >= 0; --i) {
            tmp = (digits[i] * value) + overflow;
            digits[i] = tmp % base;
            overflow = tmp / base;
        }
    }

    template<typename Digit_List>
    void convertNumber(Digit_List& srcDigits, const int& srcBase, Digit_List& destDigits, const int& destBase)
    {
        for(int i=srcDigits.size()-1; i >= 0; --i) {
            //for (int srcDigit : srcDigits){
            multNumberByValue(destDigits, destBase, srcBase);
            incNumberByValue(destDigits, destBase, srcDigits[i]);
        }
    }

    template<typename Digit_List>
    void convertNumberExt(Digit_List& srcDigits, Digit_List& destDigits, const int& srcBase, const int& destBase)
    {
        // Generate a list of zero's which is long enough to hold the destination number.
        size_t destSize = int(ceil(srcDigits.size()*log2(srcBase)/log2(destBase)));
        if (destSize != destDigits.size()){
            destDigits.resize(destSize);
        }

        // Make sure that destDigits is empty
        destDigits.clear();

        // Do conversion.
        convertNumber(srcDigits, srcBase, destDigits, destBase);

        // Return result.
        //return destDigits;
    }
}


// Tapx Interface
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
    friend Tapx operator+ (const Tapx& x, const Tapx& y);
    friend Tapx operator* (const Tapx& x, const Tapx& y);

    // Data section
    std::vector<Byte> data;
};


// Tapx member functions implementation
// ===============================================>
Tapx::Tapx () : data(0)
{}

Tapx::Tapx (const char* source_string, int src_base) :
    data (std::strlen(source_string) * std::log2(src_base)/8)
{

    // Build a vector of bytes from a source string
    std::vector<Byte> src_digits(std::strlen(source_string));
    for (unsigned i=0; i != src_digits.size(); ++i) {
        src_digits[i] = source_string[i] - '0';
    }

    Convert::convertNumber(src_digits, src_base, this->data, BASE);
}



// Return a string representation of the instance in the chosen base
std::string Tapx::to_s (int base_to_print) const
{
    std::vector<Byte> source_vector = this->data;
    std::vector<Byte> result_vector;
    Convert::convertNumberExt(source_vector, result_vector, this->BASE, base_to_print);

    // build string from converted result vector
    // TODO: Too slow
    std::string dest_string = "";
    for (unsigned i=0; i != result_vector.size(); ++i) {
        dest_string += result_vector[i] - '0';
    }

    return dest_string;
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
    if (carry) {
        result_tapx.data.resize(x_size+1, carry);
    }

    return result_tapx;
}


Tapx operator* (const Tapx& x, const Tapx& y)
{
    unsigned x_size = x.len(), y_size = y.len();

    Tapx z;
    z.data.resize(x_size + y_size);

    unsigned carryout = 0;

    for (unsigned i = 0; i < x_size; i++) {

        unsigned carry = 0;
        unsigned j = 0;
        for (; j < y_size; j++) {
            carry += x.data[i]*y.data[j] + z.data[i+j];
            z.data[i+j] = carry%Tapx::BASE;
            carry /= myBASE;
        }

        for ( ; j < (x_size + y_size) - i; j++) {
            carry += z.data[i+j];
            z.data[i+j] = carry%Tapx::BASE;
            carry /= Tapx::BASE;
        }
        carryout |= carry;
    }
    if (carryout){
        z.data[z.len()] = 1;             // add the carry that spilled out
    }

    z.normalize();
    return z;
}



#endif // TAPX_H
