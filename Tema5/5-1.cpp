/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
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

const int MAX = 10000;
const int INF = 1000000000;

int ady(int v, int i)
{
    switch (i)
    {
    case 0:
        return (v + 1) % MAX;
    case 1:
        return (v * 2) % MAX;
    case 2:
        return v / 3;
    }
}

int bfs(int origen, int destino) {
    if (origen == destino) return 0;
    vector<int> dist(MAX, INF);

    dist[origen] = 0;

    queue<int> q; 
    q.push(origen);

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int i = 0; i < 3; i++) {
            int w = ady(v, i);

            if (dist[w] == INF) {
                dist[w] = dist[v] + 1;

                if (w == destino) return dist[w];
                else q.push(w);
            }
        }
    }
}

void resuelveCaso()
{
    int origen, destino;

    cin >> origen >> destino;

    cout << bfs(origen, destino) << '\n';
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
