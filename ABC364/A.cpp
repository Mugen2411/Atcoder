#include <iostream>
#include <string>

int main()
{
    size_t N;
    std::cin >> N;
    std::string S;
    bool isBeforeSweet = false;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> S;
        if (S == "sweet")
        {
            if (isBeforeSweet)
            {
                if (i == N - 1)
                    break;
                std::cout << "No";
                return 0;
            }
            else
            {
                isBeforeSweet = true;
            }
        }
        else
        {
            isBeforeSweet = false;
        }
    }
    std::cout << "Yes";
    return 0;
}