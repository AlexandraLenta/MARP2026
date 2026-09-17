
/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "PriorityQueue.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Caja {
   int id;
   int time;
};

bool operator<(Caja const& a, Caja const& b) {
   return a.time < b.time || (b.time == a.time && a.id < b.id);
}

bool resuelveCaso() {

   // leer los datos de la entrada
   int cajas, clientes;
   cin >> cajas >> clientes;

   if (cajas == 0 && clientes == 0)
      return false;

   vector<int> queue;
   int tiempo_cliente;
   for (int i = 0; i < clientes; i++) {
        cin >> tiempo_cliente;
        queue.push_back(tiempo_cliente);
   }

   PriorityQueue<Caja> lista_cajas;

   int caja_libre = 1;

   for (int cliente : queue) {
      if (caja_libre > cajas) {
         // cout << "reached last caja.\n";
         Caja libre = lista_cajas.top();
         lista_cajas.pop();
         lista_cajas.push({libre.id, cliente + libre.time});

         // cout << "liberated caja " << libre.id << " from client with time " << libre.time << '\n';
      }
      else {
         lista_cajas.push({caja_libre, cliente});
         caja_libre++;
      }

      // cout << "adding client with time " << cliente << " to caja " << caja_libre << '\n';

      // cout << "next caja! " << caja_libre << '\n';
   }

   if (clientes < cajas) {
      cout << clientes + 1;
   }
   else 
      cout << lista_cajas.top().id;

   cout << '\n';

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
