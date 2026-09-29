/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
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

bool resuelveCaso() {

   int n, a, b;
   cin >> n >> a >> b;

   if (!std::cin)  // fin de la entrada
      return false;

   priority_queue<int> pilasA, pilasB; // almacena el nr de horas de cada pila

   int h;
   for (int i = 0; i < a; i++) {
      cin >> h;
      pilasA.push(h);
   }
   for (int i = 0; i < b; i++) {
      cin >> h;
      pilasB.push(h);
   }

   int aP, bP;

   int total = 0;
   vector<int> usadasA;
   vector<int> usadasB;

   while (!pilasA.empty() && !pilasB.empty()) {
      total = 0;

      for (int i = 0; i < n; i++) {
         aP = pilasA.top();
         bP = pilasB.top();

         pilasA.pop();
         pilasB.pop();

         int max = std::min(aP, bP);
         total += max;

         if (aP > bP) {
            // pilasA.push(aP - bP);
            usadasA.push_back(aP - bP);
         }
         else if (bP > aP) {
            // pilasB.push(bP - aP);
            usadasB.push_back(bP - aP);
         }

         if (pilasA.empty() || pilasB.empty()) {
            break;
         }
      }
      std::cout << total << ' ';

      for (auto j : usadasA) {
         pilasA.push(j);
      }
      for (auto k : usadasB) {
         pilasB.push(k);
      }

      usadasA.clear();
      usadasB.clear();

   }
   std::cout << '\n';

   return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   ifstream in("casos.txt");
   if (!in.is_open())
      std::cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
   auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

   while (resuelveCaso());

   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   cin.rdbuf(cinbuf);
#endif
   return 0;
}