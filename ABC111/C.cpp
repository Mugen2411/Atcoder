#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

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
        int N;
        In() >> N;
        N /= 2;
        std::vector<int> V1(N);
        std::vector<int> V2(N);
        std::unordered_map<int, int> N1;
        std::unordered_map<int, int> N2;
        N1[0] = 0;
        N2[0] = 0;
        for (int i = 0; i < N; i++)
        {
            In() >> V1[i];
            In() >> V2[i];
            ++N1[V1[i]];
            ++N2[V2[i]];
        }

        int val1 = -1;
        int val2 = -1;
        int ans1 = 0;
        int ans2 = 0;
        for (int i = 0; i < N; ++i)
        {
            if (ans1 < N1[V1[i]])
            {
                ans1 = N1[V1[i]];
                val1 = V1[i];
            }
            if (ans2 < N2[V2[i]])
            {
                ans2 = N2[V2[i]];
                val2 = V2[i];
            }
        }

        if (val1 == val2)
        {
            int64_t val21 = -1;
            int64_t val22 = -1;
            int64_t ans21 = 0;
            int64_t ans22 = 0;

            for (int i = 0; i < N; ++i)
            {
                if (ans21 < N1[V1[i]] && V1[i] != val1)
                {
                    ans21 = N1[V1[i]];
                    val21 = V1[i];
                }
                if (ans22 < N2[V2[i]] && V2[i] != val2)
                {
                    ans22 = N2[V2[i]];
                    val22 = V2[i];
                }
            }

            if (ans1 + ans22 < ans21 + ans2)
            {
                ans1 = ans21;
            }
            else
            {
                ans2 = ans22;
            }
        }

        Out() << (N - ans1) + (N - ans2) << std::endl;
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