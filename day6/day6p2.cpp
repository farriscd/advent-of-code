#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
    std::string line;
    std::ifstream inputFile;
    std::vector<std::vector<std::string>> orbits;

    inputFile.open("input.txt");

    if (inputFile.is_open())
    {
        while (getline(inputFile, line))
        {
            // Input values are as ABC)DEF, so we split it around ) by position
            std::vector<std::string> temp;
            std::string orbit = line.substr(0, 3);
            std::string object = line.substr(4, 7);
            temp.push_back(orbit);
            temp.push_back(object);

            orbits.push_back(temp);
        }
        inputFile.close();
    }

    sort(orbits.begin(), orbits.end());

    int last_pos = 0;
    int sum = 0;

    std::vector<std::string> temp;
    temp.push_back("YOU");
    while (orbits.size() > 0)
    {
        //std::cout << orbits.size() << '\n';

        /*
        for (auto i : temp)
        {
            std::cout << i << ' ';
        }
        std::cout << '\n';
        */

        bool eop = true;

        for (int i = 0; i < orbits.size(); i++)
        {
            if ((orbits[i][0] == temp.back()) && (orbits[i][1] != temp.end()[-2]))
            {
                temp.push_back(orbits[i][1]);
                eop = false;
                last_pos = i;
                break;
            }
            if ((orbits[i][1] == temp.back()) && (orbits[i][0] != temp.end()[-2]))
            {
                temp.push_back(orbits[i][0]);
                eop = false;
                last_pos = i;
                break;
            }
        }

        if (eop == true)
        {
            if (temp.back() == "SAN")
            {
                for (auto i : temp)
                {
                    std::cout << i << ' ';
                }
                std::cout << '\n';
                std::cout << temp.size();
            }
            orbits.erase(orbits.begin() + last_pos);
            temp.clear();
            temp.push_back("YOU");
        }
    }

    return 0;
}

// Part One Correct Answer: 142497
// Part Two Correct Answer: 301