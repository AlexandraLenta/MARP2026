/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include <algorithm>
#include <limits>

/*@ <answer>

La idea es maximizar el tiempo que ve las peliculas, - 10 minutos intermedios

We want to look at movies from 1 to j, where 0 <= j <= n, and n is the total nr of movies.

if j = 0 -> do nothing

else

prior(j) = latest request by finish time that does not overlap with j, so we can find the latest-ending movie
that can be seen if we see movie j.

for 0 <= i <= n, peli[i] = maximum possible time achievable considering movies from 1 to i (ordered by finish time)
peli[0] = 0; -> no movie, no time

result is peli[n], that is, from 1 to n, all the movies

              -> 0 if i = 0
             |
peli[i] = ---
             |
              -> max(peli[i - 1] (reject movie i), duration(i) + peli[prior(i)] (accept movie i)) if i > 0


 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

int resolver(vector<pair<long long, long long>> const &movies, vector<int> const& prior, int i)
{
   int n = movies.size();

   vector<long long> res(n + 1, 0);

   for (int i = 1; i < n + 1; i++) {
         long long diff = movies[i - 1].first - movies[i - 1].second - 10;

         res[i] = max(res[i - 1], diff + res[prior[i]]);
   }

   return res[n];
}

void resuelveCaso()
{
   int N;
   cin >> N;

   vector<pair<long long, long long>> movies(N);

   int d, sH, sM, dur;
   char filler;
   for (int i = 0; i < N; i++)
   {
      cin >> d >> sH >> filler >> sM >> dur;

      long long startHour = (long long)(d - 1) * 1440 + sH * 60 + sM;
      long long endHour = startHour + dur + 10;
      movies[i] = {endHour, startHour};
   }

   sort(movies.begin(), movies.end());

   vector<int> prior(N + 1, 0);

   for (int i = 1; i <= N; ++i)
   {
      long long start = movies[i - 1].second;
      prior[i] = upper_bound(movies.begin(), movies.end(), pair<long long, long long>{start, numeric_limits<long long>::max()}) - movies.begin();
   }
   
   cout << resolver(movies, prior, N) << '\n';
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
