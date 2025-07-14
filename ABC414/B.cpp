#include <iostream>
#include <string>
#include <vector>

int main()
{
    struct ELEM
    {
        char c;
        int64_t l;
    };

    int N;
    std::cin >> N;

    std::vector<ELEM> leng(N);
    int64_t len = 0;
    for (int i = 0; i < N; ++i)
    {
        char c;
        int64_t l;
        std::cin >> c >> l;
        leng[i] = ELEM{c, l};
        len += l;
        if (len > 100)
        {
            std::cout << "Too Long";
            return 0;
        }
    }
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < leng[i].l; ++j)
        {
            std::cout << leng[i].c;
        }
    }
    return 0;
}