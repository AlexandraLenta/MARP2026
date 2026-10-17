/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "GrafoValorado.h"
using namespace std;
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

class DFS
{
public:
    DFS(GrafoValorado<int> const &g, int origen, int destino, int coste) : g(g), origen(origen), destino(destino), coste(coste), visited(g.V(), false)
    {
        dfs(origen);
    }

    bool res() {
        return puede;
    }

private:
    GrafoValorado<int> const &g;
    int origen, destino, coste;
    bool puede = false;
    vector<bool> visited;

    void dfs(int v)
    {
        if (puede) return;

        visited[v] = true;
        for (auto a : g.ady(v))
        {
            if (a.valor() >= coste)
            {
                int w = a.otro(v);

                if (!visited[w])
                {
                    if (w == destino)
                    {
                        puede = true;
                        return;
                    }
                    dfs(w);
                }
            }
        }
    }
};

void resuelveCaso()
{
    int V, E;
    cin >> V >> E;

    GrafoValorado<int> g(V);

    int u, v, valor;
    for (int i = 0; i < E; i++) {
        cin >> u >> v >> valor;
        g.ponArista({u - 1, v - 1, valor});
    }

    int K;
    cin >> K;

    int o, d, c;

    for (int i = 0; i < K; i++)
    {
        cin >> o >> d >> c;
        if (DFS(g, o - 1, d - 1, c).res())
        {
            cout << "SI\n";
        }
        else
        {
            cout << "NO\n";
        }
    }
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
   // entrada/salida rápida
   ios::sync_with_stdio(false);
   cin.tie(nullptr);

   // ajustes para que cin extraiga directamente de un fichero (solamente en local)
#ifndef DOMJUDGE
   ifstream in("casos.txt");
   if (!in.is_open()) {
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
