#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INFINITO = 1e9; 

struct Aresta {
    int destino;
    int custo;
};

struct Estado {
    int custo;
    int cidadeAtual;
    int paridade; 

    bool operator>(const Estado& outro) const {
        return custo > outro.custo;
    }
};

int calcularMenorCustoPar(int totalCidades, const vector<vector<Aresta>>& grafo) {
    vector<vector<int>> distancia(totalCidades + 1, vector<int>(2, INFINITO));
    
    priority_queue<Estado, vector<Estado>, greater<Estado>> filaPrioridade;

    distancia[1][0] = 0;
    filaPrioridade.push({0, 1, 0});

    while (!filaPrioridade.empty()) {
        Estado atual = filaPrioridade.top();
        filaPrioridade.pop();

        int custoAtual = atual.custo;
        int u = atual.cidadeAtual;
        int p = atual.paridade;

        if (custoAtual > distancia[u][p]) continue;

        for (const Aresta& aresta : grafo[u]) {
            int v = aresta.destino;
            int pesoDaAresta = aresta.custo;
            
            int proximaParidade = 1 - p;

            if (distancia[u][p] + pesoDaAresta < distancia[v][proximaParidade]) {
                distancia[v][proximaParidade] = distancia[u][p] + pesoDaAresta;
                filaPrioridade.push({distancia[v][proximaParidade], v, proximaParidade});
            }
        }
    }

    return (distancia[totalCidades][0] == INFINITO) ? -1 : distancia[totalCidades][0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int C, V;
    
    if (!(cin >> C >> V)) return 0;

    vector<vector<Aresta>> grafo(C + 1);
    for (int i = 0; i < V; ++i) {
        int origem, destino, custo;
        cin >> origem >> destino >> custo;
        grafo[origem].push_back({destino, custo});
        grafo[destino].push_back({origem, custo}); 
    }

    int resultado = calcularMenorCustoPar(C, grafo);
    
    cout << resultado << "\n";

    return 0;
}