/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h"
#include "EnterosInf.h"
#include <unordered_map>
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

void Floyd(Matriz<EntInf> const &G, Matriz<EntInf> &C)
{
   int V = G.numfils(); // número de vértices de G

   // inicialización

   C = G;

   // actualizaciones de las matrices
   for (int k = 0; k < V; ++k)
   {
      for (int i = 0; i < V; ++i)
      {
         for (int j = 0; j < V; ++j)
         {
            auto temp = C[i][k] + C[k][j];

            if (temp < C[i][j])
            { // es mejor pasar por k
               C[i][j] = temp;
            }
         }
      }
   }
}

void resuelveCaso()
{
   int P, R;
   cin >> P >> R;

   string name1, name2;

   unordered_map<string, int> nameIDS;
   Matriz<EntInf> G(P, P, Infinito);

   for (int i = 0; i < P; i++)
   {
      G[i][i] = 0;
   }

   int j = 0;

   for (int i = 0; i < R; i++)
   {
      cin >> name1 >> name2;

      // el nombre no aun
      if (nameIDS.find(name1) == nameIDS.end())
      {
         nameIDS[name1] = j;
         j++;
      }

      if (nameIDS.find(name2) == nameIDS.end())
      {
         nameIDS[name2] = j;
         j++;
      }

      G[nameIDS[name1]][nameIDS[name2]] = 1;
      G[nameIDS[name2]][nameIDS[name1]] = 1;
   }

   Matriz<EntInf> C;
   EntInf grado = 0;

   Floyd(G, C);

   for (int i = 0; i < C.numfils(); i++)
   {
      for (int j = 0; j < C.numcols(); j++)
      {
         grado = max(grado, C[i][j]);
         if (grado == Infinito)
         {
            cout << "DESCONECTADA\n";
            return;
         }
      }
   }

   cout << grado << '\n';
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
