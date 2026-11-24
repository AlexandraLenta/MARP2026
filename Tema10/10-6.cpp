/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
using namespace std;
#include <vector>

/*@ <answer>

res[i][j] = maximo profit teniendo en cuenta las actuaciones entre los dias i y j

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

int resolver_rec(vector<int> const& v, int i, vector<int>& res) {
    if (i > v.size()) {
        return 0;
    }
    int& r = res[i];

    if (r == -1) {
        if (i == v.size()) {
            r = v[i]; // solo actuamos este dia
        }
        else {
            r = max(resolver_rec(v, i + 2, res) + v[i], resolver_rec(v, i + 1, res));
        }
    }
    return r;
}

void resuelveCaso()
{
    int N;
    cin >> N;
    vector<int> nrs(N);
    int a;
    for (int i = 0; i < N; i++) {
        cin >> a;
        nrs[i] = a;
    }

    vector<int> res(N, -1);
    cout << resolver_rec(nrs, 0, res) << '\n'; 
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
