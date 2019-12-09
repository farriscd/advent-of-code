#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
    std::string line;
    std::ifstream inputFile;
    std::vector<std::vector<int>> image;

    inputFile.open("input.txt");

    if (inputFile.is_open())
    {
        while (getline(inputFile, line))
        {
        }
        inputFile.close();
    }

    std::vector<int> temp;

    int j = 0;
    for (int i = 1; i < 15000; i++)
    {
        if (j == 150)
        {
            j = 0;
            image.push_back(temp);
            temp.clear();
        }

        int pix = line[i] - '0';
        temp.push_back(pix);
        j++;
    }

    int layer = 0;
    int min_count = 999;
    int min_count_layer = 0;
    int min_sum = 0;
    for (auto i : image)
    {
        layer++;
        int temp_count = count(i.begin(), i.end(), 0);
        if (temp_count < min_count)
        {
            min_count_layer = layer;
            min_count = temp_count;
            min_sum = count(i.begin(), i.end(), 1) * count(i.begin(), i.end(), 2);
        }
    }

    std::cout << min_count_layer << " " << min_count << " " << min_sum << '\n';

    return 0;
}

// Part One Correct Answer: 1560
// Part Two Correct Answer: