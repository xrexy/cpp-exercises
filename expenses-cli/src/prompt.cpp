#include <iostream>
#include <limits>
#include <string>

template <typename T>
T prompt(const std::string &message, bool (*validationFunc)(T))
{
    T value;
    while (true)
    {
        std::cout << message;
        std::cin >> value;
        if (validationFunc(value))
        {
            break;
        }
        std::cout << "Invalid input" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return value;
}

template int prompt(const std::string &message, bool (*validationFunc)(int));
template float prompt(const std::string &message, bool (*validationFunc)(float));
template double prompt(const std::string &message, bool (*validationFunc)(double));
template long double prompt(const std::string &message, bool (*validationFunc)(long double));
template std::string prompt(const std::string &message, bool (*validationFunc)(std::string));
