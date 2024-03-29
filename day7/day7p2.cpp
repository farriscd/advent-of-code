#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

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

long long amplifierController(std::vector<long long> &v_in, int phase_setting, int input_signal)
{
    std::vector<int> inputs;
    inputs.push_back(phase_setting);
    inputs.push_back(input_signal);

    long long result;

    long long relative_base = 0;
    long long temp_input = 0;
    for (int i = 0;;)
    {
        std::vector<long long> intcode = splitIntcode(v_in[i]);

        /* Parameters */
        // Calculate param1
        long long param1;
        if (intcode[0] != 3)
        {
            switch (intcode[1])
            {
            // Position mode
            case 0:
                param1 = v_in[v_in[i + 1]];
                break;
            // Immediate mode
            case 1:
                param1 = v_in[i + 1];
                break;
            // Relative mode
            case 2:
                param1 = v_in[v_in[i + 1] + relative_base];
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
                param1 = v_in[i + 1];
                break;
            // Immediate mode
            case 1:
                param1 = i + 1;
                break;
            // Relative mode
            case 2:
                param1 = v_in[i + 1] + relative_base;
                break;
            }
        }

        // Calculate param2
        long long param2;
        switch (intcode[2])
        {
        // Position mode
        case 0:
            param2 = v_in[v_in[i + 2]];
            break;
        // Immediate mode
        case 1:
            param2 = v_in[i + 2];
            break;
        // Relative mode
        case 2:
            param2 = v_in[v_in[i + 2] + relative_base];
            break;
        }

        // Calculate param3
        // When used param3 is an address, so must be used as v_in[param3]
        long long param3;
        switch (intcode[3])
        {
        // Position mode
        case 0:
            param3 = v_in[i + 3];
            break;
        // Immediate mode
        case 1:
            param3 = i + 3;
            break;
        // Relative mode
        case 2:
            param3 = v_in[i + 3] + relative_base;
            break;
        }

        /* Opcodes */
        switch (intcode[0])
        {
        // Addition
        case 1:
            v_in[param3] = param1 + param2;
            i += 4;
            break;
        // Multiplication
        case 2:
            v_in[param3] = param1 * param2;
            i += 4;
            break;
        // Input
        case 3:
            v_in[param1] = inputs[0];
            inputs.erase(inputs.begin());
            i += 2;
            break;
        // Output
        case 4:
            std::cout << "Output integer: " << param1 << '\n';
            result += param1;
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
                v_in[param3] = 1;
            else
                v_in[param3] = 0;
            i += 4;
            break;
        // Equals
        case 8:
            if (param1 == param2)
                v_in[param3] = 1;
            else
                v_in[param3] = 0;
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
    return result;
}

int main()
{
    std::string line;
    std::ifstream inputFile;
    std::vector<long long> v;

    // Read integer list into a vector
    inputFile.open("test2.txt");

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

    std::vector<int> sequence;
    sequence.push_back(5);
    sequence.push_back(6);
    sequence.push_back(7);
    sequence.push_back(8);
    sequence.push_back(9);

    int max_signal = 0;
    std::vector<int> max_sequence;

    std::sort(sequence.begin(), sequence.end());
    do
    {
        int input_signal = 0;
        long long temp;
        for (;;)
        {
            for (auto i : sequence)
            {
                temp = amplifierController(v, i, input_signal);
                input_signal = temp;
            }
        }
        if (input_signal > max_signal)
        {
            max_signal = input_signal;
            max_sequence = sequence;
        }

    } while (std::next_permutation(sequence.begin(), sequence.end()));

    for (auto i : max_sequence)
    {
        std::cout << i << ' ';
    }

    std::cout << '\n';
    std::cout << max_signal << '\n';

    return 0;
}

// Part One Correct Answer: 277328
// Part Two Correct Answer: