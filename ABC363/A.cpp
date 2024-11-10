#include <iostream>

int main()
{
    int R;
    std::cin >> R;
    R %= 100;
    std::cout << 100 - R;
    return 0;
}