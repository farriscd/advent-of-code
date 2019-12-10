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

        if (w < 24)
        {
            if (j == 0)
            {
                std::cout << " ";
            }
            else
            {
                std::cout << "X";
            }
            w++;
        }
        else
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
    std::vector<std::string> inputImage;
    std::vector<std::vector<int>> image;

    inputFile.open("formattedinput.txt");

    if (inputFile.is_open())
    {
        while (getline(inputFile, line))
        {
            inputImage.push_back(line);
        }
        inputFile.close();
    }

    std::vector<int> temp;

    for (auto i : inputImage)
    {
        for (int j = 0; j < i.length(); j++)
        {
            int pix = i[j] - '0';
            temp.push_back(pix);
        }
        image.push_back(temp);
        temp.clear();
    }

    std::vector<int> visible_layer;
    visible_layer = image[0];

    std::cout << '\n';

    for (auto layer : image)
    {
        for (int pixel = 0; pixel < 150; pixel++)
        {
            if (visible_layer[pixel] == 2)
            {
                visible_layer[pixel] = layer[pixel];
            }
        }
    }

    printImage(visible_layer);

    return 0;
}

// Part One Correct Answer: 1560
// Part Two Correct Answer: "UGCUH"