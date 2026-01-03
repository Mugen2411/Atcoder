#ifndef ___INCLUDED_COMBINATION___
#define ___INCLUDED_COMBINATION___

class Combination
{
  public:
    //! @brief 組み合わせ(nCr)を計算する
    //! @param n 母数
    //! @param r 選択数
    //! @return nCrの結果
    static int64_t Calc(int64_t n, int64_t r)
    {
        int64_t ans = 1;
        for (int i = 0; i < r; ++i)
        {
            ans *= (n - i);
            ans /= (i + 1);
        }
        return ans;
    }
};

#endif //___INCLUDED_COMBINATION___