#include <iostream>
#include <string>
#include "prompt.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

const u_int8_t WEEKS_IN_MONTH = 4;

int main(int argc, char const *argv[])
{
    int travelDaysPerWeek = prompt<int>("How many days do you travel per week? (1-7) ", [](const int value)
                                        { return value >= 1 && value <= 7; });

    float costPerDay = prompt<float>("How much does it cost per day? ", [](const float value)
                                     { return value > 0.0; });

    int cardPrice = prompt<int>("How much does the card cost? ", [](const int value)
                                { return value > 0; });

    float totalCost = (travelDaysPerWeek * WEEKS_IN_MONTH) * costPerDay;
    float moneySaved = totalCost - cardPrice;
    if (moneySaved <= 0)
    {
        cout << "\n\nNot worth it, you spend " << totalCost << " on travel per month, and the card is worth " << cardPrice << ". That is a loss of " << -moneySaved << "" << endl;
        return 0;
    }

    float percentageSaved = (moneySaved / totalCost) * 100;
    cout << "\n\nWorth it, You save " << moneySaved << " (" << percentageSaved << "%)" << endl;
    return 0;
}
