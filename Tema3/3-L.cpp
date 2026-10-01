/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
using namespace std;
#include "IndexPQ.h"
#include <map>

struct Entrada
{
   int canal;
   int minutos;
};

bool operator>(const Entrada &e1, const Entrada &e2)
{
   return e1.minutos > e2.minutos || (e1.minutos == e2.minutos && e1.canal < e2.canal);
}

// O((c + n) * log(c)), donde c es el numero de canales y n es el numero de actualizaciones
void resuelveCaso()
{
   int d, c, n;
   cin >> d >> c >> n;

   IndexPQ<int, std::greater<int>> colaCanales(c); // una cola de c entradas. prioridad = audiencia, elem = nr canal
   IndexPQ<Entrada, std::greater<Entrada>> colaMinutos(c);

   int c0;
   for (int i = 0; i < c; i++)
   { // O(c * log(c)), donde c es el numero de canales
      cin >> c0;
      colaCanales.push(i, c0); // i + 1 pq los id de los canales empiezan en 1
      colaMinutos.push(i, {i, 0});
   }

   int min, canales, canal, audiencia, minAnt = 0;

   for (int i = 0; i < n; i++)
   { // O(n * log(c)), donde n = numero de actualizaciones, y c = numero de canales
      cin >> min >> canales;
      colaMinutos.update(colaCanales.top().elem, {colaCanales.top().elem, colaMinutos.priority(colaCanales.top().elem).minutos + min - minAnt});

      for (int j = 0; j < canales; j++)
      {
         cin >> canal >> audiencia;
         colaCanales.update(canal - 1, audiencia);
      }
      minAnt = min;
   }

   colaMinutos.update(colaCanales.top().elem, {colaCanales.top().elem, colaMinutos.priority(colaCanales.top().elem).minutos + d - minAnt});
   
   while (!colaMinutos.empty())
   { // O(c * log(c)), donde c = numero de canales
      int elem = colaMinutos.top().elem;
      int minutos = colaMinutos.top().prioridad.minutos;
      colaMinutos.pop();
      if (minutos > 0)
      {
         cout << elem + 1 << ' ' << minutos << '\n';
      }
   }

   cout << "---\n";
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
