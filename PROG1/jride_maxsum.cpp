#include <iostream>

using namespace std;

struct MelhorTrecho {
    long long soma;
    int inicioAresta;
    int fimAresta;
};

bool trechoAtualEhMelhor(int inicioAtual, int fimAtual, const MelhorTrecho& melhor) {
    int tamanhoAtual = fimAtual - inicioAtual + 1;
    int tamanhoMelhor = melhor.fimAresta - melhor.inicioAresta + 1;

    if (tamanhoAtual != tamanhoMelhor) {
        return tamanhoAtual > tamanhoMelhor;
    }

    return inicioAtual < melhor.inicioAresta;
}

MelhorTrecho encontrarMelhorTrecho(int quantidadeArestas) {
    MelhorTrecho melhor = {-(1LL << 60), 1, 0};

    long long somaAtual = 0;
    int inicioAtual = 1;

    for (int aresta = 1; aresta <= quantidadeArestas; aresta++) {
        int niceness;
        cin >> niceness;
        somaAtual += niceness;

        if (somaAtual > melhor.soma) {
            melhor = {somaAtual, inicioAtual, aresta};
        } else if (somaAtual == melhor.soma && trechoAtualEhMelhor(inicioAtual, aresta, melhor)) {
            melhor = {somaAtual, inicioAtual, aresta};
        }

        if (somaAtual < 0) {
            somaAtual = 0;
            inicioAtual = aresta + 1;
        }
    }

    return melhor;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int quantidadeRotas;
    if (!(cin >> quantidadeRotas)) return 0;

    for (int rota = 1; rota <= quantidadeRotas; rota++) {
        int quantidadeParadas;
        cin >> quantidadeParadas;

        int quantidadeArestas = quantidadeParadas - 1;
        MelhorTrecho melhor = encontrarMelhorTrecho(quantidadeArestas);

        if (melhor.soma > 0) {
            int paradaInicio = melhor.inicioAresta;
            int paradaFim = melhor.fimAresta + 1;

            cout << "The nicest part of route " << rota
                 << " is between stops " << paradaInicio
                 << " and " << paradaFim << '\n';
        } else {
            cout << "Route " << rota << " has no nice parts\n";
        }
    }

    return 0;
}