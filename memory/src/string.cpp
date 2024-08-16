#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

using std::string;

class StringPool
{
public:
    std::shared_ptr<string> get(const string &value)
    {
        auto it = pool.find(value);
        if (it != pool.end())
        {
            // string found in the pool, return it
            return it->second;
        }
        else
        {
            // string not found in the pool, create a new one and add it to the pool
            auto newString = std::make_shared<string>(value);
            pool[value] = newString;

            return newString;
        }
    }

    std::shared_ptr<string> operator[](const string &value)
    {
        return get(value);
    }

private:
    std::unordered_map<string, std::shared_ptr<string>> pool;
};

class String
{
public:
    String(const std::string &value, StringPool &pool) : str(pool.get(value)) {}

    bool operator==(const String &other) const
    {
        return *str == *(other.str);
    }

    bool operator!=(const String &other) const
    {
        return *str != *(other.str);
    }

    const std::string &get() const
    {
        return *str;
    }

    friend std::ostream &operator<<(std::ostream &os, const String &myString)
    {
        os << *(myString.str);
        return os;
    }

private:
    std::shared_ptr<std::string> str;
};
