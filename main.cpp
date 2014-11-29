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

using namespace mjr;
using namespace std;

int main()
{
    Tap a = "260";
    Tap b = "300";
    Tap c = a * b;

    cout << "a == " << a << endl; // Print a in decimal
    cout << "b == " << b << endl; // Print b in decimal
    cout << "c == " << c << endl; // Print c in decimal
}
