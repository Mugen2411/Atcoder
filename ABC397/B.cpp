#include <iostream>
#include <string>

int main()
{
    std::string S;
    std::cin >> S;

    int inserted = 0;
    bool isEven = true;
    for (int i = 0; i < S.size(); ++i)
    {
        if (isEven)
        {
            if (S[i] != 'i')
            {
                ++inserted;
                isEven = !isEven;
            }
        }
        else
        {
            if (S[i] != 'o')
            {
                ++inserted;
                isEven = !isEven;
            }
        }
        isEven = !isEven;
    }
    if ((S.size() + inserted) % 2 != 0)
    {
        ++inserted;
    }
    std::cout << inserted;
    return 0;
}