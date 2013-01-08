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

#include <iostream>
#include <cmath>
#include "headers/Tap.h"
#include "headers/Tapx.h"


/*
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


// ===========================

typedef unsigned char byte;


double logTwo(double num)
{
    return std::log10(num) / std::log10(2);
}


void incNumberByValue(std::vector<byte> digits, int base, int value)
{
    //# The initial overflow is the 'value' to add to the number.
    int overflow = value;
    //# Traverse list of digits in reverse order.
    for(int i = digits.size()-1; i >= 0; --i){
        //# If there is no overflow we can stop overflow propagation to next higher digit(s).
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


void multNumberByValue(std::vector<byte> digits, int base, int value)
{
    int overflow = 0;

    /* # Traverse list of digits in reverse order.
    for i in reversed(xrange(len(digits))):
        tmp = (digits[i] * value) + overflow
        digits[i] = tmp % base
        overflow = tmp / base
    */
    for(int i = digits.size()-1; i >= 0; --i){
        int tmp = (digits[i] * value) + overflow;
        digits[i] = tmp % base;
        overflow = tmp / base;
    }
}



void convertNumber(std::vector<byte> srcDigits, int srcBase, std::vector<byte> destDigits, int destBase)
{
    // for each srcDigit in srcDigits
    for(unsigned i =0; i != srcDigits.size(); ++i){
        // multNumberByValue(destDigits, destBase, srcBase)
        // incNumberByValue(destDigits, destBase, srcDigit)
        multNumberByValue(destDigits, destBase, srcBase);
        incNumberByValue(destDigits, destBase, srcDigits[i]);
    }
}






std::vector<byte> convertNumberExt(std::vector<byte> srcDigits, const int srcBase, const int destBase)
{
    // # Generate a list of zero's which is long enough to hold the destination number.
    // destDigits = [0] * int(math.ceil(len(srcDigits)*math.log(srcBase,2)/math.log(destBase,2)))
    int sizeNeeded = std::ceil( srcDigits.size() * logTwo(srcBase) / logTwo(destBase) );
    std::vector<byte> destDigits(sizeNeeded);

    convertNumber(srcDigits, srcBase, destDigits, destBase); // # Do conversion.

    return destDigits; //# Return result.
}
// ============================


using namespace std;
using mjr::Tap;

int main()
{
    Tap a = "8684864688468";
    Tap b = "6465535646564654465454546554655654654546545465564654484615164646553564656";
    Tap c = a*b+Tap("123456789123456789123456789");

    std::cout << "a == " << a.to_s() << std::endl; // Print a in decimal
    std::cout << "b == " << b.to_s() << std::endl << std::endl; // Print b in decimal

    std::cout << "c == \n" << c.to_s() << std::endl << std::endl; // Print c in decimal
    std::cout << "c in binary == \n"  << c.to_s(2) << std::endl << std::endl; // Print c in binary
    std::cout << "c in base 36 == \n" << c.to_s(36) << std::endl << std::endl; // Print c in base 36

    if (b > a){
        std::cout << "b is larger than a" << std::endl;
    }
    else {
        std::cout << "a is larger than b" << std::endl;
    }


    vector<byte> sourceNum;
    sourceNum.push_back(byte(2));
    sourceNum.push_back(byte(0));

    vector<byte> destNum = convertNumberExt(sourceNum, 10, 16);

    for(int i = 0; i < destNum.size(); ++i){
        cout << destNum[i] << endl;
    }
}
