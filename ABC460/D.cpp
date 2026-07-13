#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>

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
    void Solve();

    //----------- 以下編集の必要なし ----------------------

  public:
    /**
        @brief	各種処理の起点になる窓口
     */
    void Run()
    {
        int64_t numTestCases = 1;
#ifdef DISABLE_MULTICASE
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
#define DISABLE_MULTICASE //!< マルチケース用スイッチ：コメントアウトするとマルチケースになる

#include "../module/Grid2D.cpp"

void AtcoderSolveHelper::Solve()
{
    int64_t H, W;
    In() >> H >> W;
    Grid2D<char> S(H, W, '.');
    In() >> S;
    Grid2D<char> init(S);

    Grid2D<int> searched(H, W, 0);

    auto q = S.GetPositionsQueueByValue('#');

    // 2手目で黒に戻れないやつを白にする
    while (!q.empty())
    {
        auto curPos = q.front();
        q.pop();

        int64_t numBlack = 0;
        int64_t numValid = 0;

        for (char dir : POSITION::GetTenkeyChars())
        {
            auto nextPos = curPos + POSITION::Tenkey(dir);
            if (nextPos.IsInner())
            {
                ++numValid;
                if (*init.GetItr(nextPos.GetIndex()) == '#')
                {
                    ++numBlack;
                }
            }
        }

        if (numBlack == numValid)
        {
            *curPos = '.';
        }
    }

    // 生き残った黒を起点に偶数手目で黒になるマスを検出
    q = S.GetPositionsQueueByValue('#');

    std::queue<int64_t> distQ;
    for (int i = 0; i < q.size(); ++i)
    {
        distQ.push(0);
    }

    while (!q.empty())
    {
        auto curPos = q.front();
        q.pop();
        auto dist = distQ.front();
        distQ.pop();

        if (*searched.GetItr(curPos.GetIndex()) != 0)
        {
            continue;
        }

        *searched.GetItr(curPos.GetIndex()) = 1;
        if (dist % 2 == 0)
        {
            *curPos = '#';
        }

        for (char dir : POSITION::GetTenkeyChars())
        {
            auto nextPos = curPos + POSITION::Tenkey(dir);
            if (nextPos.IsInner() && *searched.GetItr(nextPos.GetIndex()) == 0)
            {
                q.push(nextPos);
                distQ.push(dist + 1);
            }
        }
    }

    for (int y = 0; y < S.GetHeight(); ++y)
    {
        for (int x = 0; x < S.GetWidth(); ++x)
        {
            Out() << S.Ref(x, y);
        }
        Out() << std::endl;
    }
}

//----------------------編集スペースここまで--------------------------

#endif //___INCLUDED_MAIN___