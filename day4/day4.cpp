#include <iostream>

using namespace std;

int main()
{

    int count = 0;
    for (int i = 172851; i < 675869; i++)
    {
        bool isRepeating = false;
        bool isDecreasing = true;
        int temp[6];
        temp[0] = i / 100000;
        temp[1] = (i / 10000) % 10;
        temp[2] = (i / 1000) % 10;
        temp[3] = (i / 100) % 10;
        temp[4] = (i / 10) % 10;
        temp[5] = (i % 10);

        for (int j = 0; j < 5; j++)
        {
            if (temp[j] > temp[j + 1])
            {
                isDecreasing = false;
            }
            if (temp[j] == temp[j + 1])
            {
                isRepeating = true;
            }
        }
        if ((isRepeating) && (isDecreasing))
        {
            count++;
        }
    }

    cout << count << '\n';
    return 0;
}

// Part One Correct Answer: 1660