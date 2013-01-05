Tap (Type of arbitrary precision)
==========

Tap is a signed type of arbitrary precision for C++. The goal of this project is to have a simple and short library without external dependencies to be used in algorithms that need abitrary precision calculations. 



Examples
---------------
 
#include <iostream>
#include "headers/Tap.h"
#include "headers/Tapx.h"

using mjr::Tap;

int main()
{
	Tap a = "8684864688468";
	Tap b = "6465535646564654465454546554655654654546545465564654484615164646553564656465446545454655465565465454654546556465448461516464655356465646544654545465546556546545465454655646544846151646465535646564654465454546554655654654546545465564654484615164646553564656465446545454655465565465454654546556465448461516464655356465646544654545465546556546545465454655646544846151646465535646564654465454546554655654654546545465564654484615164646553564656465446545454655465565465454654546556465448461516464655356465646544654545465546556546545465454655646544846151646465535646564654465454546554655654654546545465564654484615164646553564656465446545454655465565465454654546556465448461516464655356465646544654545465546556546545465454655646544846151646465535646564654465454546554655654654546545465564654484615164646553564656465446545454655465565465454654546556465448461516464655356465646544654545465546556546545465454655646544846151646465535646564654465454546554655654654546545465564654484615164";
   	Tap c = a*b+Tap("123456789123456789123456789");

   	std::cout << c.to_s() << std::endl; // Print c in decimal
   	std::cout << c.to_s(2) << std::endl; // Print c in binary
    std::cout << c.to_s(36) << std::endl; // Print c in base 36
   	
   	if (b > a){
    	std::cout << "b is larger than a" << std::endl;
    }
    else {
		std::cout << "a is larger than b" << std::endl;
    }
}



License
------------

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.