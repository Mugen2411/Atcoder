﻿#include <iostream>
#include <string>
#include <sstream>

#include <algorithm>
#include <vector>
#include <unordered_map>

#define ENABLE_MULTICASE //!< マルチケース用スイッチ：コメントを外すとマルチケースになる

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
        int N;
        In() >> N;
        std::vector<int64_t> A(N);
        std::unordered_map<int64_t, std::pair<int64_t, int64_t>> dict;
        EachInput(A);
        for (auto &a : A)
        {
            if (a < 0)
            {
                ++dict[std::abs(a)].first;
            }
            else
            {
                ++dict[std::abs(a)].second;
            }
        }

        if (A.size() <= 2)
        {
            Yes();
            return;
        }
        if (dict.size() == 1)
        {
            auto top = dict.begin();
            YesNo((top->second.first) == 0 || (top->second.second) == 0 || std::abs((top->second.first) - (top->second.second)) <= 1);
            return;
        }
        std::sort(A.begin(), A.end(), [](const int64_t &lhs, const int64_t &rhs)
                  { return std::abs(lhs) < std::abs(rhs); });

        bool isValid = true;
        std::unordered_map<int64_t, int64_t> mult;
        for (int i = 1; i < N - 1; ++i)
        {
            if (A[i - 1] * A[i + 1] != A[i] * A[i])
            {
                isValid = false;
                break;
            }
            else
            {
                ++mult[A[i] * A[i]];
            }
        }
        YesNo(isValid);
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