/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int resolver(vector<int> const& enemigos, vector<int> const& aliados) {
    int count = 0;

    int i = 0, j = 0;

    while (i < enemigos.size() && j < aliados.size()) {
        if (enemigos[i] <= aliados[j]) {
            count++;
            i++;
            j++;
        }
        else {
            j++;
        }
    }

    return count;
}

void resuelveCaso()
{

    int N;
    cin >> N;

    vector<int> enemigos(N);
    vector<int> aliados(N);

    for (auto& e : enemigos) {
        cin >> e;
    }

    for (auto& a : aliados) {
        cin >> a;
    }

    sort(enemigos.begin(), enemigos.end());
    sort(aliados.begin(), aliados.end());
    
    cout << resolver(enemigos, aliados) << '\n';
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
