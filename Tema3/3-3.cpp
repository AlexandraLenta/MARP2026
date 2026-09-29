/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
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

struct Entrada {
    int ini;
    int fin;
    int periodo = 0;
};

bool operator>(const Entrada& e1, const Entrada& e2) {
    return e1.ini > e2.ini;
}

void resuelveCaso()
{

    // leer los datos de la entrada
    int n, m, t;
    cin >> n >> m >> t;

    int in, f, p;

    priority_queue<Entrada, vector<Entrada>, greater<Entrada>> cola;
    
    for (int i = 0; i < n; i++)
    {
        cin >> in >> f;
        cola.push({in, f});
        // cout << "pushed " << i << ' ' << f << '\n';
    }
    for (int i = 0; i < m; i++) {
        cin >> in >> f >> p;
        cola.push({in, f, p}); 
        // cout << "pushed " << i << ' ' << f << '\n';
    }

    // pop, if period > 0 && the ini + period < t, push it back with the new values
    // guardar highest 
    Entrada e = cola.top();
    cola.pop();

    while (e.ini < t && !cola.empty()) {
        // cout << e.ini << e.fin << '\n';
        if (cola.top().ini < t && e.fin > cola.top().ini) {
            cout << "SI\n";
            return;
        }
        if (e.periodo > 0 && e.ini + e.periodo < t) {
            cola.push({e.ini + e.periodo, e.fin + e.periodo, e.periodo});
        }
        e = cola.top();
        cola.pop();
    }
    cout << "NO\n";
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main()
{
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    if (!in.is_open())
        cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
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
