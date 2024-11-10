#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int main()
{
    size_t N;
    std::cin >> N;
    std::vector<std::string> M(N);
    size_t sumC = 0;
    size_t tmp;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> M[i];
        std::cin >> tmp;
        sumC += tmp;
    }
    std::sort(M.begin(), M.end());
    std::cout << M[sumC % N] << std::endl;
    return 0;
}