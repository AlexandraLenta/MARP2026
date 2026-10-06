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

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class ComponentesConexas
{
public:
   ComponentesConexas(Grafo &g)
   {
      visitados = vector<bool>(g.V(), false);
      componente = vector<int>(g.V(), -1);

      for (int v = 0; v < g.V(); v++)
      {
         if (!visitados[v])
         { // recorremos una nueva componente conexa cada vez
            compConexas.push_back(dfs(g, v, compConexas.size()));
         }
      }
   }

   int getTamComponente(int n)
   {
      return compConexas[componente[n]];
   }

   vector<int> getNodos()
   {
      return componente;
   }

private:
   vector<int> compConexas; // v[i] = tamanio de la comp conexa que contiene al i
   vector<bool> visitados;
   vector<int> componente;

   int dfs(Grafo const &g, int v, int comp)
   {
      visitados[v] = true;
      componente[v] = comp;
      int tam = 1;

      for (int u : g.ady(v))
      {
         if (!visitados[u])
         {
            tam += dfs(g, u, comp);
         }
      }

      return tam;
   }
};

void resuelveCaso()
{
   int n, m;

   cin >> n >> m;

   int u, u2, v;

   Grafo g(n);

   for (int i = 0; i < m; i++)
   {
      cin >> v;
      if (v > 0)
         cin >> u;
      for (int j = 1; j < v; j++)
      {
         cin >> u2;
         g.ponArista(u - 1, u2 - 1);
         u = u2;
      }
   }

   ComponentesConexas c(g);

   for (int i = 0; i < n; i++) 
      if (c.getTamComponente(i) > -1)
         cout << c.getTamComponente(i) << ' ';

   cout << '\n';
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
