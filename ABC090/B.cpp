#include <iostream>

int main()
{
    int digit[5] = {0};
    int A, B;
    std::cin >> A >> B;
    int answer = 0;
    for (int i = A; i <= B; ++i)
    {
        int tmp = i;
        for (int j = 0; j < 5; ++j)
        {
            digit[j] = tmp % 10;
            tmp /= 10;
        }

        if (digit[0] == digit[4] && digit[1] == digit[3])
        {
            ++answer;
        }
    }
    std::cout << answer << std::endl;
    return 0;
}