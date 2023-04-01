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

void calcula(int valor, int k, int contamenores, int Profit, int compra, vector<int> &Comb)
{

    int prox = k + 1;

    if (prof < Profit)
    {

        prof = Profit;
    }
    if (k == Vi.size())
    {
        prof += (-3 * (compra)) * R;
        return;
    }
    for (int i = 0; i < Comb.size(); i++)
    {
        printf("%d ", Comb[i]);
    }
    printf("\n\n");
    //  printf("VALOR %d com  e V %d e contamenores %d profit é %d\n", k, Vi[k], contamenores, Profit);
    if (Vi[k] == menor)
    {

        if (valor < 3 && valor > -3)
        {
            if (contamenores != 1)
            {
                for (int i = 0; i < contamenores; i++)
                {
                    Profit += Vi[k] * (-i);
                    Comb[k] = i;
                    int next = contamenores - i;
                    // printf("%d  _ %d\n", k, i);
                    calcula(valor + i, prox, next, Profit, compra, Comb);
                }
            }
            else
            {
                valor = 0;
                Comb[k] = 3;
                calcula(valor + 1, prox, 0, Profit, compra, Comb);
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

        if (soma <= 3 && soma >= -3)
        {

            Profit += soma * Vi[k];
            Comb[k] = -soma;
            valor -= soma;
            calcula(valor + soma, prox, contamenores, Profit, compra + 1, Comb);
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
        profit = (-K) * menor + K * maior - 3 * R;
    }
    else
    {
        vector<int> Comb = vector<int>(D, -2);
        calcula(0, 0, contamenores, 0, 0, Comb);
        printf("%d\n", prof);
    }

    printf("ContaMenores %d\n", contamenores);
    return profit;
}

int main()
{
    cin >> tipo;
    cin >> N >> D >> K >> R;
    while (N--)
    {
        comprou = vector<bool>(D, false);
        Vi = vector<int>(D, 0);

        dp = vector<vector<int>>(D, vector<int>(D, 0));
        for (int i = 0; i < D; i++)
        {
            cin >> valor;
            Vi[i] = valor;
        }
        printf("%d\n", BestProfitCase1());
    }
}
