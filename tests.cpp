#include <iostream>
#include <cassert>

// User include Tap header
#include "headers/Tap.h"


int main()
{
    // User puts using statement for mjr namespace
    using namespace mjr;

    // User create a new instance of Tap object named 'x'
    Tap x = Tap();

    // User assign 5000000 to 'x'
    x = "5000000";

    // User create another instance of Tap object named 'y'
    Tap y = Tap();

    // User assign 500000000000000000000000000000000000000 to 'y'
    y = "500000000000000000000000000000000000000";

    // User multiplies 'x' to 'y' and assign to a new instance called 'z'
    Tap z = x*y;

    // User prints 'z' using Tap method to_s()
    // The result is: 2500000000000000000000000000000000000000000000
    assert(z.to_s() == "2500000000000000000000000000000000000000000000");
    std::cout << z.to_s() << std::endl;

    return 0;
}