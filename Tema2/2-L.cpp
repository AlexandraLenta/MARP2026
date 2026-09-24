/*@ <authors>
 * MARP39 Alexandra Lenta
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

/*@ <answer>

 Se usa un priority queue que ordena la cola segun el grupo de instrumentos con mas gente compartiendo una partitura.
 Primero se da una partitura a cada grupo, y luego se coge el numero de partituras que quedan y se reparte una a cada
 grupo que la necesita mas.

 Coste espacial: O(n), donde n es el numero de grupos de instrumentos.
 Coste de tiempo: O(n * log n) para crear la cola inicial, luego
                O(m * log n) para el algoritmo, donde n = numero de instrumentos y 
                                                      m = partituras - n

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct GrupoInstrumentos {
    int gente;
    int partituras;
};

// Divide num1 entre num2 con redondeo hacia arriba
int divideRoundUp(int dividend, int divisor) {
    return (dividend + (divisor - 1)) / divisor;
}

bool operator<(const GrupoInstrumentos& g1, const GrupoInstrumentos& g2) {
    return divideRoundUp(g1.gente, g1.partituras) < divideRoundUp(g2.gente, g2.partituras);
}

bool resuelveCaso()
{
    int p, n;
    cin >> p >> n;

    int m;

    priority_queue<GrupoInstrumentos> grupos;
    
    for (int i = 0; i < n; i++) { // O(n*logn)
        cin >> m;
        grupos.push({m, 1}); //O(logn)
    }

    p -= n; // hemos dado 1 partitura a cada grupo

    
    GrupoInstrumentos g;
    while (p > 0) { // O((p-n) * log n)
        g = grupos.top();
        grupos.pop();
        g.partituras++;
        grupos.push(g); // O(log n)
        p--;
    }

    g = grupos.top();
    cout << divideRoundUp(g.gente, g.partituras) << '\n';

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
