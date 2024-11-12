#include <iostream>

#ifndef ___INCLUDED_UNIONFIND___
#define ___INCLUDED_UNIONFIND___

#ifndef ___INCLUDED_VECTOR___
#define ___INCLUDED_VECTOR___
#include <vector>
#endif //___INCLUDED_VECTOR___

/**
    @brief	    UnionFind
 */
class UnionFind final
{
public:
    /**
        @brief       コンストラクタ

        @param[in]   size        要素数
     */
    UnionFind(size_t size)
        : m_data(size, NO_PARENT), m_size(size, 0)
    {
    }

    /**
        @brief	デストラクタ
     */
    ~UnionFind()
    {
    }

    /**
        @brief	    親のインデックスを取得する

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
        @brief	            右辺と左辺を同じグループとする

        @param[in]  lhs     左辺のインデックス
        @param[in]  rhs     右辺のインデックス
     */
    void Merge(int64_t lhs, int64_t rhs)
    {
        // 先に親まで繋げておく
        int64_t parentL = Find(lhs);
        int64_t parentR = Find(rhs);

        // 同じグループならば何もしない
        if (parentL == parentR)
        {
            return;
        }

        // 片方が親を持たない場合はその配下に入れる
        if (m_data[rhs] == NO_PARENT)
        {
            m_data[rhs] = lhs;
            m_size[rhs] = m_size[lhs] + 1;
            return;
        }
        if (m_data[lhs] == NO_PARENT)
        {
            m_data[lhs] = rhs;
            m_size[lhs] = m_size[rhs] + 1;
            return;
        }

        // その他の場合はサイズが大きいほうに小さい方を入れる
        if (m_size[lhs] > m_size[rhs])
        {
            m_data[rhs] = lhs;
            m_size[lhs] = m_size[rhs] + 1;
            return;
        }
        else
        {
            m_data[lhs] = rhs;
            m_size[rhs] = m_size[lhs] + 1;
            return;
        }
    }

    /**
        @brief	        親が共通かどうか

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

int main()
{
    size_t N, Q;
    std::cin >> N >> Q;

    UnionFind unionfind(N);

    while (Q--)
    {
        int P;
        int64_t A, B;
        std::cin >> P >> A >> B;

        switch (P)
        {
        case 0:
            unionfind.Merge(A, B);
            break;
        case 1:
            if (unionfind.IsSame(A, B))
            {
                std::cout << "Yes" << std::endl;
            }
            else
            {
                std::cout << "No" << std::endl;
            }
            break;
        }
    }

    return 0;
}