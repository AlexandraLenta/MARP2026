/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
using namespace std;
#include "Grafo.h"
#include <vector>
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

class Red
{
public:
   Red(Grafo &g) : g(g) {}

   int resolver(int v, int ttl)
   {
      visited = vector<bool>(g.V(), false);
      int tam = bfs(v, ttl);

      return g.V() - tam;
   }

private:
   Grafo &g;
   vector<bool> visited;

   int bfs(int n, int ttl)
   {
      int tam = 1;
      queue<pair<int, int>> q; // cola de nuestro camino por los nodos

      // empezamos con el nodo 0
      visited[n] = true;
      q.push({n, ttl});

      while (!q.empty())
      {
         int u = q.front().first;
         int tt = q.front().second;

         q.pop();

         for (int v : g.ady(u))
         {
            if (!visited[v] && tt > 0)
            {
               q.push({v, tt - 1});
               tam++;
               visited[v] = true;
            }
         }
      }
      return tam;
   }
};

void resuelveCaso()
{

   int N, C;
   cin >> N >> C;

   Grafo g(N);
   int a, b;

   for (int i = 0; i < C; i++)
   {
      cin >> a >> b;
      g.ponArista(a - 1, b - 1);
   }

   int K;
   cin >> K;

   int ini, ttl;
   Red r(g);

   for (int i = 0; i < K; i++)
   {
      cin >> ini >> ttl;
      cout << r.resolver(ini - 1, ttl) << '\n';
   }

   cout << "---\n";
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
