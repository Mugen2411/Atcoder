#include <iostream>

int main()
{
    size_t N, M;
    int64_t male[101] = {0};
    std::cin >> N >> M;
    while (M--)
    {
        int64_t A;
        char B;
        std::cin >> A >> B;
        if (B == 'F')
        {
            std::cout << "No" << std::endl;
            continue;
        }
        if (male[A] == 0)
        {
            std::cout << "Yes" << std::endl;
        }
        else
        {
            std::cout << "No" << std::endl;
        }
        ++male[A];
    }
    return 0;
}