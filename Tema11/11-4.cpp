/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h"
using namespace std;

/*@ <answer>



 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

int resolver_rec(vector<int> const& v, int i, int j, Matriz<int>& res) {
    if (i < 0 || i >= v.size() || j < 0 || j >= v.size()) 
        return 0;
        
    int& r = res[i][j];

    if (r == -1) {
        if (i == j) {
            r = v[i];
        }
        else if (i > j) {
            r = 0;
        }
        else {
            // primer caso: comemos i;
            int i1 = i + 1;
            int j1 = j;
            // cual se come devoradora?
            if (v[i1] > v[j1]) {
                i1++;
            }
            else {
                j1--;
            }

            // segundo caso: comemos j
            int j2 = j - 1;
            int i2 = i;
            // cual se come devoradora?
            if (v[i2] > v[j2]) {
                i2++;
            }
            else {
                j2--;
            }

            r = max(resolver_rec(v, i1, j1, res) + v[i], resolver_rec(v, i2, j2, res) + v[j]);
        }
    }
    return r;
}

void resuelveCaso()
{
    int N;
    cin >> N;

    int a;
    vector<int> nr(N);
    for (int i = 0; i < N; i++) {
        cin >> a;
        nr[i] = a;
    }

    Matriz<int> res(N, N, -1);

    cout << resolver_rec(nr, 0, N - 1, res) << '\n';
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
