/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "Digrafo.h"
#include <vector>
#include <queue>
using namespace std;

/*@ <answer>

 El problema pide hallar el numero de restaurantes por los que podía pasar el dictador dado un origen y un destino.
 Para esto se puede utilizar un grafo dirigido. Tiene que ser dirigido porque se especifica en el problema que
 las calles pueden ser unidireccionales o bidireccionales.

 Podemos implementar una clase que almacene el grafo y un método que reciba un origen y destino y cuente, a través
 de un algoritmo BFS, el número de restaurantes en el camino desde el origen hasta el destino. Utilizamos BFS y no DFS
 porque resulta más cómodo parar el recorrido cuando encontremos el destino.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class BFSDirigido
{
public:
   BFSDirigido(Digrafo const &g) : g(g), g2(g.inverso()), desdeOrigen(g.V()), hastaDestino(g.V())
   {
   }

   int resuelve(int origen, int destino)
   {
      int sol = 0;

      bfs(g, origen, desdeOrigen); // primero vemos todos los vertices a los cuales se puede llegar desde el origen

      if (!desdeOrigen[destino]) return -1;

      bfs(g2, destino, hastaDestino); // luego sobre el inverso, vemos los vertices desde los que se puede alcanzar el destino

      for (int i = 0; i < g.V(); i++) {
         if (i != origen && i != destino && desdeOrigen[i] && hastaDestino[i]) 
            sol++;
      }

      return sol;
   }

private:
   Digrafo const &g;
   Digrafo g2;

   vector<bool> visited;

   vector<bool> desdeOrigen; // desdeOrigen[s] -> se puede llegar desde el origen al vertice s?
   vector<bool> hastaDestino; // hastaDestino[s] -> se puede llegar desde s hasta el vertice destino?

   void bfs(Digrafo const& g, int v, vector<bool>& alcanzable)
   {
      visited = vector<bool>(g.V(), false);
      alcanzable = vector<bool>(g.V());

      queue<int> q;

      visited[v] = true;

      q.push(v);

      while (!q.empty())
      {
         int v = q.front();
         q.pop();

         for (int w : g.ady(v))
         {
            if (!visited[w])
            {
               visited[w] = true;
               alcanzable[w] = true;

               q.push(w);
            }
         }
      }
   }
};

void resuelveCaso()
{
   int NV, NA;

   cin >> NV >> NA;

   Digrafo d(NV);

   int a, b;
   for (int i = 0; i < NA; i++)
   {
      cin >> a >> b;
      d.ponArista(a - 1, b - 1);
   }

   BFSDirigido sol(d);

   int Q;
   int origen, destino;
   cin >> Q;
   for (int i = 0; i < Q; i++)
   {
      cin >> origen >> destino;
      int s = sol.resuelve(origen - 1, destino - 1);
      if (s != -1)
         cout << s << '\n';
      else
         cout << "IMPOSIBLE\n";
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
