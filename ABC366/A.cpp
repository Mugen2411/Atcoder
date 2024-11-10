#include <iostream>

int main()
{
    size_t N, T, A;
    std::cin >> N >> T >> A;
    size_t win = std::max(T, A);
    size_t lose = std::min(T, A);
    if(win > N / 2)
    {
        std::cout << "Yes";
    }else
    {
        std::cout << "No";
    }
    return 0;
}