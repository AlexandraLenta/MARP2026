/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include <algorithm>
#include "EnterosInf.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

vector<int> devolverCombinaciones(int C, vector<int> const &valor)
{
   int n = valor.size();

   vector<EntInf> sectores(C + 1, Infinito);

   sectores[0] = 0;

   for (int i = 1; i <= valor.size(); i++) {
      for (int j = valor[i - 1]; j <= C; j++) {
         sectores[j] = min(sectores[j], sectores[j - valor[i - 1]] + 1);
      }
   }

   vector<int> sol;

   if (sectores[C] != Infinito) {
      int i = n, j = C;

      while (j > 0) {
         if (valor[i - 1] <= j && sectores[j] == sectores[j - valor[i - 1]] + 1) {
            sol.push_back(valor[i - 1]);
            j = j - valor[i - 1];
         }
         else 
            i--;
      }
   }

   return sol;
}

void resuelveCaso()
{
   int C, S;
   cin >> C >> S;

   int a;
   vector<int> sectores(S);
   for (int i = 0; i < S; i++)
   {
      cin >> a;
      sectores[i] = a;
   }

   vector<int> sol = devolverCombinaciones(C, sectores);

   if (sol.empty())
   {
      cout << "Imposible\n";
      return;
   }

   cout << sol.size() << ": ";

   for (auto &i : sol)
   {
      cout << i << ' ';
   }

   cout << '\n';
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
