/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
using namespace std;
#include <queue>

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

int ady(int v, int i, unordered_map<int, int>& m) {
    if (m.find(v + i) == m.end()) {
        return v + i;
    }
    else {
        return m.find(v + i)->second;
    }
}

int bfs(int origen, int destino, int K, unordered_map<int, int>& m) {
    if (origen == destino) return 0;
    vector<int> dist(destino + 1, -1);

    dist[origen] = 0;

    queue<int> q; 
    q.push(origen);

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int i = 1; i <= K && v + i <= destino; i++) {
            int w = ady(v, i, m);

            if (dist[w] == -1) {
                dist[w] = dist[v] + 1;

                if (w == destino) return dist[w];
                else q.push(w);
            }
        }
    }
}

void resuelveCaso()
{
    int N, K, S, E;
    cin >> N >> K >> S >> E;

    int a, b;

    unordered_map<int, int> m;

    for (int i = 0; i < S + E; i++)
    {
        cin >> a >> b;
        m[a] =  b;
    }

    cout << bfs(1, N*N, K, m) << '\n';
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main()
{
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    if (!in.is_open())
        cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
#endif
    return 0;
}