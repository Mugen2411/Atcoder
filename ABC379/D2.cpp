#include <iostream>
#include <queue>

int main()
{
    int64_t Q;
    std::cin >> Q;

    std::queue<int64_t> inventory;
    int64_t curTime = 0;
    while (Q--)
    {
        int cmd;
        std::cin >> cmd;
        switch (cmd)
        {
        case 1:
            inventory.push(curTime);
            break;
        case 2:
        {
            int64_t T;
            std::cin >> T;
            curTime += T;
        }
        break;
        case 3:
        {
            int64_t H;
            std::cin >> H;
            int64_t ans = 0;
            while (!inventory.empty() && curTime - inventory.front() >= H)
            {
                ++ans;
                inventory.pop();
            }
            std::cout << ans << std::endl;
        }
        break;

        default:
            break;
        }
    }

    return 0;
}