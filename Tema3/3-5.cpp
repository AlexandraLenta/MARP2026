/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
using namespace std;
#include <unordered_map>
#include "IndexPQ.h"
#include <algorithm>

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Entry {
    int quantity;
    string name;
};

bool operator>(const Entry& e1, const Entry& e2) {
    return e1.quantity > e2.quantity || (e1.quantity == e2.quantity && e1.name < e2.name);
 }

void resuelveCaso()
{
    int N;
    cin >> N;

    IndexPQ<Entry, std::greater<Entry>> pqStock(N);
    IndexPQ<Entry, std::greater<Entry>> pqSold(N);

    unordered_map<string, int> index;

    string name; int c;
    for (int i = 0; i < N; i++) {
        cin >> name >> c;
        
        index[name] = i;

        pqStock.push(i, {c, name});
        pqSold.push(i, {0, name});
    }

    int E;
    cin >> E;

    char type;

    for (int i = 0; i < E; i++) {
        cin >> type;

        if (type == 'C') {
            cin >> name >> c;
            int q = pqStock.priority(index[name]).quantity;
            int a = q - c;

            int remaining = a >= 0 ? a : 0;

            int sold = clamp(q - remaining, 0, q); 

            pqStock.update(index[name], {remaining, name});

            pqSold.update(index[name], { pqSold.priority(index[name]).quantity + sold, name});

            // cout << "STOCK: " << pqStock.priority(index[name]).name << ' ' << pqStock.priority(index[name]).quantity << '\n';
            // cout << "SOLD: " << pqSold.priority(index[name]).name << ' ' << pqSold.priority(index[name]).quantity << '\n';
        }
        else if (type == 'P') {
            cin >> name >> c;

            pqStock.update(index[name], {pqStock.priority(index[name]).quantity + c, name});
        }
        else if (type == 'Q') {
            if (pqStock.top().prioridad.quantity > 0)
                cout << pqStock.top().prioridad.name << ' ' << pqStock.top().prioridad.quantity;
            else 
                cout << "NO HAY";
            cout  << "; ";

            if (pqSold.top().prioridad.quantity > 0)
                cout << pqSold.top().prioridad.name << ' ' << pqSold.top().prioridad.quantity;
            else
                cout << "NO HAY";
            cout  << '\n'; 
        }
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
