/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
using namespace std;
#include "DigrafoValorado.h"
#include <vector>
#include "IndexPQ.h"
#include <list>
#include <limits>

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
   Dijkstra(DigrafoValorado<int> const &g, int orig) : origen(orig),
                                                       dist(g.V(), INF), ulti(g.V()), pq(g.V())
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

   list<AristaDirigida<int>> camino(int v) const
   {
      list<AristaDirigida<int>> cam;

      // recuperamos el camino retrocediendo
      AristaDirigida<int> a;

      for (a = ulti[v]; a.desde() != origen; a = ulti[a.desde()])
         cam.push_front(a);

      cam.push_front(a);

      return cam;
   }

private:
   const int INF = std::numeric_limits<int>::max();
   int origen;
   std::vector<int> dist;
   std::vector<AristaDirigida<int>> ulti;
   IndexPQ<int> pq;

   void relajar(AristaDirigida<int> a)
   {
      int v = a.desde(), w = a.hasta();
      if (dist[w] > dist[v] + a.valor())
      {
         dist[w] = dist[v] + a.valor();
         ulti[w] = a;
         pq.update(w, dist[w]);
      }
   }
};

void resuelveCaso()
{
   int N;
   cin >> N;

   int t;
   vector<int> tiempos(N);

   for (int i = 0; i < N; i++)
   {
      cin >> t;
      tiempos[i] = t;
   }

   int M;
   cin >> M;

   DigrafoValorado<int> g(N);

   int a, b;
   for (int i = 0; i < M; i++)
   {
      cin >> a >> b >> t;

      g.ponArista({a - 1, b - 1, t + tiempos[b - 1]}); // coste: tiempo desde que la pagina a este cargada, hasta encontrar y pulsar en enlace a la pagina b y que ademas esa cargue
   }

   Dijkstra d(g, 0);

   if (d.hayCamino(N - 1))
   {
      int res = d.distancia(N - 1) + tiempos[0];
      cout << res << '\n';
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
