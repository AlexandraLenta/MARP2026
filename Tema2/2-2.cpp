
/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

// #include "..."  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

 struct User {
    int timer;
    int id;
    int period;
 };

 bool operator<(User const& a, User const& b) {
    return b.timer < a.timer || (b.timer == a.timer && b.id < a.id);
 }

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


// O(k*log(n)), donde k es el numero de envios y n el numero de usuarios en la cola
bool resuelveCaso() {

   // leer los datos de la entrada
    int n;
    cin >> n;

   if (n == 0)
      return false;

    priority_queue<User> users;

    for (int i = 0; i < n; i++) {
        // leer usuarios
        int id, period;
        std::cin >> id >> period;
        users.push({period, id, period});
    }

    // primeros envios de info
    int k;
    std::cin >> k;

    while (k--) {
        User u = users.top();
        users.pop();
        cout << u.id << '\n';
        u.timer += u.period;
        users.push(u);
    }

    cout << "---\n";

   return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
// #ifndef DOMJUDGE
//    ifstream in("casos.txt");
//    if (!in.is_open())
//       cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
//    auto cinbuf = cin.rdbuf(in.rdbuf());
// #endif

   while (resuelveCaso());

   // para dejar todo como estaba al principio
// #ifndef DOMJUDGE
//    cin.rdbuf(cinbuf);
// #endif
   return 0;
}
