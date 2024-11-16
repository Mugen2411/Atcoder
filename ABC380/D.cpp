#include <iostream>
#include <string>

int main()
{
    std::string S;
    std::cin >> S;
    int64_t length = S.size();

    int64_t Q;
    std::cin >> Q;

    while (Q--)
    {
        int64_t K;
        std::cin >> K;
        --K;
        int64_t group = K / length;
        bool needConvert = false;
        for (int i = 0; i < 60; ++i)
        {
            if (group & (1ull << i))
            {
                needConvert = !needConvert;
            }
        }
        char ch = S[K % length];
        const char diff = 'A' - 'a';
        if ('a' <= ch && ch <= 'z')
        {
            if (needConvert)
            {
                std::cout << static_cast<char>(ch + diff);
            }
            else
            {
                std::cout << ch;
            }
        }
        else
        {
            if (needConvert)
            {
                std::cout << static_cast<char>(ch - diff);
            }
            else
            {
                std::cout << ch;
            }
        }
        std::cout << " ";
    }
    return 0;
}