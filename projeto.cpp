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

// funciona quando so existe um menor e um maior.
int BestProfitCase1()
{
    int menor = 10000000, maior = -1;
    int contador = 0;
    for (int i = 0; i < D; i++)
    {
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

    int profit = (-K) * menor + K * maior - 3 * R;
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
        for (int i = 0; i < D; i++)
        {
            cin >> valor;
            Vi[i] = valor;
        }
        printf("%d\n", BestProfitCase1());
    }
}
