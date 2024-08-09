#include <iostream>
#include <vector>

#include "singleton.cpp"

void doSingletonTests()
{
    auto &s1 = Singleton::getInstance();
    auto &s2 = Singleton::getInstance();

    auto printValues = [&s1, &s2]()
    {
        std::cout << "s1: " << s1.getValue() + " | s2: " << s2.getValue() << "\n";
    };

    s1.setValue("1");

    printValues();

    s1.setValue("2");
    s2.setValue("3");

    printValues();

    s2.setValue("4");

    printValues();

    std::cout << "Addresses are the same: " + std::to_string(&s1 == &s2) << std::endl;
}
int main(int argc, char const *argv[])
{
    doSingletonTests();
}
