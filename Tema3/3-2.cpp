/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;

#include "IndexPQ.h" // propios o los de las estructuras de datos de clase

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
    string pais;
    int puntos;
};

class ComparaEntrada {
public:
    bool operator()(const Entrada& e1, const Entrada& e2) {
        return e1.puntos > e2.puntos || (e1.puntos == e2.puntos && e1.pais < e2.pais); 
    }
};

bool resuelveCaso()
{
    // leer los datos de la entrada
    int n;
    cin >> n;

    if (!std::cin) // fin de la entrada
        return false;

    IndexPQ<string, Entrada, ComparaEntrada> paises;
    unordered_map<string, int> puntos;
    int p;
    string nom;

    for (int i = 0; i < n; i++) {
        cin >> nom;
        if (nom == "?") {
            cout << paises.top().elem << ' ' << paises.top().prioridad.puntos << '\n';
        }
        else {
            cin >> p;
            puntos[nom] += p; 
            paises.update(nom, { nom, puntos[nom]});
        }
    }

    cout << "---\n";

    return true;
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

    while (resuelveCaso())
        ;

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
#endif
    return 0;
}