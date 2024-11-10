#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    size_t N;
    std::cin >> N;
    std::vector<int64_t> H(N);
    std::vector<int64_t> st;

    for (int i = 0; i < N; ++i)
    {
        std::cin >> H[i];
    }

    std::vector<int64_t> ans(N);

    std::reverse(H.begin(), H.end());

    for (int i = 0; i < N; ++i)
    {
        ans[i] = st.size();
        while (!st.empty() && st.back() < H[i])
        {
            st.pop_back();
        }
        st.push_back(H[i]);
    }

    for (auto itr = ans.rbegin(); itr != ans.rend(); ++itr)
    {
        std::cout << *itr << " ";
    }
}