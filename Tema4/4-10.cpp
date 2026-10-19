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

class Solucion
{
public:
   Solucion(Grafo const &g, vector<int> const &costes) : g(g), costes(costes)
   {
      visitados = vector<bool>(g.V(), false);

      for (int i = 0; i < g.V(); i++)
      {
         if (!visitados[i]) {
            costesMin.push_back(std::numeric_limits<int>::max());
            dfs(i, idx);

            total += costesMin[idx];
            idx++;
         }
      }
   }

   int getTotal() {
      return total;
   }

private:
   vector<int> costesMin;
   vector<bool> visitados;
   vector<int> const& costes;
   Grafo const& g;
   int total = 0;
   int idx = 0;

   void dfs(int v, int const& compIndex) {
      visitados[v] = true;
      costesMin[compIndex] = min(costesMin[compIndex], costes[v]);

      for (int u : g.ady(v)) {
         if (!visitados[u]) {
            dfs(u, compIndex);
         }
      }
   }
};

void resuelveCaso()
{

   int N, M;
   cin >> N >> M;

   Grafo g(N);

   int c;
   vector<int> costes(N);

   for (int i = 0; i < N; i++)
   {
      cin >> c;
      costes[i] = c;
   }

   int a, b;
   for (int i = 0; i < M; i++)
   {
      cin >> a >> b;
      g.ponArista(a - 1, b - 1);
   }

   cout << Solucion(g, costes).getTotal() << '\n';
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
