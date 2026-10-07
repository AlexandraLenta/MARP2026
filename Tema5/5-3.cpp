/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "Digrafo.h"
#include <deque>
#include <vector>
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

class CicloDirigido {
public:
   CicloDirigido(Digrafo const& g) : visited(g.V(), false), ant(g.V()), queued(g.V(), false), isCycle(false) {
      for (int i = 0; i < g.V(); i++) {
         if (!visited[i])
            dfs(g, i);
      }
   }

   bool hasCycle() {
      return isCycle;
   }

   deque<int>& getOrder() {
      return order;
   }

   private:
   vector<bool> visited;
   vector<int> ant;
   vector<bool> queued;
   bool isCycle;
   deque<int> order;

   void dfs(Digrafo const& g, int v) {
      queued[v] = true;
      visited[v] = true;

      for (int w : g.ady(v)) {
         if (isCycle) 
            return;
         if (!visited[w]) {
            ant[w] = v; dfs(g, w);
         }
         else if (queued[w]) {
            isCycle = true;
         }
      }
      order.push_front(v);
      queued[v] = false;
   }
};

void resuelveCaso() {

   int N, M;

   cin >> N >> M;

   Digrafo d(N);

   int a, b;
   for (int i = 0; i < M; i++) {
      cin >> a >> b;
      d.ponArista(a - 1, b - 1);
   }

   CicloDirigido c(d);

   if (c.hasCycle()) {
      cout << "IMPOSIBLE\n";
   }
   else {
      for (auto i : c.getOrder()) {
         cout << i + 1 << ' ';
      }
      cout << '\n';
   }
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
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
