#include <iostream>

#include "string.cpp"

int main(int argc, char const *argv[])
{
    StringPool pool;

    String str1("hello", pool);
    String str2("world", pool);
    String str3("hello", pool); // should be the same instance as str1

    std::cout << "str1: " << str1 << std::endl;
    std::cout << "str2: " << str2 << std::endl;
    std::cout << "str3: " << str3 << std::endl;

    if (str1 == str3)
    {
        std::cout << "str1 and str3 are the same instance." << std::endl;
    }
    else
    {
        std::cout << "str1 and str3 are different instances." << std::endl;
    }

    return 0;
}
