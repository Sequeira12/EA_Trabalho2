#include <iostream>
#include <vector>

using namespace std;
int K = 0, R = 0, N=0,D=0;

long best_profit;

void count_paths(vector<int>&prices,int day,int socks,int transaction, vector <long>&path, int &contador_paths){
    if(day==D-1){
         if(transaction>0 && transaction!=0&& transaction+socks>K) return;
        //venda invalida
        if (transaction<0 && transaction!=0 && socks<-1*transaction) return;

        socks+=transaction;
        path[day]=transaction;

        if(socks!=0) return;

        //calculamos o lucro
        long profit=0;
        for (int p=0;p<D;p++){
            int num = abs(path[p]);
            //venda
            if(path[p]<0){
                profit+=num*prices[p];
            }

            //compra
            else if (path[p]>0){
                profit-=num*(prices[p]+R);
            }
        }
        // cout << profit << endl;
        if(profit==best_profit) {
            // for (int i=0;i<D;i++){
            //     cout<< path[i] << " ";
            // }
            // cout << endl;

            contador_paths+=1;

            // cout << "find path" << endl;
        }
        path[day]=0;
        socks-=transaction;
        return;
    }
    else {
        //inicio
        if(day==-1){
            //testar não fazer nada
            count_paths(prices,0,socks,0,path,contador_paths);

            //testar comprar ou vender
            for (int i=1;i<=K;i++){
                //comprar
                count_paths(prices,0,socks,i,path,contador_paths);

                //vender
                count_paths(prices,0,socks,-1*i,path,contador_paths);
            }
        }
        else{
        //compra invalida 
        if(transaction>0 && transaction+socks>K) return;
        //venda invalida
        if (transaction<0 && socks<-1*transaction) return;


        //atualizar carteira
        socks+=transaction;

        path[day]=transaction;

         //testar não fazer nada
            count_paths(prices,day+1,socks,0,path,contador_paths);

            //testar comprar ou vender
            for (int i=1;i<=K;i++){
                //comprar
                count_paths(prices,day+1,socks,i,path,contador_paths);

                //vender
                count_paths(prices,day+1,socks,-1*i,path,contador_paths);
            }

        path[day]=0;
        socks-=transaction;
        }

    }
}

void getTransactionPath(vector<vector<vector<long>>> &dp, vector<int> &prices, int index, int buy, int k, vector<long> &path, vector<vector<long>> &paths)
{
    if (index >= prices.size())
    {
        paths.push_back(path);


        // for(int i=0;i<paths.size();i++){
        //     for (int j=0;j<paths[i].size();j++){
        //         cout << paths[i][j] << " ";
        //     }
        //     cout << endl;
        // }

        // cout << endl << endl;

        vector<long> p;
        if(k!=K) getTransactionPath(dp, prices, 0, 1, k+1,p, paths);
        return;
    }

    if (buy)
    {
        long BuyKaro = -prices[index] * k + dp[k][index + 1][0] - k * R;
        long skipKaro = 0 + dp[k][index + 1][1];
        if (BuyKaro >= skipKaro)
        {
            path.push_back(index);
            getTransactionPath(dp, prices, index + 1, 0, k,path, paths);
            path.pop_back();
        }
        if (skipKaro >= BuyKaro)
        {
            getTransactionPath(dp, prices, index + 1, 1, k,path, paths);
        }
    }
    else
    {
        long sellKaro = prices[index] * k + dp[k][index + 1][1];
        long skipKaro = 0 + dp[k][index + 1][0];
        if (sellKaro >= skipKaro)
        {
            path.push_back(index);
            getTransactionPath(dp, prices, index + 1, 1,k, path, paths);
            path.pop_back();
        }
        if (skipKaro >= sellKaro)
        {
            getTransactionPath(dp, prices, index + 1, 0,k, path, paths);
        }
    }
}
 vector<vector<vector<long>>> solvetab(vector<int> &prices)
{
    int n = prices.size();

    vector<vector<vector<long>>> dp(K+ 1, vector<vector<long>>(n+1,vector<long>(2, 0)));

    for(int k=1;k<=K;k++){
        for (int index = n - 1; index >= 0; index--)
        {
            for (int buy = 0; buy <= 1; buy++)
            {
                long profit = 0;

                if (buy)
                {
                    long BuyKaro = -prices[index] * k + dp[k][index + 1][0] - k * R;
                    long skipKaro = 0 + dp[k][index + 1][1];
                    profit = max(BuyKaro, skipKaro);
                }
                else
                {
                    long sellKaro = prices[index] * k + dp[k][index + 1][1];
                    long skipKaro = 0 + dp[k][index + 1][0];
                    profit = max(sellKaro, skipKaro);
                }

                dp[k][index][buy] = profit;
            }
        }
    }

    return dp;

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

    // return dp;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int tipo;
    cin >> tipo >> N;
    cin >> D >> K >> R;
    while (N--)
    {

        vector<int> prices(D, 0);
        for (int i = 0; i < D; i++)
        {
            cin >> prices[i];
        }
        vector<vector<vector<long>>> dp(K+ 1, vector<vector<long>>(D+1,vector<long>(2, 0)));
        dp = solvetab(prices);
        best_profit=dp[K][0][1];
        if (tipo == 1)
        {
            printf("%ld\n", dp[K][0][1]);
        }
        if (tipo == 2)
        {
            vector<vector<long>> paths;
            vector<long> path;
            getTransactionPath(dp, prices, 0, 1,3, path, paths);
            vector<long> v = paths[0];
            int contador = 0;
            int valor = 0;
            path = vector<long>(D, 0);
            printf("%ld\n", dp[K][0][1]);
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
            // vector<vector<long>> paths;
            // vector<long> path;
            // //getTransactionPath(dp, prices, 0, 1,3, path, paths);
            // vector<long> v = paths[0];
            // int contador = 0;
            // int valor = 0;
            int count = 0;
            vector<long> path(D,0);
            count_paths(prices,-1,0,0,path,count);
            printf("%ld %d\n", dp[K][0][1],count);
        }
    }

    return 0;
}