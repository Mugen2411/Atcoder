#include <iostream>
#include <stack>
#include <queue>

int main()
{
    std::stack<size_t> st;
    std::queue<size_t> qu;

    size_t N, tmp;
    std::cin >> N;
    for (size_t i = 0; i < N; ++i)
    {
        std::cin >> tmp;
        qu.push(tmp);
    }
    size_t tmp2;
    for (size_t i = 0; i < N; ++i)
    {
        st.push(qu.front());
        qu.pop();
        while (1)
        {
            if (st.size() <= 1)
            {
                break;
            }
            tmp = st.top();
            st.pop();
            tmp2 = st.top();
            st.pop();
            if (tmp != tmp2)
            {
                st.push(tmp2);
                st.push(tmp);
                break;
            }
            else
            {
                st.push(tmp + 1);
            }
        }
    }
    std::cout << st.size();
    return 0;
}