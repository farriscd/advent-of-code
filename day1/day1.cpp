#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int calculateFuel(int mass)
{
    int fuel;
    fuel = mass / 3;
    fuel -= 2;
    if (fuel <= 0)
    {
        return 0;
    }
    else
    {
        return fuel;
    }
}

int main()
{
    string line;
    int mass, fuel, simpleSum = 0, advancedSum = 0;
    ifstream inputFile;

    inputFile.open("input.txt");

    if (inputFile.is_open())
    {
        while (getline(inputFile, line))
        {
            mass = stoi(line);
            fuel = calculateFuel(mass);
            simpleSum += fuel;
            advancedSum += fuel;
            while (fuel > 0)
            {
                fuel = calculateFuel(fuel);
                advancedSum += fuel;
            }
        }
        inputFile.close();
    }

    cout << simpleSum << '\n';
    cout << advancedSum << '\n';
    return 0;
}

//Part 1 Correct answer: 3295206
//Part 2 Correct answer: 4939939