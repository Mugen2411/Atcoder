#include <iostream>
#include <string>
#include <sstream>
#include <map>

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
        int64_t N;
        In() >> N;

        std::map<int64_t, int64_t> mp;
        mp.insert({0, 0});
        int64_t sum = 0;

        while (N--)
        {
            int64_t A;
            In() >> A;

            auto res = mp.insert({A, 0});
            auto itr = res.first;

            auto _Update = [&mp, &sum](decltype(mp)::iterator cur)
            {
                if (cur == mp.end())
                {
                    return;
                }
                auto next = ++cur;
                --cur;

                if (cur != mp.begin())
                {
                    auto prev = --cur;
                    ++cur;

                    if (next == mp.end())
                    {
                        int64_t ld = std::abs(prev->first - cur->first);

                        sum -= cur->second;
                        cur->second = ld;
                        sum += cur->second;
                    }
                    else
                    {
                        int64_t ld = std::abs(prev->first - cur->first);
                        int64_t rd = std::abs(next->first - cur->first);

                        sum -= cur->second;
                        cur->second = std::min(ld, rd);
                        sum += cur->second;
                    }
                }
                else
                {
                    int64_t rd = std::abs(next->first - cur->first);

                    sum -= cur->second;
                    cur->second = rd;
                    sum += cur->second;
                }
            };

            auto next = ++itr;
            auto cur = --itr;
            auto prev = --itr;

            _Update(next);
            _Update(prev);
            _Update(cur);

            Out() << sum << std::endl;
        }
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