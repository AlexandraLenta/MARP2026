/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;

const int MAX = 10000;
const int INF = 1000000000;

int ady(int v, int a, int b, int M)
{
   return (a * v + b) % M;
}

int bfs(vector<pair<int, int>> const &ops, int origen, int destino, int M)
{
   if (origen == destino)
      return 0;
   vector<int> dist(MAX, INF);

   dist[origen] = 0;

   queue<int> q;
   q.push(origen);

   while (!q.empty())
   {
      int v = q.front();
      q.pop();

      for (auto op : ops)
      {
         int w = ady(v, op.first, op.second, M);

         if (dist[w] == INF)
         {
            dist[w] = dist[v] + 1;

            if (w == destino)
               return dist[w];
            else
               q.push(w);
         }
      }
   }

   return -1;
}

//@ <answer>

void resuelveCaso()
{
   int M, S, T, N;
   cin >> M >> S >> T >> N;

   int a, b;
   vector<pair<int, int>> ops;
   for (int i = 0; i < N; i++)
   {
      cin >> a >> b;
      ops.push_back({a, b});
   }
   cout << bfs(ops, S, T, M) << '\n';
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
