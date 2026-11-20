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

mochila[i][j] = maximo dinero conseguible, vendiendo solo a los primeros i vecinos maximo j cajas

para cada vecino, elegimos venderle 1 de los 5 "objetos", en este caso, nr de cajas. cada nr de cajas
tiene un "peso", es decir, el nr de cajas que se venden, ya que nos deja sin "espacio" en la "mochila",
es decir, nos quita del nr de cajas que podemos vender

mochila[i][j] = max sobre k = 0..min(4, j) de mochila[i-1][j-k] + cajas[i-1][k].
es decir, intentando vender cada nr de cajas, elegimos cual nos da el maximo beneficio
 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

int mochila_rec(Matriz<int> const &cajas, int i, int j,
                Matriz<int> &mochila)
{
   if (mochila[i][j] != -1) // subproblema ya resuelto
      return mochila[i][j];

   if (i == 0 || j == 0)
   {
      mochila[i][j] = 0;
      return 0;
   }

   int best = 0;

   for (int k = 0; k <= j && k <= 4; k++)
   { // vemos todas las opciones: no vender ninguna caja, hasta vender maximo 4 cajas
      best = max(best, mochila_rec(cajas, i - 1, j - k, mochila) + cajas[i - 1][k]);
   }

   mochila[i][j] = best;

   return best;
}

int mochila(Matriz<int> const &cajas, int M, vector<int> &sol)
{
   int n = cajas.numfils(); // nr de vecinos

   Matriz<int> mochila(n + 1, M + 1, -1);

   int valor = mochila_rec(cajas, n, M, mochila);

   sol.assign(n, 0);

   int j = M;
   for (int i = n; i >= 1; i--)
   {
      for (int k = 0; k <= 4 && k <= j; k++)
      {
         if (mochila[i][j] == mochila_rec(cajas, i - 1, j - k, mochila) + cajas[i - 1][k])
         {
            sol[i - 1] = k;
            j -= k;
            break;
         }
      }
   }

   return valor;
}

void resuelveCaso()
{
   int V, C;
   cin >> V >> C;

   // cajas[i][j] -> lo que paga el vecino i por venderle j cajas
   Matriz<int> cajas(V, 5, 0);

   int a;
   for (int i = 1; i < 5; i++)
   {
      for (int j = 0; j < V; j++)
      {
         cin >> a;
         cajas[j][i] = a;
      }
   }
   vector<int> sol;
   cout << mochila(cajas, C, sol) << '\n';

   for (auto& s : sol) {
      cout << s << ' ';
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
