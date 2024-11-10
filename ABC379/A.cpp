#include <iostream>
#include <string>

int main()
{
    std::string N;
    std::cin >> N;
    std::cout << N[1] << N[2] << N[0] << std::endl;
    std::cout << N[2] << N[0] << N[1] << std::endl;
    return 0;
}