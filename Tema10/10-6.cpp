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

in j -> ultima zi care am aleso, ceea ce inseamna ca facem max intre daca alegem azi and then ultima zi posibila aleasa...?

de exemplu in ultimul exemplu daca alegem 8, e mai mare decat pana atunci, which means we choose 8... but...

astazi maxim este max intre maxim peste o zi in urma + de azi, si maxim de ieri...
 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

int resolver_rec(vector<int> const& v) {
    int n = v.size();

    vector<int> res(n + 1, 0);
    res[1] = v[0];

    for (int i = 2; i <= n; i++) {
        res[i] = max(res[i - 1], res[i - 2] + v[i - 1]);
    }

    return res[n];
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

    cout << resolver_rec(nrs) << '\n'; 
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
