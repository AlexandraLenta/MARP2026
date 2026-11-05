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
#include <queue>

/*@ <answer>

En este problema se pide hallar en número mínimo de salas necesarias para celebrar
todas las conferencias que se nos dan como datos.

Para esto, podemos utilizar un algoritmo voraz. La estrategia voraz consiste en 
coger cada conferencia en orden de inicio, y buscar una sala que quede libre en 
ese momento. Si no hay ninguna sala así, significa que se necesita otra sala.

Además, se pide imprimir la sala utilizada por cada conferencia, en orden de 
llegada. Por esto, mantenemos un vector con las conferencias en ese orden y creamos
otro vector que contenga los índices de las conferencias y lo ordenamos por tiempo 
de inicio.

Para identificar que sala quedará libre primero, creamos un priority queue con el
tiempo de finalización de las conferencias y la sala que quedará libre, ordenado
por conferencias que terminan antes. 

Recorremos las conferencias ordenadas. Por cada conferencia, miramos si empieza
después de la conferencia que termina más pronto. Si se da ese caso, esa conferencia
puede celebrarse en la sala que se liberará, y si no, se añade otra sala.

 @ </answer> */

//@ <answer>

void resuelveCaso()
{
    int N;
    cin >> N;

    int ini, fin;
    vector<pair<int, int>> horasConferencias(N);
    for (int i = 0; i < N; i++)
    {
        cin >> ini >> fin;
        horasConferencias[i] = {ini, fin};
    }

    vector<int> ordenIndex(N); // contiene los indices que corresponden a las conferencias
    for (int i = 0; i < N; i++) {
        ordenIndex[i] = i;
    }

    sort(ordenIndex.begin(), ordenIndex.end(), [&](int a, int b) { // ordenamos los indices segun el tiempo de inicio de las conferencias a las que apuntan dichos indices
        return horasConferencias[a].first < horasConferencias[b].first;
    });

    // priority queue de <tiempo final, numero sala>, para ordenar segun la conferencia que termina antes
    priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<pair<int, int>>> salas; 
    vector<int> salaPorConf(N); // el nr de la sala para cada conferencia
    int currSala = 0;

    for (int i : ordenIndex) {
        int sala;

        if (!salas.empty() && salas.top().first <= horasConferencias[i].first) {
            sala = salas.top().second;
            salas.pop();
        }
        else {
            currSala++;
            sala = currSala;
        }

        salaPorConf[i] = sala;
        salas.push({horasConferencias[i].second, sala});
    }
    
    cout << currSala << '\n';

    for (int i = 0; i < N; i++) {
        cout << salaPorConf[i] << ' ';
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
