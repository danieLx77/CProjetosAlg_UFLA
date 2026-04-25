#include <iostream>
#include <vector>

using namespace std;

long long mergeAndCount(vector<int>& arr, int esq, int meio, int dir) {
    int n1 = meio - esq + 1;
    int n2 = dir - meio;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[esq + i];
    for (int j = 0; j < n2; j++) R[j] = arr[meio + 1 + j];

    int i = 0, j = 0, k = esq;
    long long inversoes = 0;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
            inversoes += (n1 - i); 
        }
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    return inversoes;
}


long long solve(vector<int>& arr, int esq, int dir) {
    long long cont = 0;
    if (esq < dir) {
        int meio = esq + (dir - esq) / 2;

        cont += solve(arr, esq, meio);      
        cont += solve(arr, meio + 1, dir);   
        cont += mergeAndCount(arr, esq, meio, dir); 
    }
    return cont;
}

int main() {
    int N;
    while (cin >> N && N != 0) {
        vector<int> A(N);
        for (int i = 0; i < N; i++) cin >> A[i];

        long long result = solve(A, 0, N - 1);
        cout << "Minimum exchange operations : " << result << endl;
    }
    return 0;
}