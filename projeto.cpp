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
int main()
{
    cin >> tipo;
    cin >> N >> D >> K >> R;
    for (int i = 0; i < D; i++)
    {
        cin >> valor;
        Vi.push_back(valor);
    }
}