/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
using namespace std;

#include "PriorityQueue.h"


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Paciente {
    string nombre;
    int gravedad;
    int orden;
};

bool operator<(const Paciente& p1, const Paciente& p2) {
    return p1.gravedad < p2.gravedad || (p1.gravedad == p2.gravedad && p1.orden > p2.orden);
}

bool operator>(const Paciente& p1, const Paciente& p2) {
    return !(p1 < p2); 
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int n;
    cin >> n;

    if (n == 0)
        return false;

    char event;
    PriorityQueue<Paciente, greater<Paciente>> colaPacientes;
    string nombre;
    int gravedad;
    int totalP = 0;
    
    for (int i = 0; i < n; i++) {   
        cin >> event;

        if (event == 'I') {
            cin >> nombre >> gravedad;
            colaPacientes.push({nombre, gravedad, totalP});
            totalP++;
        } 
        else if (event == 'A') {
            cout << colaPacientes.top().nombre << '\n';
            colaPacientes.pop();
        }
    }

    cout << "---\n";

    return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   ifstream in("casos.txt");
   if (!in.is_open())
      cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
   auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

   while (resuelveCaso());

   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   cin.rdbuf(cinbuf);
#endif
   return 0;
}
