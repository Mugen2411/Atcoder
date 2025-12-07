#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#ifndef __INCLUDED_GRID2D__
#define __INCLUDED_GRID2D__

#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

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

#include <algorithm>
#include <vector>

// #define ENABLE_MULTICASE //!< マルチケース用スイッチ：コメントを外すとマルチケースになる

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
        Grid2D<int> C(3, 3, -1);
        In() >> C;

        std::vector<int> order;
        for (int i = 0; i < 9; ++i)
        {
            order.push_back(i);
        }

        int bingo[][2][2] = {
            {{0, 1}, {0, 2}},  {{0, -1}, {0, -2}},   {{1, 0}, {2, 0}},   {{-1, 0}, {-2, 0}},
            {{1, 1}, {2, 2}},  {{-1, -1}, {-2, -2}}, {{-1, 1}, {-2, 2}}, {{1, -1}, {2, -2}},
            {{1, 0}, {-1, 0}}, {{0, 1}, {0, -1}},    {{1, 1}, {-1, -1}}, {{-1, 1}, {1, -1}},
        };
        int64_t all = 0;
        int64_t ans = 0;
        do
        {
            Grid2D<int> isFound(3, 3, 0);
            bool isSad = false;

            for (auto &o : order)
            {
                int64_t curX = isFound.GetX(o);
                int64_t curY = isFound.GetY(o);
                isFound.Ref(curX, curY) = 1;

                for (auto &b : bingo)
                {
                    bool isValid = true;
                    for (auto &i : b)
                    {
                        if (!isFound.IsInner(curX + i[0], curY + i[1]) || isFound.Ref(curX + i[0], curY + i[1]) == 0)
                        {
                            isValid = false;
                            break;
                        }
                    }
                    if (!isValid)
                    {
                        continue;
                    }
                    if (C.Ref(curX + b[0][0], curY + b[0][1]) == C.Ref(curX + b[1][0], curY + b[1][1]) &&
                        C.Ref(curX + b[0][0], curY + b[0][1]) != C.Ref(curX, curY))
                    {
                        isSad = true;
                        break;
                    }
                }
                if (isSad)
                {
                    break;
                }
            }
            if (!isSad)
            {
                ++ans;
            }
            ++all;
        } while (std::next_permutation(order.begin(), order.end()));

        Out() << std::fixed << std::setprecision(10) << static_cast<long double>(ans) / all;
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