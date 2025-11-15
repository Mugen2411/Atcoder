#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
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
        int64_t N, X, Y;
        In() >> N >> X >> Y;
        struct AREA
        {
            int64_t x, y, w, h;
        };
        std::vector<AREA> cur;
        cur.push_back(AREA{0, 0, X, Y});
        std::vector<AREA> next;

        while (N--)
        {
            char cmd;
            int64_t A, B;
            In() >> cmd >> A >> B;
            if (cmd == 'X')
            {
                for (auto &a : cur)
                {
                    if (a.x <= A && a.x + a.w >= A)
                    {
                        int64_t slice = A - a.x;
                        next.push_back(AREA{a.x, a.y + B, a.w - slice, a.h});
                        next.push_back(AREA{a.x + slice, a.y - B, slice, a.h});
                    }
                    else
                    {
                        next.push_back(a);
                    }
                }
            }
            else
            {
                for (auto &a : cur)
                {
                    if (a.y <= A && a.y + a.h >= A)
                    {
                        int64_t slice = A - a.y;
                        next.push_back(AREA{a.x + B, a.y, a.w - slice, a.h});
                        next.push_back(AREA{a.x - B, a.y + slice, a.w, slice});
                    }
                    else
                    {
                        next.push_back(a);
                    }
                }
            }
            cur = next;
            next.clear();
        }

        int64_t sz = cur.size();
        std::vector<int> searched(sz, -1);
        std::unordered_map<int64_t, int64_t> ans;
        auto dfs = [&](auto self, int64_t idx, int64_t gp)
        {
            if (searched[idx] != -1)
            {
                return;
            }
            searched[idx] = gp;
            AREA me = cur[idx];
            for (int64_t i = 0; i < sz; ++i)
            {
                if (i != idx && searched[i] == -1)
                {
                    AREA c = cur[i];
                    bool xTouch = me.x >= c.x && me.x <= c.x + c.w && c.y >= me.y && c.y <= me.y + me.h;
                    bool yTouch = me.y >= c.y && me.y <= c.y + c.h && c.x >= me.y && c.x <= me.x + me.w;
                    if (xTouch || yTouch)
                    {
                        ans[gp] += c.w * c.h;
                        self(self, i, gp);
                    }
                }
            }
        };
        for (int64_t g = 0; g < sz; g++)
        {
            dfs(dfs, g, g);
        }

        std::vector<int64_t> ans2;
        for (auto &g : ans)
        {
            ans2.push_back(g.second);
        }
        std::sort(ans2.begin(), ans2.end());
        for (auto i : ans2)
        {
            Out() << i << ' ';
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