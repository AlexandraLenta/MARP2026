/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
using namespace std;
#include "Matriz.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

// calcula la longitud del mayor palíndromo en patitos[i..j]
int resolver_rec(string const &palabra, int i, int j, Matriz<int> &palin)
{
   int &res = palin[i][j];
   if (res == -1)
   {
      if (i > j)
         res = 0;
      else if (i == j)
         res = 1;
      else if (palabra[i] == palabra[j])
         res = resolver_rec(palabra, i + 1, j - 1, palin) + 2;
      else
         res = max(resolver_rec(palabra, i + 1, j, palin),
                   resolver_rec(palabra, i, j - 1, palin));
   }
   return res;
}

void reconstruir(string const &palabra, Matriz<int> const &palin,
                 int i, int j, string &sol)
{
   if (i > j)
      return;
   if (i == j)
      sol.push_back(palabra[i]);
   else if (palabra[i] == palabra[j])
   {
      sol.push_back(palabra[i]);
      reconstruir(palabra, palin, i + 1, j - 1, sol);
      sol.push_back(palabra[j]);
   }
   else
   {
      if (palin[i][j] == palin[i + 1][j])
      {
         sol.push_back(palabra[i]);
         reconstruir(palabra, palin, i + 1, j, sol);
         sol.push_back(palabra[i]);
      }
      else {
         sol.push_back(palabra[j]);
         reconstruir(palabra, palin, i, j - 1, sol);
         sol.push_back(palabra[j]);
      }
   }
}

void resuelveCaso()
{
   string word;
   cin >> word;

   int n = word.length();

   Matriz<int> palindromo(n, n, -1);
   int res = resolver_rec(word, 0, n - 1, palindromo);

   string sol;

   reconstruir(word, palindromo, 0, n - 1, sol);

   cout << (sol.size() - res) / 2 << ' ' << sol << '\n';
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
