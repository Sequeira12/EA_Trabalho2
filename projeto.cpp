#include <iostream>
#include <vector>

using namespace std;
int K = 0, R = 0, N = 0, D = 0;

long best_profit;
int MOD = 1e9 + 7;
void count_p(int &count, vector<vector<vector<int>>> &aux, int visited, int day, vector<vector<int>> &dp) {
    if (day == 0) {
        count = (count+1) % MOD;
        return;
    }

    //ja foi calculado
    if (dp[visited][day] != -1) {
        count = (count + dp[visited][day]) % MOD;
        return;
    }

    int sub_count = 0;
    for (int i = 0; i < aux[day][visited].size(); i++) {
        count_p(sub_count, aux, aux[day][visited][i], day - 1, dp);
    }
    dp[visited][day] = sub_count;
    count = (count + sub_count) %MOD;
}
void make_paths(vector<int> &prices, int &count){
    //dp com dia/numero de açoes na carteira
    vector<vector<long>> dp (D,vector<long>(K+1,0));
    vector<vector<vector<int>>> aux;

    int n=prices.size();

    vector<vector<int>> day;
    for(int k=0;k<=K;k++){
        dp[0][k]=-prices[0]*k - k * R;
        day.push_back({-1});
    }
    aux.push_back(day);

    for (int i=1;i<D;i++){
        vector<vector<int>> day;
        for(int k=0;k<=K;k++){     //k=1
            if(i==D-1 && k==1) break; 
            vector<int> lucros_maximos;
            long best=INT8_MIN;
            for(int ka=0;ka<=K;ka++){ //o que tinhamos no dia anterior=
                long profit;
                //mantem
                if(k-ka==0){ //dia anterior tinhamos 1 fi
                    profit=dp[i-1][ka];
                }

                //venda
                else if(k-ka<0){
                    profit=dp[i-1][ka] + abs(k-ka) * prices[i];
                }

                //compra
                else if(k-ka>0){
                    profit=dp[i-1][ka] - (k-ka) * prices[i] - (k-ka)*R;
                }

                if(profit>best){
                    best=profit;
                    lucros_maximos.clear();
                    lucros_maximos.push_back(ka);
                }

                else if (profit==best){
                    lucros_maximos.push_back(ka);
                }
            }
            
            dp[i][k]=best;

            day.push_back(lucros_maximos);
        }
        aux.push_back(day);
    }

    vector<vector<int>> dp_memo(K+1,vector<int>(D,-1));
    count_p(count,aux,0,D-1,dp_memo);
    printf("%ld %d\n", dp[D-1][0], count);
}

void count_paths(vector<int>&prices,int day,int socks,int transaction, vector <long>&path, int &contador_paths, int profit){
    if(day==D-1){
         if(transaction>0 && transaction!=0&& transaction+socks>K) return;
        //venda invalida
        if (transaction<0 && transaction!=0 && socks<-1*transaction) return;

        socks+=transaction;
        path[day]=transaction;

        if(socks!=0) return;
        
        int num = abs(transaction);
        //venda
        if(transaction<0) profit+=num*prices[day];
        //compra
        else if (transaction>0) profit-=num*(prices[day]+R);
    
        // // //calculamos o lucro
        // for (int i=0;i<D;i++){
        //     cout<< path[i] << " ";
        // }
        // cout << endl;

        if(profit==best_profit) {
             for (int i=0;i<D;i++){
            cout<< path[i] << " ";
        }
        cout << endl;
            contador_paths+=1;
        }

        //     // cout << "find path" << endl;
        // }
        path[day]=0;
        socks-=transaction;
        return;
    }
    else {
        //inicio
        if(day==-1){
            //testar não fazer nada
            count_paths(prices,0,socks,0,path,contador_paths,profit);

            //testar comprar ou vender
            for (int i=1;i<=K;i++){
                //comprar
                count_paths(prices,0,socks,i,path,contador_paths,profit);

                //vender
                count_paths(prices,0,socks,-1*i,path,contador_paths,profit);
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

        int num = abs(transaction);
        //venda
        if(transaction<0){
            profit+=num*prices[day];
        }

            //compra
        else if (transaction>0) profit-=num*(prices[day]+R);

        long best=0;
                
            //testar não fazer nada
            count_paths(prices,day+1,socks,0,path,contador_paths,profit);

            //testar comprar ou vender
            for (int i=1;i<=K;i++){
                //comprar
                count_paths(prices,day+1,socks,i,path,contador_paths,profit);

                //vender
                count_paths(prices,day+1,socks,-1*i,path,contador_paths,profit);
            }

        path[day]=0;
        socks-=transaction;
        }
    }
}
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

    return dp;
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
        vector<vector<long>> dp(D + 1, vector<long>(2, 0));
        if (tipo == 1)
        {
            dp = solvetab(prices);
            best_profit = dp[0][1];
            printf("%ld\n", dp[0][1]);
        }
        if (tipo == 2)
        {
            dp = solvetab(prices);
            best_profit = dp[0][1];
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
            int count = 0;
            vector<long> path(D, 0);
            make_paths(prices,count);
        }
    }
    return 0;
}
