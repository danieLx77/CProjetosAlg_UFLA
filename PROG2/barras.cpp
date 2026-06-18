#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INFINITO = 1e9;


int resolverDP(int esq, int dir, const vector<int>& cortes, vector<vector<int>>& memo) {
    if (esq + 1 == dir) return 0;

    if (memo[esq][dir] != -1) return memo[esq][dir];

    int custoMinimo = INFINITO;

    for (int k = esq + 1; k < dir; ++k) {
        int custoAtual = resolverDP(esq, k, cortes, memo) +
                         resolverDP(k, dir, cortes, memo) +
                         (cortes[dir] - cortes[esq]);
                         
        custoMinimo = min(custoMinimo, custoAtual);
    }

    return memo[esq][dir] = custoMinimo;
}

int calcularMenorCustoCorte(int tamanhoBarra, int numCortes, vector<int>& cortes) {
    cortes.insert(cortes.begin(), 0);
    cortes.push_back(tamanhoBarra);

    int totalPontos = cortes.size();

    vector<vector<int>> memo(totalPontos, vector<int>(totalPontos, -1));

    return resolverDP(0, totalPontos - 1, cortes, memo);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tamanhoBarra;

    while (cin >> tamanhoBarra && tamanhoBarra != 0) {
        int numCortes;
        cin >> numCortes;

        vector<int> cortes(numCortes);
        for (int i = 0; i < numCortes; ++i) {
            cin >> cortes[i];
        }

        int resultado = calcularMenorCustoCorte(tamanhoBarra, numCortes, cortes);
        cout << resultado << "\n";
    }

    return 0;
}