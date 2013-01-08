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
#include <vector>
#include <deque>



class Converter{
    typedef unsigned char Byte;
    Converter(){}

public:
    static std::vector<Byte> to_byte_array(std::vector<Byte> source_digits, int source_base, int destination_base)
    {
        return convertNumberExt(source_digits, source_base, destination_base);
    }


private:
    static double logTwo(double num)
    {
        return std::log10(num) / std::log10(2);
    }


    static void incNumberByValue(std::vector<Byte> digits, int base, int value)
    {
        // The initial overflow is the 'value' to add to the number.
        int overflow = value;

        // Traverse list of digits in reverse order.
        for(int i = digits.size()-1; i >= 0; --i){
            // If there is no overflow we can stop overflow propagation to next higher digit(s).
            if (not overflow){
                return ;
            }
            else{
                int sum = digits[i] + overflow;
                digits[i] = sum % base;
                overflow = sum / base;
            }
        }
    }


    static void multNumberByValue(std::vector<Byte> digits, int base, int value)
    {
        int overflow = 0;

        for(int i = digits.size()-1; i >= 0; --i){
            int tmp = (digits[i] * value) + overflow;
            digits[i] = tmp % base;
            overflow = tmp / base;
        }
    }



    static void convertNumber(std::vector<Byte> srcDigits, int srcBase, std::vector<Byte> destDigits, int destBase)
    {
        // For each srcDigit in srcDigits
        for(unsigned i =0; i != srcDigits.size(); ++i){
            multNumberByValue(destDigits, destBase, srcBase);
            incNumberByValue(destDigits, destBase, srcDigits[i]);
        }
    }


    static std::vector<Byte> convertNumberExt(std::vector<Byte> srcDigits, const int srcBase, const int destBase)
    {
        // # Generate a list of zero's which is long enough to hold the destination number.
        int sizeNeeded = std::ceil( srcDigits.size() * logTwo(srcBase) / logTwo(destBase) );
        std::vector<Byte> destDigits(sizeNeeded);

        convertNumber(srcDigits, srcBase, destDigits, destBase); // # Do conversion.

        return destDigits; //# Return result.
    }
};



class Tapx{
public:
    Tapx(const char* entree, int n_base =10);
    //..

private:
    Tapx();
    typedef unsigned char Digit;
    const static unsigned int BASE = (1L<<8);
    std::vector<Digit> data;
};



//-------------------------------------------------
using namespace std;

/*
def divmod_long(src, src_base, divisor):
    dividend=[]
    remainder=0
    for d in src:
      (e, remainder) = divmod(d + remainder * src_base, divisor)
      if dividend or e: dividend += [e]
    return (dividend, remainder)

def convert(src, src_base, dst_base):
    result = []
    while src:
      (src, remainder) = divmod_long(src, src_base, dst_base)
      result = [remainder] + result
    return result



// ============================================

import math

def incNumberByValue(digits, base, value):
	# The initial overflow is the 'value' to add to the number.
	overflow = value
	# Traverse list of digits in reverse order.
	for i in reversed(xrange(len(digits))):
      	# If there is no overflow we can stop overflow propagation to next higher digit(s).
		if not overflow:
			return
		sum = digits[i] + overflow
		digits[i] = sum % base
		overflow = sum / base


def multNumberByValue(digits, base, value):
	overflow = 0
	# Traverse list of digits in reverse order.
	for i in reversed(xrange(len(digits))):
		tmp = (digits[i] * value) + overflow
		digits[i] = tmp % base
		overflow = tmp / base


def convertNumber(srcDigits, srcBase, destDigits, destBase):
	for srcDigit in srcDigits:
		multNumberByValue(destDigits, destBase, srcBase)
		incNumberByValue(destDigits, destBase, srcDigit)


def convertNumberExt(srcDigits, srcBase, destBase):
	# Generate a list of zero's which is long enough to hold the destination number.
	destDigits = [0] * int(math.ceil(len(srcDigits)*math.log(srcBase,2)/math.log(destBase,2)))
	# Do conversion.
	convertNumber(srcDigits, srcBase, destDigits, destBase)
	# Return result.
	return destDigits

sourceNum = [2, 0]
destNum = convertNumberExt(sourceNum, 10, 16)

print "numero source %s" % sourceNum
print "numero dest %s" % destNum
*/


Tapx::Tapx(const char* entree, int src_base /*=10*/) :
    data(std::strlen(entree) * log2(src_base)/8)  // find the number of digits needed

{
    const char* p = entree;
    vector<unsigned> src(strlen(p));
    for(unsigned i=0; i != src.size(); ++i){
        src[i] = (*p++) - '0';
    }
    vector<Digit> result;

    while (src.size()){

        // Functions
        //unsigned divisor = BASE;
        vector<unsigned> dividend;
        unsigned remainder = 0;
        /*
        for(unsigned d : src){
            unsigned e = (d + remainder * src_base) / divisor;
            unsigned remainder = (d + remainder * src_base) % divisor;
            if (dividend.size() || e) dividend.push_back(e);
        }
        */
        src = dividend;
        result.push_back(remainder);
    }


    cout << "good" << endl;
}



#endif // TAPX_H
