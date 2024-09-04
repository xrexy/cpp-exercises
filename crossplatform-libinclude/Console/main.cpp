#include <iostream>

#include "multiply_dll.h"
#include "multiply_static.h"
#include "circle.h"

int main()
{
    std::cout << "(dll;x2) 5 * 3 = " << multiplyDLL(5, 3) << "\n";

    std::cout << "(static;x3) 5 * 3 = " << multiplyStatic(5, 3) << "\n";

    std::cout << "(nested_dll;x2) radius(4) * 2 * 2 = " << calculateCircleDiameter(4) << std::endl;
}
