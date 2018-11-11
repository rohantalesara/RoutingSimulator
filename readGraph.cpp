#include <iostream>
#include <vector>
#include <limits>

using namespace std;

int main() {
    int N;
    int i, j, temp;
    cin >> N;
    vector< vector< int> > graph(N, vector< int >(N, INT_MAX));
    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++){
            cin >> temp;
            if(temp != -1)  graph[i][j] = temp;
        }
    }
    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) cout << graph[i][j] << " ";
        cout << endl;
    }
}