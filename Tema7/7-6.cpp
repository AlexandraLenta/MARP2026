/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include "IndexPQ.h"
#include <queue>
#include <limits>

const vector<pair<int, int>> dirs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

class Dijkstra
{
public:
   // dist[v] = menor fatiga posible llegando a v desde origen
   Dijkstra(vector<int> const &costs, int fils, int cols, pair<int, int> origin) : pq(fils * cols), dist(fils * cols, INF), costs(costs)
   {
      linearOrigin = origin.first * cols + origin.second;

      dist[linearOrigin] = costs[linearOrigin];

      pq.push(linearOrigin, costs[linearOrigin]);

      while (!pq.empty())
      {
         int v = pq.top().elem;
         pq.pop();

         for (auto dir : dirs)
         {
            int ni = v / cols + dir.first, nj = v % cols + dir.second;

            int linearNext = ni * cols + nj;

            if (ni >= 0 && ni < fils && nj >= 0 && nj < cols)
            {
               relajar(v, linearNext);
            }
         }
      }
   }

   int distancia(int v)
   {
      return dist[v];
   }

private:
   const int INF = std::numeric_limits<int>::max();
   int linearOrigin;
   IndexPQ<int> pq;
   vector<int> dist;
   int fils, cols;
   vector<int> const& costs;

   void relajar(int v, int w)
   {
      int nd = max(dist[v], costs[w]);
      if (nd < dist[w])
      {
         dist[w] = nd;
         pq.update(w, dist[w]);
      }
   }
};

void resuelveCaso()
{
   int F, C;
   cin >> F >> C;
   vector<int> map(F * C);

   int a;
   for (int i = 0; i < F; i++)
   {
      for (int j = 0; j < C; j++)
      {
         cin >> a;
         map[i * C + j] = a;
      }
   }

   Dijkstra d(map, F, C, {0, 0});

   cout << d.distancia((F - 1) * C + (C - 1)) << '\n';
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
