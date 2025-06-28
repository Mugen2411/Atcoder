#include <vector>
#include <iostream>
#include <array>

int main()
{
    int N, M;
    std::cin >> N >> M;
    auto ReadBit = [](uint64_t val, int idx) -> bool
    {
        return val & (1ull << idx);
    };
    auto WriteBit = [ReadBit](uint64_t val, int idx)
    {
        if (ReadBit(val, idx))
        {
            std::cerr << "Write Error!" << std::endl;
        }
        val |= (1ull << idx);
        return val;
    };
    auto GetIdx = [N](int start, int goal)
    {
        int idx = start * N + goal;
        if (idx >= 64)
        {
            std::cerr << "index error!" << std::endl;
        }
        return idx;
    };
    auto DbgOutput = [](uint64_t val)
    {
        for (int i = 0; i < 64; ++i)
        {
            if ((val >> i) & 1)
            {
                std::cerr << 1;
            }
            else
            {
                std::cerr << 0;
            }
        }
        std::cerr << std::endl;
    };
    uint64_t cur = 0ll;
    while (M--)
    {
        int A, B;
        std::cin >> A >> B;
        --A, --B;
        cur = WriteBit(cur, GetIdx(A, B));
        cur = WriteBit(cur, GetIdx(B, A));
    }

    int ans = 0xff;
    auto dfs = [&](auto self, uint64_t curVal, int idx, std::array<char, 8> already)
    {
        // DbgOutput(curVal);
        if (idx == N)
        {
            for (int i = 0; i < N; ++i)
            {
                if (already[i] != 2)
                {
                    return;
                }
            }
            int tmp = 0;
            uint64_t diff = cur ^ curVal;
            for (int i = 0; i < 64; ++i)
            {
                if ((diff >> i) & 1)
                {
                    ++tmp;
                }
            }
            std::cerr << tmp << std::endl;
            ans = std::min(ans, tmp / 2);
            return;
        }

        if (already[idx] > 2)
        {
            std::cerr << "Logic Error!" << std::endl;
            return;
        }
        if (already[idx] == 2)
        {
            self(self, curVal, idx + 1, already);
        }
        else if (already[idx] == 1)
        {
            for (int j = idx + 1; j < N; ++j)
            {
                if (!ReadBit(curVal, GetIdx(idx, j)))
                {
                    if (already[j] >= 2)
                    {
                        continue;
                    }
                    uint64_t newVal = WriteBit(curVal, GetIdx(idx, j));
                    newVal = WriteBit(newVal, GetIdx(j, idx));
                    std::array<char, 8> newAlready = already;
                    ++newAlready[idx];
                    ++newAlready[j];
                    self(self, newVal, idx + 1, newAlready);
                }
            }
        }
        else
        {
            for (int i = idx + 1; i < N - 1; ++i)
            {
                if (already[i] >= 2)
                {
                    continue;
                }
                for (int j = i + 1; j < N; ++j)
                {
                    if (already[j] >= 2)
                    {
                        continue;
                    }
                    uint64_t newVal = WriteBit(curVal, GetIdx(idx, j));
                    newVal = WriteBit(newVal, GetIdx(j, idx));
                    newVal = WriteBit(newVal, GetIdx(idx, i));
                    newVal = WriteBit(newVal, GetIdx(i, idx));
                    std::array<char, 8> newAlready = already;
                    newAlready[idx] += 2;
                    ++newAlready[j];
                    ++newAlready[i];
                    self(self, newVal, idx + 1, newAlready);
                }
            }
        }
    };

    dfs(dfs, 0, 0, std::array<char, 8>());

    std::cout << ans;
}