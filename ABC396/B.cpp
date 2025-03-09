#include <iostream>
#include <stack>

int main()
{
    std::stack<int64_t> st;
    for (int i = 0; i < 100; ++i)
    {
        st.push(0);
    }
    int64_t Q;
    std::cin >> Q;
    while (Q--)
    {
        int cmd;
        std::cin >> cmd;
        switch (cmd)
        {
        case 1:
        {
            int64_t x;
            std::cin >> x;
            st.push(x);
        }
        break;
        case 2:
        {
            std::cout << st.top() << std::endl;
            st.pop();
        }
        break;

        default:
            break;
        }
    }
    return 0;
}