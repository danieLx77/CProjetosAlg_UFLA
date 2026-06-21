#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    int preco;
    int peso;
};

// Problema da mochila 0/1
int calcularMaximoValorMochila(int capacidade, const vector<Item>& itens) {
    // dp[c] armazenará o maior valor possível para uma capacidade 'c'
    vector<int> dp(capacidade + 1, 0);

    for (const auto& item : itens) {
        for (int c = capacidade; c >= item.peso; c--) {
            dp[c] = max(dp[c], dp[c - item.peso] + item.preco);
        }
    }

    return dp[capacidade];
}

void resolverCasoDeTeste() {
    int quantidadeItens;
    cin >> quantidadeItens;

    vector<Item> itens(quantidadeItens);
    for (int i = 0; i < quantidadeItens; i++) {
        cin >> itens[i].preco >> itens[i].peso;
    }

    int quantidadePessoas;
    cin >> quantidadePessoas;

    long long valorTotalGrupo = 0;
    for (int i = 0; i < quantidadePessoas; i++) {
        int capacidadePessoa;
        cin >> capacidadePessoa;
        
        // Acumula o valor máximo que consegue carregar
        valorTotalGrupo += calcularMaximoValorMochila(capacidadePessoa, itens);
    }

    cout << valorTotalGrupo << "\n";
}

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int casosDeTeste;
    cin >> casosDeTeste;

    while (casosDeTeste--) {
        resolverCasoDeTeste();
    }

    return 0;
}