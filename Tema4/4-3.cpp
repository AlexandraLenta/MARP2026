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
using namespace std;


class MaxAmigos
{
public:
    MaxAmigos(Grafo const &g)
    {
        visitados = vector<bool>(g.V(), false);

        for (int v = 0; v < g.V(); v++)
        {
            if (!visitados[v])
            { // recorremos una nueva componente conexa cada vez
                int tam = dfs(g, v);
                maxim = max(maxim, tam);
            }
        }
    }

    int maximo()
    {
        return maxim;
    }

private:
    vector<bool> visitados;
    int maxim = 0;

    int dfs(Grafo const &g, int v)
    {
        visitados[v] = true;
        int tam = 1;

        for (int u : g.ady(v))
        {
            if (!visitados[u])
            {
                tam += dfs(g, u);
            }
        }

        return tam;
    }
};

void resuelveCaso()
{

    int n, m;
    cin >> n >> m;

    Grafo g(n);

    char v, w;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++);
        cin >> v >> w;
        g.ponArista(v - 1, w - 1);
    }

    cout << MaxAmigos(g).maximo() << '\n';
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
