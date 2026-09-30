/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
using namespace std;
#include "Grafo.h"
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

// class IsTree {
// public:
//     IsTree(Grafo const& g) : _grafo(g) {}

// si es conexo y aciclico
// o sea, todo par de vertices esta conectado por justo un camino
bool isTree(Grafo const &g)
{
    // un grafo conexo TIENE que tener n - 1 aristas, donde n es el numero de vertices
    if (g.V() - 1 != g.A())
        return false;

    vector<bool> visited(g.V(), false);

    queue<int> q; // cola de nuestro camino por los nodos

    // empezamos con el nodo 0
    visited[0] = true;
    q.push(0);

    int count = 1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v : g.ady(u))
        {
            if (!visited[v])
            {
                q.push(v);
                count++;
                visited[v] = true;
            }
        }
    }

    return count == g.V();
}

// private:
//     Grafo const& _grafo;
// };

void resuelveCaso()
{
    Grafo g(cin);

    if (isTree(g))
        cout << "SI\n";
    else
        cout << "NO\n";
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
