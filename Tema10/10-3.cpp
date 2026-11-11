/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include <algorithm>
#include "EnterosInf.h"

void resolver(int C, vector<pair<int, int>> const &valor, long long& formasNr, int& costeMin, int& numMin)
{
   int n = valor.size();

   vector<long long> formas(C + 1, 0);
   // vector<vector<int>> formas(n + 1, vector<int>(C + 1, 0));
   vector<EntInf> minimo(C + 1, Infinito);
   vector<EntInf> costeMinimo(C + 1, Infinito);

   formas[0] = 1; // una forma de sumar 0
   // formas[0][0] = 1;
   minimo[0] = 0; // minimas cuerdas para sumar longitud 0
   costeMinimo[0] = 0;

   for (int i = 1; i <= n; i++)
   {
      for (int j = C; j >= valor[i - 1].first; j--) {
         minimo[j] = min(minimo[j], minimo[j - valor[i - 1].first] + 1);
         formas[j] = (formas[j - valor[i - 1].first] + formas[j]);
         
         costeMinimo[j] = min(costeMinimo[j], costeMinimo[j - valor[i - 1].first] + valor[i - 1].second);
      }
   }

   // for (int i = 1; i <= n; i++) {
   //    formas[i][0] = 1;
   //    for (int j = 1; j <= C; j++) {
   //       if (j < valor[i - 1].first) {
   //          formas[i][j] = formas[i - 1][j];
   //       }
   //       else {
   //          formas[i][j] = formas[i - 1][j] + formas[i - 1][j - valor[i - 1].first];
   //       }
   //    }
   // }

   formasNr = formas[C];
   costeMin = costeMinimo[C].number();
   numMin = minimo[C].number();
}

//@ <answer>

void resuelveCaso()
{
   int N, L;
   cin >> N >> L;

   int a, b;
   vector<pair<int, int>> cordelesCoste(N);

   for (int i = 0; i < N; i++)
   {
      cin >> a >> b;
      cordelesCoste[i] = {a, b};
   }

   long long formas; int costeMin, numMin;
   
   resolver(L, cordelesCoste, formas, costeMin, numMin);

   if (formas == 0) {
      cout << "NO\n";
      return;
   }

   cout << "SI " << formas << ' ' << numMin << ' ' << costeMin << '\n';
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
