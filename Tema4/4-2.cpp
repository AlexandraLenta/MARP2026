/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
using namespace std;
#include "Grafo.h"
#include <queue>
#include <vector>

bool isBipartito(Grafo const &g)
{
    // visited & color: -1 = not visited, 0 = color 1, 1 = color 2
    vector<int> visited(g.V(), -1);

    queue<int> q; // cola de nuestro camino por los nodos

    for (int i = 0; i < g.V(); i++)
    {
        // ya hemos visitado este vertice
        if (visited[i] != -1)
            continue;

        // empezamos con el nodo 0
        visited[i] = 0;
        q.push(i);
        
        // si no lo hemos visitado, visitamos el vertice y todas sus conexiones
        while (!q.empty())
        {
            int node = q.front();
            bool color = visited[node];

            q.pop();

            for (int v : g.ady(node))
            {
                if (visited[v] == -1)
                {
                    q.push(v);
                    visited[v] = 1 - visited[node];
                }
                else if (color == visited[v])
                {
                    return false;
                }
            }
        }
    }

    return true;
}

void resuelveCaso()
{

    Grafo g(cin);

    if (isBipartito(g))
    {
        cout << "SI\n";
    }
    else
    {
        cout << "NO\n";
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
