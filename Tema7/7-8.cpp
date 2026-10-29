/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
using namespace std;
#include "DigrafoValorado.h"
#include "IndexPQ.h"
#include <vector>
#include <limits>
#include <list>

class Dijkstra
{
public:
   Dijkstra(DigrafoValorado<int> const &g, int orig) : origen(orig),
                                                       dist(g.V(), INF), pq(g.V())
   {
      dist[origen] = 0;
      pq.push(origen, 0);
      while (!pq.empty())
      {
         int v = pq.top().elem;
         pq.pop();
         for (auto a : g.ady(v))
            relajar(a);
      }
   }

   bool hayCamino(int v) const { return dist[v] != INF; }

   int distancia(int v) const { return dist[v]; }

private:
   const int INF = std::numeric_limits<int>::max();
   int origen;
   std::vector<int> dist;
   IndexPQ<int> pq;

   void relajar(AristaDirigida<int> a)
   {
      int v = a.desde(), w = a.hasta();
      if (dist[w] > dist[v] + a.valor())
      {
         dist[w] = dist[v] + a.valor();
         pq.update(w, dist[w]);
      }
   }
};

void resuelveCaso()
{
   int N, C;
   cin >> N >> C;

   DigrafoValorado<int> g(N);

   int a, b, c;
   for (int i = 0; i < C; i++)
   {
      cin >> a >> b >> c;
      g.ponArista({a - 1, b - 1, c});
   }

   int origen, paquetes;
   cin >> origen >> paquetes;

   Dijkstra d1(g, origen - 1);
   Dijkstra d2(g.inverso(), origen - 1);

   int dist = 0;
   bool hayCamino = true;
   for (int i = 0; i < paquetes; i++)
   {
      cin >> a;
      a--;
      if (!d1.hayCamino(a) || !d2.hayCamino(a)) {
         hayCamino = false;
      }
      else {
         dist += d1.distancia(a) + d2.distancia(a);
      }
   }

   if (!hayCamino)   
      cout << "Imposible\n";
   else
      cout << dist << '\n';
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
