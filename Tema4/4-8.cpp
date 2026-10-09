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
#include <unordered_map>
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
class Guardias
{
public:
    Guardias(Grafo const &g)
    {
        _guardias = 0;
        _bipartito = isBipartito(g);
    }

    bool bipartito() {
        return _bipartito;
    }

    int callesConGuardias() {
        return _guardias;
    }

private:
    bool _bipartito;
    unordered_map<int, int> _callesConSinGuardias;
    int _guardias;

    bool isBipartito(Grafo const &g)
    {
        // visited & guardias: -1 = not visited, 0 = sin guardia, 1 = con guardia
        vector<int> visited(g.V(), -1);

        queue<int> q; // cola de nuestro camino por los nodos

        for (int i = 0; i < g.V(); i++)
        {
            // ya hemos visitado este vertice
            if (visited[i] != -1)
                continue;

            // empezamos con el nodo 0
            visited[i] = 1;
            _callesConSinGuardias[1]++;
            q.push(i);

            // si no lo hemos visitado, visitamos el vertice y todas sus conexiones
            while (!q.empty())
            {
                int node = q.front();
                int color = visited[node];

                q.pop();

                for (int v : g.ady(node))
                {
                    if (visited[v] == -1)
                    {
                        q.push(v);
                        visited[v] = 1 - visited[node];
                        _callesConSinGuardias[visited[v]]++;
                    }
                    else if (color == visited[v])
                    {
                        return false;
                    }
                }
            }

            _guardias += min(_callesConSinGuardias[1], _callesConSinGuardias[0]);
            _callesConSinGuardias.clear();
        }

        return true;
    }
};

void resuelveCaso()
{
    int N, C;

    cin >> N >> C;

    Grafo g(N);

    int a, b;
    for (int i = 0; i < C; i++)
    {
        cin >> a >> b;
        g.ponArista(a - 1, b - 1);
    }

    Guardias res(g);

    if (res.bipartito())
    {
        cout << res.callesConGuardias() << '\n';
    }
    else
    {
        cout << "IMPOSIBLE\n";
    }
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
