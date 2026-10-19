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

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

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

    int A, R;
    cin >> A >> R;

    Grafo g(A);

    int a, b;
    for (int i = 0; i < R; i++)
    {
        cin >> a >> b;
        g.ponArista(a - 1, b - 1);
    }

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
    // entrada/salida rápida
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ajustes para que cin extraiga directamente de un fichero (solamente en local)
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    if (!in.is_open())
    {
        cout << "Error: no se ha podido abrir el archivo de entrada." << endl;
        // sin fichero no hay nada que leer, y cin >> ... dejaría las
        // variables sin tocar, con su valor basura
        return 1;
    }
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
