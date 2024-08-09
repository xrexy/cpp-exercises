#include <iostream>
#include <string>

class Singleton
{
private:
    std::string value;
    Singleton()
    {
        value = "ctor";
        std::cout << "Singleton instance created!" << std::endl;
    }

    // declare copy constructor and assignment operator as deleted to prevent copying.
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

public:
    static Singleton &getInstance()
    {
        static Singleton instance; // this instance is created only once since it is static
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
