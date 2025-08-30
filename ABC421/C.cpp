#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

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
        std::string S;
        In() >> S;

        std::vector<int64_t> A;
        std::vector<int64_t> B;

        for (int i = 0; i < 2 * N; ++i)
        {
            if (S[i] == 'A')
            {
                A.push_back(i);
            }
            else
            {
                B.push_back(i);
            }
        }

        auto Calc = [&](std::vector<int64_t> &a, std::vector<int64_t> &b)
        {
            int64_t retval = 0;
            for (int i = 0; i < a.size(); ++i)
            {
                retval += std::abs(a[i] - b[i]);
            }
            return retval;
        };

        std::vector<int64_t> A2 = A;
        std::vector<int64_t> B2 = B;

        {
            auto itr = std::remove_if(A2.begin(), A2.end(), [](const int64_t cur)
                                      { return cur % 2 == 1; });
            A2.erase(itr, A2.end());
        }
        {
            auto itr = std::remove_if(B2.begin(), B2.end(), [](const int64_t cur)
                                      { return cur % 2 == 0; });
            B2.erase(itr, B2.end());
        }

        int64_t score1 = Calc(A2, B2);

        std::vector<int64_t> A3 = A;
        std::vector<int64_t> B3 = B;

        {
            auto itr = std::remove_if(A3.begin(), A3.end(), [](const int64_t cur)
                                      { return cur % 2 == 0; });
            A3.erase(itr, A3.end());
        }
        {
            auto itr = std::remove_if(B3.begin(), B3.end(), [](const int64_t cur)
                                      { return cur % 2 == 1; });
            B3.erase(itr, B3.end());
        }
        int64_t score2 = Calc(A3, B3);

        Out() << std::min(score1, score2);
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