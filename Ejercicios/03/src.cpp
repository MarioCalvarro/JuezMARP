// DG, Mario Calvarro Marines
//
// Solución:
//
// Para la realización de este problema he hecho uso de 
// una cola de prioridad. En un primer momento, esta consistirá 
// en los elementos que se van a sumar. Según se van sumando los 
// elementos, se añade esta suma a la cola de prioridad en su 
// posición correspondiente para ser luego sumada (en cada ciclo 
// se suman los dos elementos menores). Por la conmutatividad y
// asociatividad de la suma no importa el orden en que se opere.
//
// Finalmente, se suman los costes parciales para ver el resultado
// final.

#include <iostream>
#include <fstream>
#include <queue>

#include "PriorityQueue.h"

// Coste O(Nlog(N)), con N número de elementos de aSumar, puesto que se realizan
// N operaciones (hay un total de N - 1 sumas) de coste logarítmico al insertar
// un elemento en aSumar y al eliminar el mínimo.
//
// aSumar siempre tendrá tamaño >= 1
size_t resolver(PriorityQueue<size_t>& aSumar) 
{
    std::queue<size_t> costes;
    size_t elem2, elem1 = aSumar.top(); aSumar.pop();
    size_t res = 0;

    while (!aSumar.empty())
    {
        elem2 = aSumar.top(); aSumar.pop();
 
        costes.push(elem1 + elem2);
        aSumar.push(elem1 + elem2);

        elem1 = aSumar.top(); aSumar.pop();
    }
    
    while (!costes.empty()) 
    {
        res += costes.front();
        costes.pop();
    }

    return res;
}

bool resuelveCaso() 
{
    //Leer
    size_t N;
    std::cin >> N;

    if (N == 0)
        return false;

    PriorityQueue<size_t> aSumar;
    for (size_t i = 0; i < N; ++i)
    {
        size_t elem; std::cin >> elem;
        aSumar.push(elem);
    }

    size_t sol = resolver(aSumar);

    //Escribir
    std::cout << sol << '\n';

    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while(resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}
