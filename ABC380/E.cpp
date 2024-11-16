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

#include <set>
#include <cassert>

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
        for (int64_t i = 0; i < size; ++i)
        {
            m_parent.insert(i);
        }
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
        assert(0 <= index && index < m_data.size());
        if (m_data[index] == NO_PARENT)
        {
            return index;
        }
        m_parent.erase(index);
        return m_data[index] = Find(m_data[index]);
    }

    /**
        @brief                右辺と左辺を同じグループとする

        @param[in]  lhs     左辺のインデックス
        @param[in]  rhs     右辺のインデックス
     */
    void Merge(int64_t lhs, int64_t rhs)
    {
        assert(0 <= lhs && lhs < m_data.size());
        assert(0 <= rhs && rhs < m_data.size());
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
        assert(0 <= lhs && lhs < m_data.size());
        assert(0 <= rhs && rhs < m_data.size());

        int64_t parentL = Find(lhs);
        int64_t parentR = Find(rhs);

        return parentL == parentR;
    }

    int64_t GetSize(int64_t index)
    {
        assert(0 <= index && index < m_data.size());
        return m_size[Find(index)];
    }

    template <class Func>
    void EachParent(Func f)
    {
        for (auto &i : m_parent)
        {
            f(i);
        }
    }

    int64_t GetNextParent(int64_t idx)
    {
        int64_t parent = Find(idx);
        auto itr = m_parent.lower_bound(idx);
        if (itr == m_parent.end())
        {
            return -1;
        }
        return *(++itr);
    }

    int64_t GetPrevParent(int64_t idx)
    {
        int64_t parent = Find(idx);
        auto itr = m_parent.lower_bound(idx);
        if (itr == m_parent.begin())
        {
            return -1;
        }
        return *(--itr);
    }

private:
    const int64_t NO_PARENT = -1; //!< 親がいない(=自分が親)であることを示す定数
    std::vector<int64_t> m_data;  //!< 本体となる配列
    std::vector<int64_t> m_size;  //!< 木のサイズ
    std::set<int64_t> m_parent;
};

#endif //___INCLUDED_UNIONFIND___

#include <iostream>

int main()
{
    int64_t N, Q;
    std::cin >> N >> Q;
    std::vector<int64_t> color(N);
    UnionFind uf(N);

    for (int i = 0; i < N; ++i)
    {
        color[i] = i;
    }

    while (Q--)
    {
        int cmd;
        std::cin >> cmd;
        switch (cmd)
        {
        case 1:
        {
            int64_t x, c;
            std::cin >> x >> c;
            --x, --c;
            color[uf.Find(x)] = c;
            int64_t l = uf.GetPrevParent(x);
            if (l != -1 && color[l] == c)
            {
                uf.Merge(x, uf.Find(l));
                color[uf.Find(x)] = c;
                color[uf.Find(l)] = c;
            }
            int64_t r = uf.GetNextParent(x);
            if (r != -1 && color[r] == c)
            {
                uf.Merge(x, uf.Find(r));
                color[uf.Find(x)] = c;
                color[uf.Find(r)] = c;
            }
        }
        break;
        case 2:
        {
            int64_t c;
            std::cin >> c;
            --c;
            int64_t ans = 0;
            auto f = [&](int64_t idx)
            {
                if (color[idx] == c)
                {
                    ans += uf.GetSize(idx);
                }
            };
            uf.EachParent(f);
            std::cout << ans << std::endl;
        }
        }
    }
    return 0;
}