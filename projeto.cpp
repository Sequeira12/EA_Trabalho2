#include <iostream>
#include <vector>

using namespace std;
int K = 0, R = 0;

int solvetab(vector<int> &prices)
{
    int n = prices.size();

    vector<vector<int>> dp(n + 1, vector<int>(2, 0));

    for (int index = n - 1; index >= 0; index--)
    {
        for (int buy = 0; buy <= 1; buy++)
        {
            int profit = 0;

            if (buy)
            {
                int BuyKaro = -prices[index] * K + dp[index + 1][0] - K * R;
                int skipKaro = 0 + dp[index + 1][1];
                profit = max(BuyKaro, skipKaro);
            }
            else
            {
                int sellKaro = prices[index] * K + dp[index + 1][1];
                int skipKaro = 0 + dp[index + 1][0];
                profit = max(sellKaro, skipKaro);
            }
            dp[index][buy] = profit;
        }
    }
    return dp[0][1];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int tipo, N, D;
    cin >> tipo >> N;
    cin >> D >> K >> R;
    while (N--)
    {

        vector<int> prices(D, 0);
        for (int i = 0; i < D; i++)
        {
            cin >> prices[i];
        }

        printf("%d\n", solvetab(prices));
    }

    return 0;
}