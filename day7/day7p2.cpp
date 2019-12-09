#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

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

// VERY IMPORTANT TO PASS BY REFERENCE I AM STUPID
std::vector<int> amplifierController(std::vector<int> &v_in, int phase_setting, int input_signal)
{
    std::vector<int> inputs;
    inputs.push_back(phase_setting);
    inputs.push_back(input_signal);
    std::vector<int> result;
    result.push_back(0);
    result.push_back(0);

    for (int i = 0; i < v_in.size();)
    {
        std::vector<int> intcode = splitIntcode(v_in[i]);
        int param1, param2, param3;

        param1 = intcode[2] == 1 ? v_in[i + 1] : v_in[v_in[i + 1]];
        param2 = intcode[1] == 1 ? v_in[i + 2] : v_in[v_in[i + 2]];
        // Currently dont really use param3
        //param3 = intcode[0] == 1 ? v_in[i + 3] : v_in[v_in[i + 3]];

        //std::cout << v_in[i] << " " << param1 << " " << param2 << '\n';

        // Addition - Opcode 1
        if (intcode[3] == 1)
        {
            v_in[v_in[i + 3]] = param1 + param2;
            i += 4;
        }
        // Multiplication - Opcode 2
        else if (intcode[3] == 2)
        {
            v_in[v_in[i + 3]] = param1 * param2;
            i += 4;
        }
        // Input - Opcode 3
        else if (intcode[3] == 3)
        {

            if (inputs.empty())
            {
                int temp;
                temp = result[0];
                //std::cin >> temp;
                v_in[v_in[i + 1]] = temp;
            }
            else
            {
                v_in[v_in[i + 1]] = inputs[0];
                inputs.erase(inputs.begin());
            }

            i += 2;
        }
        // Output - Opcode 4
        else if (intcode[3] == 4)
        {
            i += 2;
            //std::cout << param1 << '\n';
            result[0] = param1;
            break;
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
                v_in[v_in[i + 3]] = 1;
                i += 4;
            }
            else
            {
                v_in[v_in[i + 3]] = 0;
                i += 4;
            }
        }

        // Equals - Opcode 8
        else if (intcode[3] == 8)
        {
            if (param1 == param2)
            {
                v_in[v_in[i + 3]] = 1;
                i += 4;
            }
            else
            {
                v_in[v_in[i + 3]] = 0;
                i += 4;
            }
        }

        // Exit - Opcode 99
        else if (intcode[3] == 99)
        {
            std::cout << "BREAK" << '\n';
            result[1] = 1;
            break;
        }
    }
    return result;
}

int main()
{
    std::string line;
    std::ifstream inputFile;
    std::vector<int> v;

    // Read integer list into a vector
    inputFile.open("test2.txt");

    if (inputFile.is_open())
    {
        while (getline(inputFile, line, ','))
        {
            v.push_back(stoi(line));
        }
        inputFile.close();
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
        std::vector<int> temp;
        temp.push_back(0);
        temp.push_back(0);
        while (temp[1] == 0)
        {
            for (auto i : sequence)
            {
                temp = amplifierController(v, i, input_signal);
                input_signal = temp[0];
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