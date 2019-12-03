/*
    This a very slow brute force answer to the problem
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

// Code taken from GeeksForGeeks and modified
// https://www.geeksforgeeks.org/split-numeric-alphabetic-and-special-symbols-from-a-string/
int returnNum(string str)
{
    string alpha, num, special;
    for (int i = 0; i < str.length(); i++)
    {
        if (isdigit(str[i]))
            num.push_back(str[i]);
        else if ((str[i] >= 'A' && str[i] <= 'Z') ||
                 (str[i] >= 'a' && str[i] <= 'z'))
            alpha.push_back(str[i]);
        else
            special.push_back(str[i]);
    }
    return stoi(num);
}
string returnAlpha(string str)
{
    string alpha, num, special;
    for (int i = 0; i < str.length(); i++)
    {
        if (isdigit(str[i]))
            num.push_back(str[i]);
        else if ((str[i] >= 'A' && str[i] <= 'Z') ||
                 (str[i] >= 'a' && str[i] <= 'z'))
            alpha.push_back(str[i]);
        else
            special.push_back(str[i]);
    }
    return alpha;
}

int main()
{
    // Read in paths and to make directions
    vector<string> firstWirePath, secondWirePath;
    vector<vector<int>> firstWireCoords, secondWireCoords;
    vector<int> point(3, 0);
    int firstWireStepCount, secondWireStepCount;

    ifstream inputFile;
    string line, word;
    inputFile.open("input.txt");

    if (inputFile.is_open())
    {
        int lineCount = 0;
        while (getline(inputFile, line))
        {
            lineCount++;
            if (lineCount == 1)
            {
                stringstream sstream(line);
                while (getline(sstream, word, ','))
                    firstWirePath.push_back(word);
            }
            if (lineCount == 2)
            {
                stringstream sstream(line);
                while (getline(sstream, word, ','))
                    secondWirePath.push_back(word);
            }
        }
        inputFile.close();
    }

    // Calculate first wire
    for (auto a : firstWirePath)
    {
        string direction = returnAlpha(a);
        int distance = returnNum(a);
        if (direction == "R")
        {
            for (int i = 0; i < distance; i++)
            {
                point[0]++;
                point[2]++;
                firstWireCoords.push_back(point);
            }
        }
        if (direction == "L")
        {
            for (int i = 0; i < distance; i++)
            {
                point[0]--;
                point[2]++;
                firstWireCoords.push_back(point);
            }
        }
        if (direction == "U")
        {
            for (int i = 0; i < distance; i++)
            {
                point[1]++;
                point[2]++;
                firstWireCoords.push_back(point);
            }
        }
        if (direction == "D")
        {
            for (int i = 0; i < distance; i++)
            {
                point[1]--;
                point[2]++;
                firstWireCoords.push_back(point);
            }
        }
    }
    cout << "First Wire calculated" << '\n';

    // Calculate second wire
    point[0] = 0;
    point[1] = 0;
    point[2] = 0;
    for (auto a : secondWirePath)
    {
        string direction = returnAlpha(a);
        int distance = returnNum(a);
        if (direction == "R")
        {
            for (int i = 0; i < distance; i++)
            {
                point[0]++;
                point[2]++;
                secondWireCoords.push_back(point);
            }
        }
        if (direction == "L")
        {
            for (int i = 0; i < distance; i++)
            {
                point[0]--;
                point[2]++;
                secondWireCoords.push_back(point);
            }
        }
        if (direction == "U")
        {
            for (int i = 0; i < distance; i++)
            {
                point[1]++;
                point[2]++;
                secondWireCoords.push_back(point);
            }
        }
        if (direction == "D")
        {
            for (int i = 0; i < distance; i++)
            {
                point[1]--;
                point[2]++;
                secondWireCoords.push_back(point);
            }
        }
    }
    cout << "Second Wire calculated" << '\n';

    // Compare wire paths
    for (auto firstWire : firstWireCoords)
        for (auto secondWire : secondWireCoords)
        {
            if (firstWire[0] == secondWire[0] && firstWire[1] == secondWire[1])
            {
                cout << firstWire[0] << ',' << firstWire[1] << ' ' << firstWire[2] << '\n';
                cout << secondWire[0] << ',' << secondWire[1] << ' ' << secondWire[2] << '\n';
            }
        }

    return 0;
}

// Part 1 Correct Answer: 1211
// Part 2 Correct Answer: 101,386