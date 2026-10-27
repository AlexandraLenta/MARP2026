/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
using namespace std;
#include "GrafoValorado.h"
#include <limits>
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

class AllPaths
{
public:
   AllPaths(GrafoValorado<int> const &g, int origen, int destino) : visited(g.V(), false), result(), q()
   {
      visited[origen] = true;
      q.push_back({{origen}, 0});

      while (!q.empty())
      {
         vector<int> path = q.front().first;
         int cost = q.front().second;

         q.pop_front();
         int lastN = path[path.size() - 1];

         if (lastN == destino)
         {
            result.push_back({path, cost});
            continue;
         }

         for (auto a : g.ady(lastN))
         {
            if (!visited[a.otro(lastN)])
            {
               visited[a.otro(lastN)] = true;
               
               vector<int> newPath = path;
               
               newPath.push_back(a.otro(lastN));
               q.push_back({newPath, cost + a.valor()});
            }
         }
      }
   }

private:
   const int INF = std::numeric_limits<int>::max();
   int origen;
   std::vector<bool> visited;
   std::vector<pair<vector<int>, int>> result;
   deque<pair<vector<int>, int>> q;
};

void resuelveCaso()
{
   int N, C;
   cin >> N >> C;

   GrafoValorado<int> g(N);

   int a, b, l;
   for (int i = 0; i < C; i++)
   {
      cin >> a >> b >> l;
      g.ponArista({a - 1, b - 1, l});
   }

   int K;
   cin >> K;

   for (int i = 0; i < K; i++)
   {
      cin >> a >> b;
      AllPaths d(g, a - 1, b - 1);
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
