/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"
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

class Solucion
{
public:
    Solucion(GrafoValorado<int> const& g, int origen, int destino) : g(g), visited(g.V(), false) { 
        bfs(origen, destino);
    }

    bool end() {
        return endReached;
    }

    int maxCoste() {
        return costeMax;
    }

private:
    GrafoValorado<int> const& g;
    std::vector<Arista<int>> _arm;
    int costeMax;
    vector<bool> visited;
    bool endReached = false;

    void bfs(int origen, int destino) {
        costeMax = 0;
        queue<int> q;
        ConjuntosDisjuntos cjtos(g.V());

        visited[origen] = true;

        q.push(origen);
        int minim = numeric_limits<int>::max();

        while (!q.empty()) {
            int u = q.front();

            q.pop();

            for (auto a : g.ady(u)) {
                if (a.otro(u) == destino) {
                    minim = min(minim, a.valor());
                    endReached = true;
                }
                else if (!cjtos.unidos(u, a.otro(u))) {
                    q.push(a.otro(u));
                    cjtos.unir(u, a.otro(u));

                    minim = min(minim, a.valor());
                }
            }
            costeMax = max(costeMax, minim);
        }
    }
};

void resuelveCaso()
{

    int N, M;
    cin >> N >> M;

    GrafoValorado<int> g(N);

    int a, b, c;
    for (int i = 0; i < M; i++) {
        cin >> a >> b >> c;

        g.ponArista({a - 1, b - 1, c});
    }

    int n, m;
    cin >> n >> m;

    Solucion res(g, n - 1, m - 1);

    if (res.end() == g.V() - 1) {
        cout << res.maxCoste() << '\n';
    }
    else
        cout << "IMPOSIBLE\n";
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
