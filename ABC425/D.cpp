#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// #define ENABLE_MULTICASE //!< マルチケース用スイッチ：コメントを外すとマルチケースになる

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
        @brief    Indexの取得

        @param[in]    x       X座標
        @param[in]    y       Y座標

        @return     Index
     */
    int64_t GetIndex(int64_t x, int64_t y) const
    {
        assert(IsInner(x, y));

        return y * m_width + x;
    }

    /**
        @brief        X座標を取得する

        @param[in]    idx     インデックス

        @return     X座標
     */
    int64_t GetX(int64_t idx) const
    {
        assert(0 <= idx && idx < m_height * m_width);

        return idx % m_width;
    }

    /**
        @brief        Y座標を取得する

        @param[in]    idx     インデックス

        @return     Y座標
     */
    int64_t GetY(int64_t idx) const
    {
        assert(0 <= idx && idx < m_height * m_width);

        return idx / m_width;
    }

    /**
        @brief            座標がグリッドの内部か否か

        @param[in]    x       X座標
        @param[in]    y       Y座標

        @retval     true    グリッドの内部にいる
        @retval     false   グリッドの外側
     */
    bool IsInner(int64_t x, int64_t y) const
    {
        return 0 <= x && x < m_width && 0 <= y && y < m_height;
    }

    /**
        @brief        全てのマスに対して操作する

        @tparam     Func    関数の型

        @param[in]    func    操作する関数(引数としてidxとその地点の値が貰える)
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

/**
    @brief	Atcoderの解答を行うのに便利なクラス
 */
class AtcoderSolveHelper
{
private:
    //----------- 編集エリア -----------------------------
    /**
        @brief	実際に問題を解く関数
        @note   マルチケースの場合はケースごとに呼ばれます
     */
    void Solve()
    {
        int H, W;
        In() >> H >> W;
        Grid2D<char> S(H, W, '\0');
        In() >> S;

        std::vector<int64_t> curSt;
        std::vector<int64_t> nextSt;
        S.ForEach([&](int64_t idx, char &val)
                  {
            if(val == '#'){
                curSt.push_back(idx);
            } });

        int RLUD[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        while (!curSt.empty())
        {
            for (auto curIdx : curSt)
            {

                int64_t curX = S.GetX(curIdx);
                int64_t curY = S.GetY(curIdx);

                for (auto &dir : RLUD)
                {
                    int64_t nextX = curX + dir[0];
                    int64_t nextY = curY + dir[1];
                    if (!S.IsInner(nextX, nextY))
                    {
                        continue;
                    }

                    if (S.Ref(nextX, nextY) == '#')
                    {
                        continue;
                    }

                    int numNb = 0;
                    for (auto &d : RLUD)
                    {
                        int64_t newX = nextX + d[0];
                        int64_t newY = nextY + d[1];

                        if (!S.IsInner(newX, newY))
                        {
                            continue;
                        }

                        if (S.Ref(newX, newY) == '#')
                        {
                            ++numNb;
                        }
                    }
                    if (numNb == 1)
                    {
                        nextSt.push_back(S.GetIndex(nextX, nextY));
                    }
                }
            }

            for (auto nx : nextSt)
            {
                int64_t x = S.GetX(nx);
                int64_t y = S.GetY(nx);
                S.Ref(x, y) = '#';
            }

            std::swap(curSt, nextSt);
            nextSt.clear();
        }

        int64_t ans = 0;
        S.ForEach([&](int64_t idx, char &val)
                  {
            if(val == '#'){
                ++ans;
            } });

        Out() << ans << std::endl;

        /*for (int y = 0; y < H; ++y)
        {
            for (int x = 0; x < W; ++x)
            {
                Error() << S.Ref(x, y);
            }
            Error() << std::endl;
        }*/
    }

    //----------- 以下編集の必要なし ----------------------

public:
    /**
        @brief	各種処理の起点になる窓口
     */
    void Run()
    {
        int64_t numTestCases = 1;
#ifdef ENABLE_MULTICASE
        In() >> numTestCases;
#endif
        while (numTestCases--)
        {
            Solve();
        }

        std::cout << Out().str();
    }

private:
    /**
        @brief	対象とするコンテナの各要素に入力を受け取る

        @tparam	TargetContainerType 対象とするコンテナの型
        @param[in]	targetContainer 対象とするコンテナ
     */
    template <class TargetContainerType>
    void EachInput(TargetContainerType &targetContainer)
    {
        for (auto &&target : targetContainer)
        {
            In() >> target;
        }
    }

    /**
        @brief	入力ストリームを取得

        @return 入力ストリーム
     */
    std::istream &In()
    {
        return std::cin;
    }

    /**
        @brief	出力ストリームを取得

        @return 出力ストリーム
     */
    std::stringstream &Out()
    {
        return m_outStream;
    }

    /**
        @brief	エラー出力ストリームを取得

        @return エラー出力ストリーム
     */
    std::ostream &Error()
    {
        return std::cerr;
    }

    /**
        @brief	Yesと1行出力する
     */
    void Yes()
    {
        Out() << "Yes" << std::endl;
    }

    /**
        @brief	Noと1行出力する
     */
    void No()
    {
        Out() << "No" << std::endl;
    }

    /**
        @brief	渡されたbool値に応じてYesかNoを出力する

        @param[in]	isYes Yesを出力するかどうか
     */
    void YesNo(bool isYes)
    {
        if (isYes)
        {
            Yes();
        }
        else
        {
            No();
        }
    }

private:
    std::stringstream m_outStream; //!< 出力を一時的に貯めておけるストリーム
};

/**
    @brief	エントリポイント

    @return ステータスコード(atcoderにおいては基本0)
 */
int main()
{
    AtcoderSolveHelper solver;
    solver.Run();
    return 0;
}