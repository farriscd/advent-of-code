#include <iostream>
#include <fstream>
#include <string>
// Arrays in C++ are not dynamic so vector constructs are used
#include <vector>

using namespace std;

int main()
{
    string line;
    ifstream inputFile;
    vector<int> v;

    // Read integer list into a vector
    inputFile.open("input.txt");

    if (inputFile.is_open())
    {
        while (getline(inputFile, line, ','))
        {
            v.push_back(stoi(line));
        }
        inputFile.close();
    }

    // Part 1
    v[1] = 12;
    v[2] = 2;

    // Appears to be an iterator pointer that could be used for this
    for (int i = 0; i < v.size(); i += 4)
    {
        //cout << v[i] << ',' << v[i + 1] << ',' << v[i + 2] << ',' << v[i + 3] << '\n';

        // Addition
        if (v[i] == 1)
        {
            v[v[i + 3]] = v[v[i + 1]] + v[v[i + 2]];
        }
        // Multiplication
        else if (v[i] == 2)
        {
            v[v[i + 3]] = v[v[i + 1]] * v[v[i + 2]];
        }
        // Exit
        else if (v[i] == 99)
        {
            //cout << "break" << '\n';
            break;
        }
    }

    cout << v[0] << '\n';

    return 0;
}

// Part 1 Correct answer: 4930687
// Part 2 Correct answer: