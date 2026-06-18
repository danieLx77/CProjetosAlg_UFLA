#include <iostream>
#include <vector>
using namespace std;

// Busca binária: retorna índice da faixa
int encontrarFaixa(int pontuacao, const vector<int>& limites) {
    int esquerda = 0;
    int direita = static_cast<int>(limites.size());

    while (esquerda < direita) {
        int meio = esquerda + (direita - esquerda) / 2;

        if (pontuacao < limites[meio])
            direita = meio;
        else
            esquerda = meio + 1;
    }

    return esquerda;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> limites(n - 1);
    for (int i = 0; i < n - 1; i++) {
        cin >> limites[i];
    }

    vector<int> premios(n);
    for (int i = 0; i < n; i++) {
        cin >> premios[i];
    }

    vector<int> pontuacoes(m);
    for (int i = 0; i < m; i++) {
        cin >> pontuacoes[i];
    }

    for (int i = 0; i < m; i++) {
        int faixa = encontrarFaixa(pontuacoes[i], limites);
        cout << premios[faixa];
        if (i < m - 1) cout << " ";
    }

    cout << "\n";
    return 0;
}