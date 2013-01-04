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
#include "Tap.h"
#include "Tapx.h"

using namespace std;
using mjr::Tap;

int main()
{
    /*
    Tap a = "255";
    unsigned long long int limit = 10000;
    unsigned long long int i =255;
    for (; i < limit; ++i){
        a++;        // 0m0.736s
        //++a;        // 0m0.094s
        //a.inc1();   // 0m0.047s
        //a.inc1v2(); // 0m0.035s
        //a.inc1v3();   // 0m0.035s
    }

    Tapx x = "260";

    cout << i << endl;
    cout << a.to_s() << endl;
    cout << (1UL<<32) << endl;
*/
//    Tap a = "8684864688468";
//    Tap b = "6465535646564654465454546554655654654546545465564654484615164646553564656465446545454655465565465454654546556465448461516464655356465646544654545465546556546545465454655646544846151646465535646564654465454546554655654654546545465564654484615164646553564656465446545454655465565465454654546556465448461516464655356465646544654545465546556546545465454655646544846151646465535646564654465454546554655654654546545465564654484615164646553564656465446545454655465565465454654546556465448461516464655356465646544654545465546556546545465454655646544846151646465535646564654465454546554655654654546545465564654484615164646553564656465446545454655465565465454654546556465448461516464655356465646544654545465546556546545465454655646544846151646465535646564654465454546554655654654546545465564654484615164646553564656465446545454655465565465454654546556465448461516464655356465646544654545465546556546545465454655646544846151646465535646564654465454546554655654654546545465564654484615164";
//    Tap c = a*b;

    Tap c = "123456789123456789123456789";

    cout << '[';
    for(int i=c.len()-1; i >= 0; --i){
        cout << int(c[i]) << ',';
    }
    cout << ']' << endl;
}
