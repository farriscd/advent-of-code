#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

void printVectorVert(std::vector<long long> vec)
{
    for (auto i : vec)
    {
        std::cout << i << '\n';
    }
}

void printVectorHori(std::vector<long long> vec)
{
    for (auto i : vec)
    {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}

// Split the intcode into its opcode and possible parameters
std::vector<long long> splitIntcode(long long intcode)
{
    std::vector<long long> splitIntcode;
    // Opcode
    splitIntcode.push_back(intcode % 100);
    // mode of 1st parameter
    splitIntcode.push_back((intcode / 100) % 10);
    // mode of 2nd parameter
    splitIntcode.push_back((intcode / 1000) % 10);
    // mode of 3rd parameter
    splitIntcode.push_back((intcode / 10000) % 10);

    return splitIntcode;
}

int main(int argc, char *argv[])
{
    std::string line;
    std::ifstream inputFile;
    std::vector<long long> v;

    // Read input file
    inputFile.open(argv[1]);

    if (inputFile.is_open())
    {
        while (getline(inputFile, line, ','))
        {
            v.push_back(stoll(line));
        }
        inputFile.close();
    }

    for (int i = v.back(); i < 512000; i++)
    {
        v.push_back(0);
    }

    long long relative_base = 0;
    long long temp_input = 0;
    for (int i = 0;;)
    {
        std::vector<long long> intcode = splitIntcode(v[i]);

        /* Parameters */
        // Calculate param1
        long long param1;
        if (intcode[0] != 3)
        {
            switch (intcode[1])
            {
            // Position mode
            case 0:
                param1 = v[v[i + 1]];
                break;
            // Immediate mode
            case 1:
                param1 = v[i + 1];
                break;
            // Relative mode
            case 2:
                param1 = v[v[i + 1] + relative_base];
                break;
            }
        }
        // There is a problem where param1 is  being used as an address by input
        // so the method for param3 should be used
        else
        {
            switch (intcode[1])
            {
            // Position mode
            case 0:
                param1 = v[i + 1];
                break;
            // Immediate mode
            case 1:
                param1 = i + 1;
                break;
            // Relative mode
            case 2:
                param1 = v[i + 1] + relative_base;
                break;
            }
        }

        // Calculate param2
        long long param2;
        switch (intcode[2])
        {
        // Position mode
        case 0:
            param2 = v[v[i + 2]];
            break;
        // Immediate mode
        case 1:
            param2 = v[i + 2];
            break;
        // Relative mode
        case 2:
            param2 = v[v[i + 2] + relative_base];
            break;
        }

        // Calculate param3
        // When used param3 is an address, so must be used as v[param3]
        long long param3;
        switch (intcode[3])
        {
        // Position mode
        case 0:
            param3 = v[i + 3];
            break;
        // Immediate mode
        case 1:
            param3 = i + 3;
            break;
        // Relative mode
        case 2:
            param3 = v[i + 3] + relative_base;
            break;
        }

        /* Opcodes */
        switch (intcode[0])
        {
        // Addition
        case 1:
            v[param3] = param1 + param2;
            i += 4;
            break;
        // Multiplication
        case 2:
            v[param3] = param1 * param2;
            i += 4;
            break;
        // Input
        case 3:
            std::cout << "Input integer: ";
            std::cin >> temp_input;
            v[param1] = temp_input;
            i += 2;
            break;
        // Output
        case 4:
            std::cout << "Output integer: " << param1 << '\n';
            i += 2;
            break;
        // Jump-if-true
        case 5:
            if (param1 != 0)
                i = param2;
            else
                i += 3;
            break;
        // Jump-if-false
        case 6:
            if (param1 == 0)
                i = param2;
            else
                i += 3;
            break;
        // Less than
        case 7:
            if (param1 < param2)
                v[param3] = 1;
            else
                v[param3] = 0;
            i += 4;
            break;
        // Equals
        case 8:
            if (param1 == param2)
                v[param3] = 1;
            else
                v[param3] = 0;
            i += 4;
            break;
        // Adjust relative base
        case 9:
            relative_base += param1;
            i += 2;
            break;
        // Exit
        case 99:
            goto endprogram;
        }
    }

endprogram:
    return 0;
}

// Part One Correct Answer: 3742852857
// Part Two Correct Answer: 73439