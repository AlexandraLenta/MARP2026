/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
using namespace std;
#include "IndexPQ.h"
#include "GrafoValorado.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class Dijkstra
{
public:
   Dijkstra(GrafoValorado<int> const &g, vector<int> const& origins, int T) :
                                                                                   dist(g.V(), INF), pq(g.V()), T(T), inLimitCount(0)
   {
      for (auto o : origins) {
         dist[o] = 0;
         pq.push(o, 0);
      }

      while (!pq.empty())
      {
         int v = pq.top().elem; pq.pop();
         
         inLimitCount++;

         for (auto a : g.ady(v))
            relajar(a, v);
      }
   }

   int count()
   {
      return inLimitCount;
   }

private:
   const int INF = std::numeric_limits<int>::max();
   int origen;
   std::vector<int> dist;
   IndexPQ<int> pq;
   int T;
   int inLimitCount;

   void relajar(Arista<int> a, int uno)
   {
      int v = uno, w = a.otro(v);
      long long d = (long long)dist[v] + a.valor();

      if (d <= T && dist[w] > d)
      {
         dist[w] = d;
         pq.update(w, dist[w]);
      }
   }
};

void resuelveCaso()
{
   int T, P, C;
   cin >> T >> P >> C;

   GrafoValorado<int> g(P);

   int a, b, c;
   for (int i = 0; i < C; i++)
   {
      cin >> a >> b >> c;
      g.ponArista({a - 1, b - 1, c});
   }

   int B;
   cin >> B;
   int count = 0;
   vector<int> origins;

   for (int i = 0; i < B; i++)
   {
      cin >> a;
      origins.push_back(a - 1);
   }

   cout << Dijkstra(g, origins, T).count() << '\n';
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
