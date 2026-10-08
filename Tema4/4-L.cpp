/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "Grafo.h"
#include <vector>
#include <queue>
#include <limits>
using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class BFS {
public:
    BFS(Grafo const& g, int a, int l, int t) : g(g) {
        bfs(a, distanciaA);
        bfs(l, distanciaL);
        bfs(t, distanciaT);

        minim = numeric_limits<int>::max();
        for (int i = 0; i < g.V(); i++) {
            minim = min(minim, distanciaA[i] + distanciaL[i] + distanciaT[i]);
        }
    }

    int res() {
        return minim;
    }

private:
    vector<bool> visitado;
    vector<int> distanciaA; // distancia desde casa de Alex hasta el punto de encuentro
    vector<int> distanciaL; // distancia desde casa de Lucas hasta el punto de encuentro
    vector<int> distanciaT; // distancia desde el trabajo hasta el punto de encuentro
    int minim;

    Grafo const& g;

    void bfs(int s, vector<int>& dist) {
        visitado = vector<bool>(g.V(), false);
        dist = vector<int>(g.V(), -1);

        queue<int> q;

        q.push(s);
        visitado[s] = true;
        dist[s] = 0;

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            for (int w : g.ady(v)) {
                if (!visitado[w]) {
                    visitado[w] = true;
                    dist[w] = dist[v] + 1;
                    q.push(w);
                }
            }
        }
    }
};

void resuelveCaso()
{

    int N, C, alex, lucas, trabajo;

    cin >> N >> C >> alex >> lucas >> trabajo;

    Grafo g(N);

    int a, b;
    for (int i = 0; i < C; i++)
    {
        cin >> a >> b;
        g.ponArista(a - 1, b - 1);
    }

    BFS bfs(g, alex - 1, lucas - 1, trabajo - 1);

    cout << bfs.res() << '\n';
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
