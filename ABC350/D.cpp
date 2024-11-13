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
#include <unordered_map>

int main()
{
    int64_t N, M;
    std::cin >> N >> M;

    UnionFind uf(N);

    for (int64_t i = 0; i < M; ++i)
    {
        int64_t A, B;
        std::cin >> A >> B;
        --A, --B;
        uf.Merge(A, B);
    }

    std::unordered_map<int64_t, int64_t> groups;
    for (int64_t i = 0; i < N; ++i)
    {
        ++groups[uf.Find(i)];
    }

    int64_t sum = 0;
    for (auto &i : groups)
    {
        sum += (i.second) * (i.second - 1) / 2;
    }

    std::cout << sum - M << std::endl;
    return 0;
}