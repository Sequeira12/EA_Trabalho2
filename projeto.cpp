#include <stdio.h>
#include <vector>
#include <iostream>
using namespace std;

vector<int> Vi;
int N;
int D;
int K;
int R;

int numeroVezes;
int tipo;
int valor;
vector<bool> comprou;
int menor = 10000000, maior = -1;
vector<vector<int>> dp;
int prof = 0;
vector<int> aux;
int contador = 0;
void calcula(int valor, int k, int contamenores, int Profit, int compra, vector<int> &Comb)
{

    int prox = k + 1;

    if (k == Vi.size() && valor == 0)
    {
        int g = 0;
        for (int i = 0; i < Comb.size(); i++)
        {

            g += (-Comb[i] * Vi[i]);
        }

        int Money = g + (-K * (compra)) * R;

        if (prof == Money)
        {
            aux = Comb;
            contador++;
        }
        if (prof < Money)
        {
            aux = Comb;
            prof = Money;
            contador = 1;
        }
        return;
    }

    if (Vi[k] == menor)
    {

        if (valor <= K && valor >= -K)
        {

            if (contamenores != 1)
            {

                for (int i = 0; i <= contamenores; i++)
                {
                    Profit += Vi[k] * (-i);
                    if (i != 0 && (valor + i) >= -K && (valor + i) <= -K)
                    {
                        Comb[k] = i;
                        calcula(valor + i, prox, contamenores - 1, Profit, compra, Comb);
                    }
                    else
                    {
                        Comb[k] = i;
                        calcula(valor + i, prox, contamenores, Profit, compra, Comb);
                    }
                }
            }
            else
            {
                Comb[k] = K;
                calcula(valor + K, prox, 0, Profit, compra, Comb);
            }
        }
        else
        {
            Comb[k] = 0;
        }
    }
    else
    {
        int soma = 0;
        for (int i = 0; i < k; i++)
        {
            soma += Comb[i];
        }

        if (valor <= K && valor >= -K)
        {

            Profit += soma * Vi[k];
            Comb[k] = -soma;
            valor -= soma;
            calcula(valor, prox, contamenores, Profit, compra + 1, Comb);
        }
        else
        {
            return;
        }
    }
}

// funciona quando so existe um menor e um maior.
int BestProfitCase1()
{

    int contador = 0;
    int contamenores = 1;
    for (int i = 0; i < D; i++)
    {
        if (Vi[i] == menor)
        {
            contamenores++;
        }
        if (Vi[i] < menor)
        {
            menor = Vi[i];
        }

        if (Vi[i] > maior)
        {
            // contador++;
            maior = Vi[i];
        }
    }
    int profit = 0;
    if (contamenores == 1)
    {
        for (int i = 0; i < Vi.size(); i++)
        {
            if (Vi[i] == menor)
            {
                aux[i] = K;
            }
            else if (Vi[i] == maior)
            {
                aux[i] = -K;
            }
        }
        contador++;

        profit = (-K) * menor + K * maior - K * R;

        return profit;
    }
    else
    {
        vector<int> Comb = vector<int>(D, -2);
        calcula(0, 0, contamenores, 0, 0, Comb);
        return prof;
    }
}

int main()
{
    cin >> tipo;
    cin >> N >> D >> K >> R;
    while (N--)
    {
        comprou = vector<bool>(D, false);
        Vi = vector<int>(D, 0);
        aux = vector<int>(D, 0);
        dp = vector<vector<int>>(D, vector<int>(D, 0));
        for (int i = 0; i < D; i++)
        {
            cin >> valor;
            Vi[i] = valor;
        }
        contador = 1;
        int p = BestProfitCase1();
        if (tipo == 1)
        {
            printf("%d\n", p);
        }
        if (tipo == 2)
        {
            printf("%d\n", p);
            for (int i = 0; i < aux.size(); i++)
            {
                if (i == aux.size() - 1)
                {
                    printf("%d\n", aux[i]);
                }
                else
                {
                    printf("%d ", aux[i]);
                }
            }
        }
        if (tipo == 3)
        {
            printf("%d %d\n", p, contador);
        }
    }
}
