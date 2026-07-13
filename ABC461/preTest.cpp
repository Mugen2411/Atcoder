#ifndef ___INCLUDED_PRETEST__
#define ___INCLUDED_PRETEST__

#include "preTest.cpp"

#include "../module/Grid2D.cpp"
#include <unordered_map>

#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

#include <iostream>
#include <sstream>
#include <string>

#define DISABLE_MULTICASE //!< マルチケース用スイッチ：コメントアウトするとマルチケースになる

/**
    @brief	Atcoderの解答を行うのに便利なクラス
 */
class AtcoderSolveHelper
{
  private:
    //----------- 編集エリア -----------------------------
    /**
        @brief	実際に問題を解く関数
        @note   マルチケ���スの場合はケースごとに呼ばれます
     */
    void Solve();

    //----------- 以下編集の必要なし ----------------------

  public:
    /**
        @brief	各種処理の起点になる窓口
     */
    void Run()
    {
        int64_t numTestCases = 1;
#ifndef DISABLE_MULTICASE
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

//----------------------編集スペースここから--------------------------

void AtcoderSolveHelper::Solve()
{
    int64_t H, W, K;
    In() >> H >> W >> K;

    Grid2D<char> S(H, W, 0);
    In() >> S;

    Grid2D<int64_t> pres(H + 1, W + 1, 0);

    for (int y = 1; y <= H; ++y)
    {
        for (int x = 0; x < W; ++x)
        {
            pres.Ref(x + 1, y) += pres.Ref(x, y) + S.Ref(x, y - 1) - '0';
        }
    }

    for (int x = 0; x <= W; ++x)
    {
        for (int y = 0; y < H; ++y)
        {
            pres.Ref(x, y + 1) += pres.Ref(x, y);
        }
    }

    auto _GetSum = [&](int64_t x1, int64_t x2, int64_t y1, int64_t y2) {
        return pres.Ref(x2, y2) - pres.Ref(x2, y1) - pres.Ref(x1, y2) + pres.Ref(x1, y1);
    };

    int64_t ans = 0;
    for (int x1 = 0; x1 < W; ++x1)
    {
        for (int x2 = x1 + 1; x2 <= W; ++x2)
        {
            int64_t wSolid = _GetSum(x1, x2, 0, H);

            std::unordered_map<int64_t, int64_t> dSolid;

            for (int y = 0; y <= H; ++y)
            {
                ++dSolid[_GetSum(x1, x2, y, H)];
            }
            for (int y1 = 0; y1 <= H; ++y1)
            {
                int64_t uSolid = _GetSum(x1, x2, 0, y1);
                ans += dSolid[wSolid - uSolid - K];
            }
        }
    }

    Out() << ans;
}

//----------------------編集スペースここまで--------------------------

#endif //___INCLUDED_MAIN___
#endif //___INCLUDED_PRETEST__