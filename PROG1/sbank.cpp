#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int ALFABETO = 256;

// Counting Sort por posição (estável)
void countingSort(vector<string>& contas, int pos) {
    int n = contas.size();
    vector<int> contagem(ALFABETO, 0);
    vector<string> resultado(n);

    // Contagem
    for (const string& conta : contas) {
        contagem[(unsigned char)conta[pos]]++;
    }

    // Prefixo acumulado
    for (int i = 1; i < ALFABETO; i++) {
        contagem[i] += contagem[i - 1];
    }

    // Construção reversa (estável)
    for (int i = n - 1; i >= 0; i--) {
        int c = (unsigned char)contas[i][pos];
        resultado[--contagem[c]] = contas[i];
    }

    contas = resultado;
}

// Radix Sort (LSD)
void radixSort(vector<string>& contas) {
    if (contas.empty()) return;

    int tamanho = contas[0].size();

    for (int pos = tamanho - 1; pos >= 0; pos--) {
        countingSort(contas, pos);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<string> contas(n);

        for (int i = 0; i < n; i++) {
            string a, b, c, d, e, f;
            cin >> a >> b >> c >> d >> e >> f;
            contas[i] = a + " " + b + " " + c + " " + d + " " + e + " " + f;
        }

        if (contas.empty()) {
            if (t) cout << "\n";
            continue;
        }

        radixSort(contas);

        // Contagem de ocorrências
        string atual = contas[0];
        int contador = 1;

        for (int i = 1; i < n; i++) {
            if (contas[i] == atual) {
                contador++;
            } else {
                cout << atual << " " << contador << "\n";
                atual = contas[i];
                contador = 1;
            }
        }

        cout << atual << " " << contador << "\n";
        cout << "\n";
    }

    return 0;
}