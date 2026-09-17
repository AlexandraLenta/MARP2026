
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

bool resuelveCaso() {

   // leer los datos de la entrada
    int n;
    cin >> n;

   if (n == 0)
      return false;

    priority_queue<long long int, vector<long long int>, greater<long long int>> numbers;
    long long int nr1;

    for (int i = 0; i < n; i++) {
        cin >> nr1;
        numbers.push(nr1);    
    }

   // resolver el caso posiblemente llamando a otras funciones
    long long int effort = 0;
    long long int nr2;

   while (numbers.size() > 1) {
        nr1 = numbers.top();
        numbers.pop();
        nr2 = numbers.top();
        numbers.pop();
        numbers.push(nr1+nr2);
        effort += nr1+nr2;
   }

   // escribir la solución
   cout << effort << '\n';

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
