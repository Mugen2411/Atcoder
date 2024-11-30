#ifndef __INCLUDED_GRID2D__
#define __INCLUDED_GRID2D__

#include <vector>
#include <cassert>
#include <cstdint>
#include <iostream>

/**
    @brief    二次元のグリッドを表すクラス

    @tparam    T   格納する型
 */
template <class T>
class Grid2D
{
public:
    /**
        @brief    コンストラクタ

        @param[in]    height          高さ
        @param[in]    width           幅
        @param[in]    initialValue    初期値
    */
    Grid2D(int64_t height, int64_t width, T initialValue)
        : m_data(height * width, initialValue), m_width(width), m_height(height)
    {
    }

    /**
        @brief            指定した座標の値にアクセスする

        @param[in]    x   X座標
        @param[in]    y   Y座標

        @return         目的の座標の参照
     */
    T &Ref(int64_t x, int64_t y)
    {
        return m_data[GetIndex(x, y)];
    }

    /**
        @brief    高さの取得

        @return 高さ
     */
    int64_t GetHeight() const
    {
        return m_height;
    }

    /**
        @brief    幅の取得

        @return 幅
     */
    int64_t GetWidth() const
    {
        return m_width;
    }

    /**
        @brief	Indexの取得

        @param[in]	x       X座標
        @param[in]	y       Y座標
        @return     Index
     */
    int64_t GetIndex(int64_t x, int64_t y) const
    {
        assert(IsInner(x, y));

        return y * m_width + x;
    }

    /**
        @brief	    X座標を取得する

        @param[in]	idx     インデックス
        @return     X座標
     */
    int64_t GetX(int64_t idx) const
    {
        assert(0 <= idx && idx < m_height * m_width);

        return idx % m_width;
    }

    /**
        @brief	    Y座標を取得する

        @param[in]	idx     インデックス
        @return     Y座標
     */
    int64_t GetY(int64_t idx) const
    {
        assert(0 <= idx && idx < m_height * m_width);

        return idx / m_width;
    }

    /**
        @brief	        座標がグリッドの内部か否か

        @param[in]	x       X座標
        @param[in]	y       Y座標

        @retval     true    グリッドの内部にいる
        @retval     false   グリッドの外側
     */
    bool IsInner(int64_t x, int64_t y) const
    {
        return 0 <= x && x < m_width && 0 <= y && y < m_height;
    }

    /**
        @brief	    全てのマスに対して操作する

        @tparam 	Func    関数の型

        @param[in]	func    操作する関数(引数としてidxとその地点の値が貰える)
     */
    template <class Func>
    void ForEach(Func func)
    {
        for (int i = 0; i < m_width * m_height; ++i)
        {
            func(i, m_data[i]);
        }
    }

private:
    std::vector<T> m_data; //!< 本体となる配列
    int64_t m_width;       //!< 幅
    int64_t m_height;      //!< 高さ

    template <class U>
    friend std::istream &operator>>(std::istream &stream, Grid2D<U> &dest);
};

/**
    @brief            入力ストリーム演算子

    @tparam    T       Grid2Dに格納する型
    @param[in]        stream  入力ストリーム
    @param[in]        dest    入力を受け付ける先のGrid2D
    @return                 入力ストリーム
 */
template <class T>
std::istream &operator>>(std::istream &stream, Grid2D<T> &dest)
{
    for (int64_t y = 0; y < dest.m_height; ++y)
    {
        for (int64_t x = 0; x < dest.m_width; ++x)
        {
            stream >> dest.Ref(x, y);
        }
    }
    return stream;
}

#endif //__INCLUDED_GRID2D__

#include <iostream>
#include <vector>
#include <unordered_map>

int main()
{
    int64_t H, W;
    std::cin >> H >> W;
    Grid2D<char> A(H, W, '.');
    std::cin >> A;
    int64_t N;
    std::cin >> N;
    struct Medicine
    {
        int64_t idx;
        int64_t Y;
        int64_t X;
        int64_t E;
    };

    // スタート地点とゴール地点のidxを拾う
    int64_t startIdx = -1, goalIdx = -1;
    A.ForEach([&](int64_t idx, char val)
              {
        if(val == 'S')
        {
            startIdx = idx;
        }
        if(val == 'T')
        {
            goalIdx = idx;
        } });

    std::unordered_map<int64_t, int64_t> idxToM;
    std::vector<Medicine> M(N);
    for (int i = 0; i < N; ++i)
    {
        int64_t Y, X, E;
        std::cin >> Y >> X >> E;
        --Y, --X;
        M[i].idx = A.GetIndex(X, Y);
        M[i].Y = Y;
        M[i].X = X;
        M[i].E = E;
        idxToM[M[i].idx] = i;
    }

    int64_t startM = -1;
    // スタート地点に薬が置いてなかったらNo
    if (idxToM.count(startIdx) == 0)
    {
        std::cout << "No" << std::endl;
        return 0;
    }
    else
    {
        startM = idxToM[startIdx];
    }

    int64_t goalM = -1;
    if (idxToM.count(goalIdx) == 0)
    {
        // ゴール地点に薬が無いならカスの薬として登録する
        M.push_back({goalIdx, A.GetY(goalIdx), A.GetX(goalIdx), 0});
        idxToM[goalIdx] = N;
        goalM = N;
    }
    else
    {
        goalM = idxToM[goalIdx];
    }

    struct Path
    {
        int64_t toIdx;
    };
    std::vector<std::vector<Path>> graph(M.size());
    Grid2D<int64_t> searched(H, W, -1);

    int64_t RLDU[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    // それぞれの薬から次の薬まで到達できるなら繋げる
    // mは薬のインデックス(0～N)
    auto dfs = [&](auto self, int64_t m, int64_t x, int64_t y, int64_t dist)
    {
        if (dist > M[m].E + 1)
        {
            return;
        }
        int64_t myIdx = M[m].idx;
        int64_t idx = A.GetIndex(x, y);
        if (idx != myIdx && idxToM.count(idx) != 0)
        {
            graph[m].push_back({idxToM[idx]});
        }
        searched.Ref(x, y) = m;

        for (auto &dir : RLDU)
        {
            int64_t nextX = x + dir[0];
            int64_t nextY = y + dir[1];
            if (A.IsInner(nextX, nextY) && A.Ref(nextX, nextY) != '#' && searched.Ref(nextX, nextY) != m)
            {
                self(self, m, nextX, nextY, dist + 1);
            }
        }
    };

    for (int i = 0; i < N; ++i)
    {
        dfs(dfs, i, M[i].X, M[i].Y, 0);
    }

    std::vector<bool> searched2(M.size(), false);
    auto dfs2 = [&](auto self, int64_t cur) -> void
    {
        searched2[cur] = true;
        for (auto p : graph[cur])
        {
            if (!searched2[p.toIdx])
            {
                self(self, p.toIdx);
            }
        }
    };

    dfs2(dfs2, startM);

    if (searched2[goalM])
    {
        std::cout << "Yes" << std::endl;
    }
    else
    {
        std::cout << "No" << std::endl;
    }

    return 0;
}