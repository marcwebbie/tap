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
}
