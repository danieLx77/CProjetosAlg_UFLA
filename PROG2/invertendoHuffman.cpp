#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void resolverCasoDeTeste(int quantidadeFolhas) {
    vector<int> folhasPorProfundidade(55, 0);
    int profundidadeMaxima = 0;

    for (int i = 0; i < quantidadeFolhas; ++i) {
        int profundidade;
        cin >> profundidade;
        folhasPorProfundidade[profundidade]++;
        profundidadeMaxima = max(profundidadeMaxima, profundidade);
    }

    vector<int> internosPorProfundidade(55, 0);
    for (int d = profundidadeMaxima; d >= 1; --d) {
        int totalNosNesteNivel = folhasPorProfundidade[d] + internosPorProfundidade[d];
        // Dois nós no nível 'd' formam um nó interno no nível 'd-1'
        internosPorProfundidade[d - 1] = totalNosNesteNivel / 2;
    }

    // 0 = Nó Folha, 1 = Nó Interno
    // Ordenamos da maior profundidade para a menor. Em caso de empate, folhas vêm antes.
    vector<int> tiposDosNos;
    for (int d = profundidadeMaxima; d >= 0; --d) {
        for (int i = 0; i < folhasPorProfundidade[d]; ++i) {
            tiposDosNos.push_back(0);
        }
        for (int i = 0; i < internosPorProfundidade[d]; ++i) {
            tiposDosNos.push_back(1);
        }
    }

    vector<long long> pesos(tiposDosNos.size(), 0);
    int indiceDoPar = 0; // Controla qual par formará o próximo nó interno

    for (size_t i = 0; i < tiposDosNos.size(); ++i) {
        if (tiposDosNos[i] == 0) {
            // Se for folha, recebe o menor peso possível (peso do nó anterior ou 1)
            if (i == 0) {
                pesos[i] = 1;
            } else {
                pesos[i] = pesos[i - 1];
            }
        } else {
            // Se for nó interno, é a soma do par correspondente processado anteriormente
            pesos[i] = pesos[2 * indiceDoPar] + pesos[2 * indiceDoPar + 1];
            indiceDoPar++;
        }
    }

    // O último nó processado é a raiz, que guarda a soma total (o tamanho mínimo do texto)
    cout << pesos.back() << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    
    while (cin >> n && n != 0) {
        resolverCasoDeTeste(n);
    }

    return 0;
}