#include <iostream>
#include <vector>

using namespace std;

int N,D,K,R;
long best_profit;

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
}

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

int count_max_profit_paths(vector<int>& prices, int K, int R) {
    int D = prices.size();
    vector<vector<long>> dp(D+1, vector<long>(2*K+1, 0));
    dp[0][K] = 1; // condição inicial, estamos no dia 0 com K ações disponíveis e 0 na carteira

    for (int day = 1; day <= D; day++) {
        for (int socks = 0; socks <= 2*K; socks++) {
            // atualizando o número de caminhos que levam ao estado atual (dia e quantidade de ações disponíveis)
            for (int action = -K; action <= K; action++) {
                // testando se é uma ação válida
                if ((action > 0 && socks-action <= 2*K) || (action < 0 && socks+action >= 0)) {
                    int prev_socks = socks-action;
                    long prev_paths = dp[day-1][prev_socks];
                    // se o estado anterior (dia anterior e quantidade de ações disponíveis) é alcançável
                    if (prev_paths > 0) {
                        long& curr_paths = dp[day][socks];
                        // atualizando o número de caminhos que levam ao estado atual
                        curr_paths += prev_paths;
                    }
                }
            }
        }
    }

    // contando o número de caminhos que levam ao lucro máximo (no último dia com 0 na carteira)
    long max_profit = 0;
    for (int p = 0; p < D; p++) {
        max_profit += (long)prices[p];
    }
    int socks = K;
    long count_paths = 0;
    for (int action = -K; action <= K; action++) {
        if (socks+action >= 0 && socks+action <= 2*K) {
            int final_socks = socks+action;
            long final_paths = dp[D][final_socks];
            if (final_paths > 0) {
                int num = abs(action);
                long profit = -num*(prices[D-1]+R) + max_profit;
                if (profit == max_profit) {
                    count_paths += final_paths;
                }
            }
        }
    }

    return count_paths;
}


int main(){
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
        dp=solvetab(prices);
        best_profit = dp[K][0][1];
        int count = 0;
        vector<long> path(D,0);
        count_paths(prices,-1,0,0,path,count);
        printf("%ld %d\n", dp[K][0][1],count);
    }
}