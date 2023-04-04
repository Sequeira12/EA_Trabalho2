#include <iostream>
#include <vector>

using namespace std;

// VERSAO QUE NAO DA ERRO DE EXECUCAO 2 pontos
/* int maxProfit(const vector<int> &prices, int D, int K, int R)
{
    vector<int> after(2, vector<int>(K + 1, 0));
    vector<int> cur(2, vector<int>(K + 1, 0));

    for (int ind = D - 1; ind >= 0; ind--)
    {
        for (int buy = 0; buy <= 1; buy++)
        {
            for (int cap = 0; cap <= K; cap++)
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
} */
// FUNCAO QUE DA ERRO DE EXECUCAO
int maxProfit2(vector<int> &prices, int n)
{
    // Write your code here.
    vector<vector<int>> dp(n + 1, vector<int>(5, -1));
    for (int i = 0; i <= 4; i++)
    {
        dp[n][i] = 0;
    }
    for (int i = 0; i <= n; i++)
    {
        dp[i][4] = 0;
    }
    for (int ind = n - 1; ind >= 0; ind--)
    {
        for (int ts = 3; ts >= 0; ts--)
        {
            if (ts % 2 == 0)
            {
                dp[ind][ts] = max(-prices[ind] * 3 + dp[ind + 1][ts + 1], dp[ind + 1][ts]) - 10;
            }
            else
            {
                dp[ind][ts] = max(prices[ind] * 3 + dp[ind + 1][ts + 1], dp[ind + 1][ts]);
            }
        }
    }
    return dp[0][0];
}

int solver(int i, int trans, vector<int> &prices)
{
    if (i == prices.size() || trans == 4)
    {
        return 0;
    }
    int profit;
    if (trans % 2 == 0)
    {
        profit = max(-prices[i] * 3 + solver(i + 1, trans + 1, prices), solver(i + 1, trans, prices)) - 10;
    }
    else
    {
        profit = max(prices[i] * 3 + solver(i + 1, trans + 1, prices), solver(i + 1, trans, prices));
    }
    return profit;
}
int maxProfit(vector<int> &prices)
{
    return solver(0, 0, prices);
}

/* int f2(int ind, int ts, int n, vector<int> &prices, vector<vector<int>> &dp, int comprei)
{
    // base cases
    if (ind == n || ts == 4)
        return 0;
    if (dp[ind][ts] != -1)
        return dp[ind][ts];
    if (ts == 0)
    {

        dp[ind][ts] = max(-prices[ind] * 3 + f2(ind + 1, ts + 1, n, prices, dp, 1), f(ind + 1, ts, n, prices, dp, 1)) - 10;
        printf("COMPRA(%d): %d -- > %d\n", ind, prices[ind], dp[ind][ts]);
        return dp[ind][ts];
    }
    else if (ts == 1)
    {
        dp[ind][ts] = max(prices[ind] * 3 + f(ind + 1, ts - 1, n, prices, dp, 0), f(ind + 1, ts, n, prices, dp, 0));
        printf("VENDA(%d): %d -- > %d\n", ind, prices[ind], dp[ind][ts]);
        return dp[ind][ts];
    }
    else
    {
        dp[ind][ts] = max(f(ind + 1, 0, n, prices, dp, 0), f(ind + 1, 0, n, prices, dp, 0));
        printf("MANTEVE(%d): %d -- > %d\n", ind, prices[ind], dp[ind][ts]);
        return dp[ind][ts] = f(ind + 1, 0, n, prices, dp, 0);
    }
}*/
int max(vector<int> prices)
{
    int n = prices.size();
    vector<vector<int>> dp(prices.size() + 1, vector<int>(3, 0));
    dp[n][0] = 0;
    dp[n][1] = 0;
    for (int ind = n - 1; ind >= 0; ind--)
    {
        for (int buy = 0; buy <= 2; buy++)
        {
            if (buy == 1)
            {
                dp[ind][buy] = max(-prices[ind] * 3 + dp[ind + 1][0], dp[ind + 1][1]) - 10;
            }

            else
            {
                // printf(" MANTEM(%d) %d %d\n", ind, dp[ind + 1][0], dp[ind + 1][1]);
                dp[ind][buy] = max(+prices[ind] * 3 + dp[ind + 1][1], 0 + dp[ind + 1][0]);
            }
        }
    }
    //  printf("%d %d %d\n", dp[0][0], dp[0][1], dp[0][2]);
    return dp[0][1];
}

int getMaximumProfit(vector<int> &prices, int n)
{
    vector<int> ahead(3, 0), cur(3, 0);
    vector<bool> compra(6, false);
    ahead[0] = ahead[1] = 0;
    bool POSSO = true;
    for (int ind = n - 1; ind >= 0; ind--)
    {
        for (int buy = 0; buy <= 1; buy++)
        {
            int profit = 0;
            if (buy == 1 && compra[ind + 1] == false)
            {

                profit = max(-prices[ind] * 3 + ahead[0], 0 + ahead[1]) - 10;
                compra[ind] = true;
            }
            else
            {
                for (int i = 0; i <= 1; i++)
                {
                    if (i == 0)
                    {
                        profit = max(prices[ind] * 3 + ahead[1], 0 + ahead[0]);
                    }
                }

                cur[buy] = profit;
            }
            ahead = cur;
        }
    }
    for (int i = 0; i < 5; i++)
    {
        cout << compra[i] << endl;
    }
    return ahead[1];
}

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

        printf("%d\n", maxProfit(prices));

        // cout << maxProfit(prices, D, K, R) << "\n";
    }

    return 0;
}