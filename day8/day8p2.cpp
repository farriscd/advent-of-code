#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

void printImage(std::vector<int> image_layer)
{
    int w = 0;
    for (auto j : image_layer)
    {
        std::cout << j;
        w++;
        if (w == 25)
        {
            std::cout << '\n';
            w = 0;
        }
    }
    std::cout << '\n';
}

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

    std::vector<int> visible_layer;
    visible_layer = image[0];

    printImage(visible_layer);

    for (auto i : image)
    {

        for (int j = 0; j < 150; j++)
        {
            if (visible_layer[j] == 2 && i[j] != 2)
            {
                std::cout << visible_layer[j] << "->" << i[j] << '\n';
                visible_layer[j] = i[j];
            }
        }
    }

    printImage(visible_layer);

    return 0;
}

// Part One Correct Answer: 1560
// Part Two Correct Answer: