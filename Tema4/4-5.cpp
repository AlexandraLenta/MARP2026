/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include <unordered_map>
#include <queue>
#include "Grafo.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

// O(V + A), donde V es el numero de actores totales y A es el numero de conexiones entre ellos,
// ya que cada actor se procesa como maximo una vez, y cada peli como maximo una vez
void resuelveCaso()
{
   int p;
   cin >> p;

   string peli, actor;
   int nrActores;

   // actores que aparecen en la peli i
   vector<vector<int>> actoresPorPeli(p);

   // id del actor a partir de su nombre
   unordered_map<string, int> ids;

   vector<string> nombres;

   // peliculas en las que aparece el actor i
   vector<vector<int>> pelisPorActor;

   for (int i = 0; i < p; i++)
   {
      cin >> peli >> nrActores;

      actoresPorPeli[i].reserve(nrActores);

      for (int j = 0; j < nrActores; j++)
      {
         cin >> actor;

         auto it = ids.find(actor);
         int id;

         if (it == ids.end())
         {
            id = ids.size();
            ids[actor] = id;

            nombres.push_back(actor);
            pelisPorActor.push_back({});
         }
         else
         {
            id = it->second;
         }
         // i = la peli
         // id = el actor
         actoresPorPeli[i].push_back(id);
         pelisPorActor[id].push_back(i);
      }
   }

   vector<int> consultas;
   int n;
   cin >> n;
   string nom;
   for (int i = 0; i < n; i++)
   {
      cin >> nom;
      consultas.push_back(ids[nom]);
   }

   vector<int> distancias(ids.size(), -1);

   auto it = ids.find("KevinBacon");

   if (it != ids.end())
   {
      int kevinId = it->second;

      // visitamos una peli una sola vez
      vector<bool> pelisVisitadas(p, false);

      queue<int> q; // nodos

      // actores
      q.push(kevinId);
      distancias[kevinId] = 0;

      // si no lo hemos visitado, visitamos el vertice y todas sus conexiones
      while (!q.empty())
      {
         int node = q.front();

         int dist = distancias[node];

         q.pop();

         for (int i = 0; i < pelisPorActor[node].size(); i++) {
            int peli = pelisPorActor[node][i];
            
            if (!pelisVisitadas[peli]) {
               pelisVisitadas[peli] = true;

               for (int j = 0; j < actoresPorPeli[peli].size(); j++) {
                  int actor = actoresPorPeli[peli][j];
                  if (actor != node && distancias[actor] == -1) {
                     q.push(actor);
                     distancias[actor] = dist + 1;
                  }
               }
            }

         }
      }

      for (int c : consultas)
      {
         if (distancias[c] != -1)
         {
            cout << nombres[c] << ' ' << distancias[c] << '\n';
         }
         else
         {
            cout << nombres[c] << " INF\n";
         }
      }
   }
   else
   {
      for (int c : consultas)
      {
         cout << nombres[c] << " INF\n";
      }
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
