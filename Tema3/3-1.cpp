/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
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

bool resuelveCaso()
{

    // leer los datos de la entrada
    int central, m;

    cin >> central >> m;

    if (central == 0 && m == 0)
        return false;

    priority_queue<int> menor;
    priority_queue<int, vector<int>, greater<int>> mayor;

    int a;
    for (int i = 0; i < m; i++)
    {
        cin >> a;
        if (a < central)
        {
            menor.push(a);
        }
        else
        {
            mayor.push(a);
        }

        cin >> a;
        if (a < central)
        {
            menor.push(a);
        }
        else
        {
            mayor.push(a);
        }

        if (menor.size() > mayor.size())
        {
            mayor.push(central);
            central = menor.top();
            menor.pop();
        }
        else if (menor.size() < mayor.size())
        {
            menor.push(central);
            central = mayor.top();
            mayor.pop();
        }

        cout << central << ' ';
    }
    cout << '\n';

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
