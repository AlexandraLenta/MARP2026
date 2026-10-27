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
#include <tuple>

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

const int INF = numeric_limits<int>::max();

// edgeCount[i] -> minimum number of edges from origen to node i
vector<int> BFS(GrafoValorado<int> const& g, int origen) {
   vector<int> edgeCount(g.V(), INF);

   queue<int> q;

   edgeCount[origen] = 0;

   q.push(origen);

   while (!q.empty()) {
      int n = q.front(); q.pop();

      for (auto a : g.ady(n)) {
         int w = a.otro(n);

         if (edgeCount[w] >= INF) {
            edgeCount[w] = edgeCount[n] + 1;
            q.push(w);
         }
      }
   }

   return edgeCount;
}

void Dijkstra(GrafoValorado<int> const& g, int origen, vector<int>& dist, vector<int>& edges) {
   dist = vector<int>(g.V(), INF);
   edges = vector<int>(g.V(), INF);

   priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq; // distance (cost), edges (streets), node

   dist[origen] = 0;
   edges[origen] = 0;

   pq.push({0, 0, origen});

   while (!pq.empty()) {
      auto [d, e, n] = pq.top(); pq.pop();

      if (d > dist[n] || (d == dist[n] && e > edges[n])) {
         continue;
      }

      for (auto a : g.ady(n)) {
         int w = a.otro(n);

         int nd = d + a.valor();
         int ne = e + 1;

         if (nd < dist[w] || (nd == dist[w] && ne < edges[w])) {
            dist[w] = nd;
            edges[w] = ne;
            pq.push({nd, ne, w});
         }
      }
   }
}

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
      a--; b--;

      vector<int> res = BFS(g, a);
      if (res[b] >= INF) {
         cout << "SIN CAMINO\n";
         continue;
      }
      
      vector<int> dist, streets;
      Dijkstra(g, a, dist, streets);

      cout << dist[b] << ' ' << (streets[b] == res[b] ? "SI" : "NO") << '\n';
   }
   cout << "---\n";
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
