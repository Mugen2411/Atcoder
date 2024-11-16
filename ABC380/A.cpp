#include <iostream>
#include <string>

int main()
{
    std::string S;
    std::cin >> S;

    int cnt[10] = {0};

    for (int i = 0; i < 6; ++i)
    {
        cnt[S[i] - '0']++;
    }

    if (cnt[1] == 1 && cnt[2] == 2 && cnt[3] == 3)
    {
        std::cout << "Yes";
    }
    else
    {
        std::cout << "No";
    }
    return 0;
}