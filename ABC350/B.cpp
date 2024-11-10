#include <iostream>

int main()
{
    bool teeth[1001] = {0};
    int N, Q;
    std::cin >> N >> Q;
    int cnt = N;
    int query;
    for (int i = 0; i < Q; ++i)
    {
        std::cin >> query;
        if (teeth[query] == 0)
        {
            teeth[query] = 1;
            --cnt;
        }
        else
        {
            teeth[query] = 0;
            ++cnt;
        }
    }
    std::cout << cnt;
}