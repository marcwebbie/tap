#include <iostream>

#include "headers/Tap.h"
#include "headers/Tapx.h"

using namespace mw;
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
