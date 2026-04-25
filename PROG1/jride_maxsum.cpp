#include <iostream>
#include <vector>

using namespace std;

struct SubArray {
    long long sum;
    int start;
    int end;
};

SubArray getBetter(const SubArray& a, const SubArray& b) {
    // Maior soma ganha
    if (a.sum != b.sum) {
        return (a.sum > b.sum) ? a : b;
    }
    
    // Em caso de empate na soma, o trecho mais longo ganha
    int lenA = a.end - a.start;
    int lenB = b.end - b.start;
    if (lenA != lenB) {
        return (lenA > lenB) ? a : b;
    }
    
    // Em caso de empate no tamanho, o que começa primeiro ganha
    return (a.start < b.start) ? a : b;
}

// Função que encontra o subvetor de soma máxima que CRUZA o meio
SubArray findMaxCrossingSubarray(const vector<int>& arr, int low, int mid, int high) {
    long long left_sum = -1e18; // Inicializa com um valor muito pequeno
    long long current_sum = 0;
    int max_left = mid;
    
    // Expande do meio para a esquerda
    for (int i = mid; i >= low; i--) {
        current_sum += arr[i];
        if (current_sum > left_sum) {
            left_sum = current_sum;
            max_left = i;
        } 
        // Desempate: Se a soma empatar, atualizamos o max_left para 'i' 
        // pois um índice menor estica o tamanho do vetor e o faz começar antes.
        else if (current_sum == left_sum) {
            max_left = i; 
        }
    }

    long long right_sum = -1e18;
    current_sum = 0;
    int max_right = mid + 1;
    
    // Expande do meio para a direita
    for (int j = mid + 1; j <= high; j++) {
        current_sum += arr[j];
        if (current_sum > right_sum) {
            right_sum = current_sum;
            max_right = j;
        } 
        // Desempate: Se a soma empatar, pegamos o maior 'j' para esticar o vetor
        else if (current_sum == right_sum) {
            max_right = j; 
        }
    }

    return {left_sum + right_sum, max_left, max_right};
}

// Função Principal da Divisão e Conquista
SubArray findMaxSubarray(const vector<int>& arr, int low, int high) {
    // Caso Base: O subvetor tem apenas 1 elemento
    if (low == high) {
        return {arr[low], low, low};
    }

    int mid = low + (high - low) / 2;

    // Conquista: Resolve para as duas metades recursivamente
    SubArray left_sub = findMaxSubarray(arr, low, mid);
    SubArray right_sub = findMaxSubarray(arr, mid + 1, high);
    
    // Combina: Acha a maior que cruza o meio
    SubArray cross_sub = findMaxCrossingSubarray(arr, low, mid, high);

    // Retorna o melhor dos três, usando as regras da Jill
    return getBetter(getBetter(left_sub, right_sub), cross_sub);
}

int main() {
    int b;
    if (!(cin >> b)) return 0;

    for (int route = 1; route <= b; route++) {
        int s;
        cin >> s;
        int n = s - 1;
        
        vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }

        SubArray result = findMaxSubarray(arr, 0, n - 1);

        if (result.sum > 0) {
            // As paradas são baseadas em 1 (1-indexed). 
            // O índice start representa a aresta que sai da parada start+1.
            // O índice end representa a aresta que chega na parada end+2.
            cout << "The nicest part of route " << route 
                 << " is between stops " << (result.start + 1) 
                 << " and " << (result.end + 2) << endl;
        } else {
            cout << "Route " << route << " has no nice parts" << endl;
        }
    }
    return 0;
}