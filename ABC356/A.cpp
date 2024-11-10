#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    size_t N, L, R;
    std::cin >> N >> L >> R;
    std::vector<int> vec(N);
    for (int i = 0; i < N; ++i)
    {
        vec[i] = i + 1;
    }

    std::reverse(vec.begin() + (L - 1), vec.begin() + (R));

    for (int i = 0; i < N; ++i)
    {
        std::cout << vec[i] << " ";
    }
    return 0;
}