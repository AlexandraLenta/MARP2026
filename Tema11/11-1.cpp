/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "Matriz.h"
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

struct Objeto {
    int tiempo;
    int valor;
};

int resolver_recu(vector<Objeto> const& objetos, int i, int j, Matriz<int>& mochila) {
    if (mochila[i][j] != -1) {
        return mochila[i][j]; // ya resuelto
    }
    
    if (i == 0 || j == 0) {
        mochila[i][j] = 0;
    }

    else if (objetos[i - 1].tiempo > j) {
        mochila[i][j] = resolver_recu(objetos, i - 1, j, mochila);
    }
    else {
        mochila[i][j] = max(resolver_recu(objetos, i - 1, j, mochila), resolver_recu(objetos, i - 1, j - objetos[i - 1].tiempo, mochila) + objetos[i - 1].valor);
    }

    return mochila[i][j];
}

int resolver(vector<Objeto> const& objetos, int T, int& nrObj, vector<Objeto>& res) {
    int n = objetos.size();
    
    Matriz<int> tesoros(n + 1, T + 1, -1);

    int valor = resolver_recu(objetos, n, T, tesoros);

    int i = n, j = T;

    nrObj = 0;

    while (i > 0 && j > 0) {
        if (tesoros[i][j] != tesoros[i - 1][j]) {
            j = j - objetos[i - 1].tiempo;
            nrObj++;
            res.push_back({objetos[i - 1]});
        }
        i--;
    }

    return valor;
}

void resuelveCaso()
{
    int T, N;
    cin >> T >> N;

    int a, b;
    vector<Objeto> objetos(N);
    

    for (int i = 0; i < N; i++) {
        cin >> a >> b;
        objetos[i] = {a*3, b};
    }

    int nr = 0;
    vector<Objeto> res;
    int value = resolver(objetos, T, nr, res);

    cout << value << '\n' << nr << '\n';

    for (auto& o : res) {
        cout << o.tiempo / 3 << ' ' << o.valor << '\n';
    }

    cout << "---\n";
    
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
