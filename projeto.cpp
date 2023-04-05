#include <iostream>
#include <vector>

using namespace std;
int K = 0, R = 0;
void getTransactionPath(vector<vector<long>> &dp, vector<int> &prices, int index, int buy, vector<long> &path, vector<vector<long>> &paths)
{
    if (index >= prices.size())
    {
        paths.push_back(path);

        return;
    }

    if (buy)
    {
        long BuyKaro = -prices[index] * K + dp[index + 1][0] - K * R;
        long skipKaro = 0 + dp[index + 1][1];
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
        long sellKaro = prices[index] * K + dp[index + 1][1];
        long skipKaro = 0 + dp[index + 1][0];
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

vector<vector<long>> solvetab(vector<int> &prices)
{
    int n = prices.size();

    vector<vector<long>> dp(n + 1, vector<long>(2, 0));

    for (int index = n - 1; index >= 0; index--)
    {
        for (int buy = 0; buy <= 1; buy++)
        {
            long profit = 0;

            if (buy)
            {
                long BuyKaro = -prices[index] * K + dp[index + 1][0] - K * R;
                long skipKaro = 0 + dp[index + 1][1];
                profit = max(BuyKaro, skipKaro);
            }
            else
            {
                long sellKaro = prices[index] * K + dp[index + 1][1];
                long skipKaro = 0 + dp[index + 1][0];
                profit = max(sellKaro, skipKaro);
            }
            dp[index][buy] = profit;
        }
    }

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
        vector<vector<long>> dp(D + 1, vector<long>(2, 0));
        dp = solvetab(prices);
        if (tipo == 1)
        {
            printf("%ld\n", dp[0][1]);
        }
        if (tipo == 2)
        {
            vector<vector<long>> paths;
            vector<long> path;
            getTransactionPath(dp, prices, 0, 1, path, paths);
            vector<long> v = paths[0];
            int contador = 0;
            int valor = 0;
            path = vector<long>(D, 0);
            printf("%ld\n", dp[0][1]);
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
                    printf("%ld\n", path[i]);
                }
                else
                {
                    printf("%ld ", path[i]);
                }
            }
        }
        if (tipo == 3)
        {
            vector<vector<long>> paths;
            vector<long> path;
            getTransactionPath(dp, prices, 0, 1, path, paths);
            vector<long> v = paths[0];
            int contador = 0;
            int valor = 0;
            path = vector<long>(D, 0);
            printf("%ld %lu\n", dp[0][1], paths.size());
        }
    }

    return 0;
}