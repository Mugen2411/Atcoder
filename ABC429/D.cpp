#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

// #define ENABLE_MULTICASE //!< マルチケース用スイッチ：コメントを外すとマルチケースになる

#ifndef ___INCLUDED_BINARY_SEARCH___
#define ___INCLUDED_BINARY_SEARCH___

#include <cstdint>

template <class F>
int64_t BinarySearch(int64_t ng, int64_t ok, F comp)
{
    int64_t mid;
    while (std::abs(ng - ok) > 1)
    {
        mid = (ng + ok) / 2;
        if (comp(mid))
        {
            ok = mid;
        }
        else
        {
            ng = mid;
        }
    }
    return ok;
}

#endif //___INCLUDED_BINARY_SEARCH___

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
        int64_t N, M, C;
        In() >> N >> M >> C;
        std::vector<int64_t> A(N);
        EachInput(A);

        std::map<int64_t, int64_t> mp;
        for (auto &a : A)
        {
            ++mp[a];
        }
        std::vector<int64_t> numList;
        for (auto &m : mp)
        {
            numList.push_back(m.second);
        }
        for (auto &m : mp)
        {
            numList.push_back(m.second);
        }
        for (int i = 1; i < numList.size(); ++i)
        {
            numList[i] += numList[i - 1];
        }
        struct ELEM
        {
            int64_t Pos;
            int64_t Num;
        };
        std::vector<ELEM> beg;
        int64_t minP = 0;
        for (auto &m : mp)
        {
            beg.push_back({m.first - minP, m.second});
            minP = m.first;
        }
        beg[0].Pos += M - minP;
        for (int i = 1; i < beg.size(); ++i)
        {
            beg[i].Num += beg[i - 1].Num;
        }

        int64_t ans = 0;

        for (int i = 0; i < beg.size(); ++i)
        {
            int64_t idx = BinarySearch(-1, numList.size(), [&](int64_t cur)
                                       { return numList[cur] - beg[i].Num >= C; });
            ans += beg[i].Pos * (numList[idx] - beg[i].Num);
        }

        Out() << ans;
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