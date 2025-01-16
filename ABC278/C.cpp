#include <vector>
#include <iostream>
#include <unordered_set>

int main()
{
    int64_t N, Q;
    std::cin >> N >> Q;
    std::unordered_set<int64_t> graph;

    while (Q--)
    {
        int T;
        int64_t A, B;
        std::cin >> T >> A >> B;
        --A, --B;

        switch (T)
        {
        case 1:
            graph.insert(A * N + B);
            break;

        case 2:
            graph.erase(A * N + B);
            break;

        case 3:
        {
            if (graph.count(A * N + B) != 0 && graph.count(B * N + A) != 0)
            {
                std::cout << "Yes" << std::endl;
            }
            else
            {
                std::cout << "No" << std::endl;
            }
            break;
        }
        default:
            break;
        }
    }
}