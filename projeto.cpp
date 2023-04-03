#include <iostream>
#include <vector>

using namespace std;

// VERSAO QUE NAO DA ERRO DE EXECUCAO 2 pontos
int maxProfit(const vector<int> &prices, int D, int K, int R)
{
    vector<vector<int>> after(2, vector<int>(K + 1, 0));
    vector<vector<int>> cur(2, vector<int>(K + 1, 0));

    for (int ind = D - 1; ind >= 0; ind--)
    {
        for (int buy = 0; buy <= 1; buy++)
        {
            for (int cap = 1; cap <= K; cap++)
            {
                if (buy == 1)
                {
                    cur[buy][cap] = max(-prices[ind] * cap + after[0][cap], 0 + after[1][cap]);
                    cur[buy][cap] -= R;
                }
                else
                {
                    cur[buy][cap] = max(prices[ind] * cap + after[1][cap - 1], 0 + after[0][cap]);
                }
            }
        }
        after = cur;
    }

    return after[1][K];
}
/* FUNCAO QUE DA ERRO DE EXECUCAO
int maxProfit(const vector<int> &prices, int D, int K, int R)
{
    vector<vector<vector<int>>> dp(D + 1, vector<vector<int>>(2, vector<int>(4, 0)));

    for (int ind = D - 1; ind >= 0; ind--)
    {
        for (int buy = 0; buy <= 1; buy++)
        {
            for (int cap = 1; cap <= K; cap++)
            {
                if (buy == 1)
                {

                    dp[ind][buy][cap] = max(-prices[ind] * cap + dp[ind + 1][0][cap], 0 + dp[ind + 1][1][cap]);
                    dp[ind][buy][cap] -= R;
                }
                else
                {

                    dp[ind][buy][cap] = max(prices[ind] * cap + dp[ind + 1][1][cap - 1], 0 + dp[ind + 1][0][cap]);
                }
            }
        }
    }

    return dp[0][1][3];
} */

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int tipo, N, D, K, R;
    cin >> tipo >> N;
    cin >> D >> K >> R;
    while (N--)
    {

        vector<int> prices(D, 0);
        for (int i = 0; i < D; i++)
        {
            cin >> prices[i];
        }

        cout << maxProfit(prices, D, K, R) << "\n";
    }

    return 0;
}