#include <iostream>
#include <vector>

using namespace std;
int K = 0, R = 0;
void getTransactionPath(vector<vector<int>> &dp, vector<int> &prices, int index, int buy, vector<int> &path, vector<vector<int>> &paths)
{
    if (index >= prices.size())
    {
        paths.push_back(path);

        return;
    }

    if (buy)
    {
        int BuyKaro = -prices[index] * K + dp[index + 1][0] - K * R;
        int skipKaro = 0 + dp[index + 1][1];
        if (BuyKaro >= skipKaro)
        {
            path.push_back(index);
            getTransactionPath(dp, prices, index + 1, 0, path, paths);
            path.pop_back();
        }
        if (skipKaro >= BuyKaro)
        {
            getTransactionPath(dp, prices, index + 1, 1, path, paths);
        }
    }
    else
    {
        int sellKaro = prices[index] * K + dp[index + 1][1];
        int skipKaro = 0 + dp[index + 1][0];
        if (sellKaro >= skipKaro)
        {
            path.push_back(index);
            getTransactionPath(dp, prices, index + 1, 1, path, paths);
            path.pop_back();
        }
        if (skipKaro >= sellKaro)
        {
            getTransactionPath(dp, prices, index + 1, 0, path, paths);
        }
    }
}

vector<vector<int>> solvetab(vector<int> &prices)
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
    vector<vector<int>> paths;
    vector<int> path;
    /*    getTransactionPath(dp, prices, 0, 1, path, paths);
       for (auto &path : paths)
       {
           cout << "Transaction path: ";
           for (auto &index : path)
           {
               cout << index << " ";
           }
           cout << endl;
       } */

    return dp;
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
        vector<vector<int>> dp(D + 1, vector<int>(2, 0));
        dp = solvetab(prices);
        if (tipo == 1)
        {
            printf("%d\n", dp[0][1]);
        }
        if (tipo == 2)
        {
            vector<vector<int>> paths;
            vector<int> path;
            getTransactionPath(dp, prices, 0, 1, path, paths);
            vector<int> v = paths[0];
            int contador = 0;
            int valor = 0;
            path = vector<int>(D, 0);
            printf("%d\n", dp[0][1]);
            for (int i = 0; i < v.size(); i++)
            {

                if (contador == 0)
                {
                    path[v[i]] = K;
                    contador++;
                }
                else
                {
                    path[v[i]] = -K;
                    contador = 0;
                }
            }
            for (int i = 0; i < path.size(); i++)
            {
                if (i == path.size() - 1)
                {
                    printf("%d\n", path[i]);
                }
                else
                {
                    printf("%d ", path[i]);
                }
            }
        }
        if (tipo == 3)
        {
            vector<vector<int>> paths;
            vector<int> path;
            getTransactionPath(dp, prices, 0, 1, path, paths);
            vector<int> v = paths[0];
            int contador = 0;
            int valor = 0;
            path = vector<int>(D, 0);
            printf("%d %lu\n", dp[0][1], paths.size());
        }
    }

    return 0;
}