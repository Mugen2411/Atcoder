#ifndef ___INCLUDED_UNIONFIND___
#define ___INCLUDED_UNIONFIND___

#ifndef ___INCLUDED_VECTOR___
#define ___INCLUDED_VECTOR___
#include <vector>
#endif //___INCLUDED_VECTOR___

#ifndef ___INCLUDED_CSTDDEF___
#define ___INCLUDED_CSTDDEF___
#include <cstddef>
#endif //___INCLUDED_CSTDDEF___

#ifndef ___INCLUDED_CSTDINT___
#define ___INCLUDED_CSTDINT___
#include <cstdint>
#endif //___INCLUDED_CSTDINT___

/**
    @brief        UnionFind
 */
class UnionFind final
{
public:
    /**
        @brief       コンストラクタ

        @param[in]   size        要素数
     */
    UnionFind(size_t size)
        : m_data(size, NO_PARENT), m_size(size, 1)
    {
    }

    /**
        @brief    デストラクタ
     */
    ~UnionFind()
    {
    }

    /**
        @brief        親のインデックスを取得する

        @param[in]  index       対象とするインデックス

        @return     親のインデックス
     */
    int64_t Find(int64_t index)
    {
        if (m_data[index] == NO_PARENT)
        {
            return index;
        }
        return m_data[index] = Find(m_data[index]);
    }

    /**
        @brief                右辺と左辺を同じグループとする

        @param[in]  lhs     左辺のインデックス
        @param[in]  rhs     右辺のインデックス
     */
    void Merge(int64_t lhs, int64_t rhs)
    {
        // 先に親まで繋げておく
        lhs = Find(lhs);
        rhs = Find(rhs);

        // 同じグループならば何もしない
        if (lhs == rhs)
        {
            return;
        }

        // 常に左辺がサイズ小さい方とする
        if (m_size[lhs] < m_size[rhs])
        {
            std::swap(lhs, rhs);
        }

        m_size[rhs] += m_size[lhs];
        m_data[lhs] = rhs;
    }

    /**
        @brief            親が共通かどうか

        @param[in]  lhs     左辺のインデックス
        @param[in]  rhs     右辺のインデックス

        @retval     true    両辺の親が共通
        @retval     false   両辺の親が異なる
     */
    bool IsSame(int64_t lhs, int64_t rhs)
    {
        int64_t parentL = Find(lhs);
        int64_t parentR = Find(rhs);

        return parentL == parentR;
    }

private:
    const int64_t NO_PARENT = -1; //!< 親がいない(=自分が親)であることを示す定数
    std::vector<int64_t> m_data;  //!< 本体となる配列
    std::vector<int64_t> m_size;  //!< 木のサイズ
};

#endif //___INCLUDED_UNIONFIND___

#include <iostream>

int main()
{
    int64_t H, W;
    std::cin >> H >> W;

    auto idx = [&](int64_t r, int64_t c)
    {
        return r * W + c;
    };
    UnionFind uf(H * W);
    std::vector<int64_t> grid(H * W, 0);

    int64_t RLDU[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    int64_t Q;
    std::cin >> Q;

    while (Q--)
    {
        int t;
        std::cin >> t;
        switch (t)
        {
        case 1:
        {
            int64_t r, c;
            std::cin >> r >> c;
            --r, --c;

            grid[idx(r, c)] = 1;
            for (auto &d : RLDU)
            {
                if (0 <= r + d[1] && r + d[1] < W && 0 <= c + d[0] && c + d[0] < H && grid[idx(r + d[1], c + d[0])])
                {
                    uf.Merge(idx(r, c), idx(r + d[1], c + d[0]));
                }
            }
        }
        break;
        case 2:
        {
            int64_t ra, ca, rb, cb;
            std::cin >> ra >> ca >> rb >> cb;
            --ra, --ca, --rb, --cb;

            if (grid[idx(ra, ca)] && grid[idx(rb, cb)] && uf.IsSame(idx(ra, ca), idx(rb, cb)))
            {
                std::cout << "Yes" << std::endl;
            }
            else
            {
                std::cout << "No" << std::endl;
            }
        }

        default:
            break;
        }
    }

    return 0;
}