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

#include "headers/Tap.h"
#include "headers/Tapx.h"

int main()
{
    mjr::Tap a = "260";
    mjr::Tap b = "300";
    mjr::Tap c = a*b + mjr::Tap("123456789123456789123456789");

    std::cout << "a == " << a << std::endl; // Print a in decimal
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


    Tapx x1 = "2";
    Tapx x2 = "30";
    std::cout << "X2 == " << x2.to_s() << std::endl;

//    Tapx x3 = x1*x2;
//    std::cout << "X3 == " << x3.to_s() << std::endl;
//    std::cout << x3.to_s(2) << std::endl;
//    std::cout << x3.to_s(16) << std::endl;
//    std::cout << x3.to_s(36) << std::endl;
}
