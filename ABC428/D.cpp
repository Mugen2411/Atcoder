#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

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
        std::string Cs, Ds;
        int64_t C, D;
        In() >> Cs >> Ds;
        C = std::stoll(Cs);
        D = std::stoll(Ds);
        std::string CDs = std::to_string(C + D);

        auto _FloorSqrt = [](int64_t n)
        {
            int64_t ans = sqrt(n);
            while (ans * ans > n)
            {
                --ans;
            }
            while ((ans + 1) * (ans + 1) <= n)
            {
                ++ans;
            }
            return ans;
        };
        int64_t mn = 1;
        int64_t mx = 10;
        int64_t lhs = C * 10;
        for (int i = 1; i < Cs.size(); ++i)
        {
            lhs *= 10;
            mn *= 10;
            mx *= 10;
        }

        int64_t ans = 0;
        for (int64_t i = 0; i < 12; ++i)
        {
            if (mn > C + D)
            {
                break;
            }
            int64_t l = std::max(C, mn - 1);
            int64_t h = std::min(C + D, mx - 1);

            ans += _FloorSqrt(lhs + h) - _FloorSqrt(lhs + l);

            mn *= 10;
            mx *= 10;
            lhs *= 10;
        }

        Out() << ans << std::endl;
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