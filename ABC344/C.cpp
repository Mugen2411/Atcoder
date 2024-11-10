#include <iostream>
#include <vector>
#include <set>

int main()
{
    size_t N, M, L, Q;
    std::cin >> N;
    std::vector<size_t> A(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> A[i];
    }
    std::cin >> M;
    std::vector<size_t> B(M);
    for (int i = 0; i < M; ++i)
    {
        std::cin >> B[i];
    }
    std::cin >> L;
    std::vector<size_t> C(L);
    for (int i = 0; i < L; ++i)
    {
        std::cin >> C[i];
    }
    std::cin >> Q;
    std::vector<size_t> X(Q);
    for (int i = 0; i < Q; ++i)
    {
        std::cin >> X[i];
    }
    std::set<size_t> s;
    for (int a = 0; a < N; ++a)
    {
        for (int b = 0; b < M; ++b)
        {
            for (int c = 0; c < L; ++c)
            {
                s.insert(A[a] + B[b] + C[c]);
            }
        }
    }

    for (int i = 0; i < Q; ++i)
    {
        if (s.count(X[i]) == 0)
        {
            std::cout << "No" << std::endl;
        }
        else
        {
            std::cout << "Yes" << std::endl;
        }
    }

    return 0;
}
