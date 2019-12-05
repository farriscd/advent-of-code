#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// This is hard written knowing that instruction codes are of a certain length
std::vector<int> splitIntcode(int intcode)
{
    std::vector<int> splitIntcode;
    // mode of 3rd parameter
    splitIntcode.push_back((intcode / 10000) % 10);
    // mode of 2nd parameter
    splitIntcode.push_back((intcode / 1000) % 10);
    // mode of 1st parameter
    splitIntcode.push_back((intcode / 100) % 10);
    // Opcode
    splitIntcode.push_back(intcode % 100);

    return splitIntcode;
}

int main()
{
    std::string line;
    std::ifstream inputFile;
    std::vector<int> v;

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

    for (int i = 0; i < v.size();)
    {
        std::vector<int> intcode = splitIntcode(v[i]);
        int param1, param2, param3;

        param1 = intcode[2] == 1 ? v[i + 1] : v[v[i + 1]];
        param2 = intcode[1] == 1 ? v[i + 2] : v[v[i + 2]];
        // Currently dont really use param3
        // param3 = intcode[0] == 1 ? v[i + 3] : v[v[i + 3]];

        // Addition - Opcode 1
        if (intcode[3] == 1)
        {
            v[v[i + 3]] = param1 + param2;
            i += 4;
        }
        // Multiplication - Opcode 2
        else if (intcode[3] == 2)
        {
            v[v[i + 3]] = param1 * param2;
            i += 4;
        }
        // Input - Opcode 3
        else if (intcode[3] == 3)
        {
            int temp = 0;
            std::cout << "Input integer: ";
            std::cin >> temp;
            v[v[i + 1]] = temp;
            i += 2;
        }
        // Output - Opcode 4
        else if (intcode[3] == 4)
        {
            std::cout << "Output integer: " << param1 << '\n';
            i += 2;
        }

        // Jump-if-true - Opcode 5
        else if (intcode[3] == 5)
        {
            if (param1 != 0)
            {
                i = param2;
            }
            else
            {
                i += 3;
            }
        }

        // Jump-if-false - Opcode 6
        else if (intcode[3] == 6)
        {
            if (param1 == 0)
            {
                i = param2;
            }
            else
            {
                i += 3;
            }
        }

        // Less than - Opcode 7
        else if (intcode[3] == 7)
        {
            if (param1 < param2)
            {
                v[v[i + 3]] = 1;
                i += 4;
            }
            else
            {
                v[v[i + 3]] = 0;
                i += 4;
            }
        }

        // Equals - Opcode 8
        else if (intcode[3] == 8)
        {
            if (param1 == param2)
            {
                v[v[i + 3]] = 1;
                i += 4;
            }
            else
            {
                v[v[i + 3]] = 0;
                i += 4;
            }
        }

        // Exit - Opcode 99
        else if (intcode[3] == 99)
        {
            //cout << "break" << '\n';
            break;
        }
    }

    return 0;
}

// Part One Correct Answer: 7265618
// Part Two Correct Answer: 7731427