#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    string line;
    ifstream inputFile;
    vector<int> v;

    // Read integer list into a vector
    inputFile.open("test.txt");

    if (inputFile.is_open())
    {
        while (getline(inputFile, line, ','))
        {
            v.push_back(stoi(line));
        }
        inputFile.close();
    }

    for (int i = 0; i < v.size();)
    {
        // Addition - Opcode 1
        if (v[i] == 1)
        {
            v[v[i + 3]] = v[v[i + 1]] + v[v[i + 2]];
            i += 4;
        }
        // Multiplication - Opcode 2
        else if (v[i] == 2)
        {
            v[v[i + 3]] = v[v[i + 1]] * v[v[i + 2]];
            i += 4;
        }
        // Input - Opcode 3
        else if (v[i] == 3)
        {
            int temp;
            cout << "Input integer: ";
            cin >> temp;
            v[v[i + 1]] = temp;
            i += 2;
        }
        // Output - Opcode 4
        else if (v[i] == 4)
        {
            cout << "Output integer: " << v[v[i + 1]] << '\n';
            i += 2;
        }

        // Exit - Opcode 99
        else if (v[i] == 99)
        {
            //cout << "break" << '\n';
            break;
        }
    }

    return 0;
}