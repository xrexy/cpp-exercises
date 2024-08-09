#include <iostream>
#include <cstdlib>
#include <string>

class Singleton
{
private:
    std::string value;
    Singleton()
    {
        value = "ctor-random";
        std::cout << "Singleton instance created!" << std::endl;
    }

    // Declare copy constructor and assignment operator as deleted to prevent copying.
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

public:
    static Singleton &getInstance()
    {
        static Singleton instance; // This instance is created only once.
        return instance;
    }

    void setValue(std::string value)
    {
        this->value = value;
    }

    std::string getValue()
    {
        return value;
    }
};
