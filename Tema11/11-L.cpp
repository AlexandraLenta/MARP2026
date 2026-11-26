/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Matriz.h"
using namespace std;

/*@ <answer>

Resolvemos el problema mediante programacion dinamica, resolviendo primero subproblemas de tamaños menores
y para resolver el problema entero final.

Este problema se parece al problema del substring comun mas largo.

maxCanciones[i][j] -> la maxima cantidad de canciones comunes, en orden, que se pueden poner en la lista,
                      considerando todas las canciones hasta la i de la primera lista, y hasta la j de la 
                      segunda.

Casos base: 
    maxCanciones[i][0] = maxCanciones[0][j] = 0, ya que no pueden haber canciones comunes si en una lista
                                                 no hay ninguna cancion.

Subproblemas:
    maxCanciones[i][j] = maxCanciones[i - 1][j - 1] + 1, si lista1[i] == lista2[j]
                                                         ya que si las canciones que estamos considerando
                                                         ahora son iguales, la añadimos a la lista final,
                                                         a lo que teniamos construido hasta ahora
    
    maxCanciones[i][j] = max(maxCanciones[i - 1][j], maxCanciones[i][j - 1]), si lista1[i] != lista2[j]
                                                         si las canciones no son iguales, cogemos la lista
                                                         que nos ha dado el mayor resultado anteriormente,
                                                         sin considerar o la cancion actual de la primera
                                                         lista, o la actual de la segunda lista

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

vector<string> resolver(vector<string> const& l1, vector<string> const& l2) {
    int n = l1.size(), m = l2.size();
    Matriz<int> maxCanciones(n + 1, m + 1, 0);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (l1[i - 1] == l2[j - 1]) {
                maxCanciones[i][j] = maxCanciones[i - 1][j - 1] + 1;
            }
            else {
                maxCanciones[i][j] = max(maxCanciones[i - 1][j], maxCanciones[i][j - 1]);
            }
        }
    }
    
    vector<string> canciones;

    int index = maxCanciones[n][m];
    if (index != 0) {
        canciones = vector<string>(index);
        int i = n, j = m;
        while (i > 0 && j > 0) {
            if (l1[i - 1] == l2[j - 1]) {
                canciones[index - 1] = l1[i - 1];
                i--;
                j--;
                index--;
            }
            else if (maxCanciones[i - 1][j] > maxCanciones[i][j - 1]) {
                i--;
            }
            else {
                j--;
            }
        }
    }

    return canciones;
}

void resuelveCaso()
{
    stringstream ss;
    vector<vector<string>> songs(2);
    cin >> ws;
    for (int i = 0; i < 2; i++) {
        string line, word;
        getline(cin, line);
        stringstream ss(line);

        while (ss >> word) {
            songs[i].push_back(word);
        }
    }

    vector<string> canc = resolver(songs[0], songs[1]);

    for (auto const& c : canc) {
        cout << c << " ";
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