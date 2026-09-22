/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "PriorityQueue.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Comic {
   int id;
   int pila;
};

bool operator<(const Comic& c1, const Comic& c2) {
   return c1.id < c2.id;
}

bool resuelveCaso() {

   // leer los datos de la entrada
   int n;
   cin >> n;

   if (!std::cin)  // fin de la entrada
      return false;
    
    int k;
    int id;
    int minId = 100000000;

    vector<vector<int>> pilas = vector<vector<int>>(n);

    for (int i = 0; i < n; i++) {
        cin >> k;
        for (int j = 0; j < k; j++) {
            cin >> id;
            pilas[i].push_back(id);
            minId = min(minId, id); // buscar el mejor id
        }
   }

   
   PriorityQueue<Comic> cola;
   int turno = 0;
   vector<int> comicsPorPila = vector<int>(n);
   for (int i = 0; i < n; i++) {
      comicsPorPila[i] = pilas[i].size() - 1;
      cola.push({ pilas[i][pilas[i].size() - 1] , i }); // elemento mas alto de la pila
   }

   while (!cola.empty()) {
      Comic comic = cola.top();
      cola.pop();
      turno++;

      if (comic.id == minId) {
         cout << turno << '\n';
         return true;
      }
      comicsPorPila[comic.pila]--;
      if (comicsPorPila[comic.pila] >= 0) {
         cola.push({pilas[comic.pila][comicsPorPila[comic.pila]], comic.pila});
      }
   }

   return true;
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

   while (resuelveCaso());

   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   cin.rdbuf(cinbuf);
#endif
   return 0;
}
