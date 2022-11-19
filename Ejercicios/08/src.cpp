// DG, Mario Calvarro Marines
//
// Solución:
// Si ambos miembros son menores que el primero, 
// el nuevo primero será el mayor de los menores. 
// Si ambos son mayores, el nuevo primero será el menor de 
// los mayores.
//
// Coste:
// Las operaciones por cada pareja son de coste logarítmico.

#include <iostream>
#include <fstream>

#include "PriorityQueue.h"

bool resuelveCaso() 
{
    //Leer
    size_t primero, nParejas;
    std::cin >> primero >> nParejas;

    if (primero == 0 || nParejas == 0)
        return false;

    PriorityQueue<size_t> mayores;
    PriorityQueue<size_t, std::greater<size_t>> menores;

    size_t pair1, pair2;
    for (size_t i = 0; i < nParejas; ++i) 
    {
        std::cin >> pair1 >> pair2;

        if (pair1 < primero)
            menores.push(pair1);
        else 
            mayores.push(pair1);

        if (pair2 < primero)
            menores.push(pair2);
        else 
            mayores.push(pair2);

        if (menores.size() < mayores.size())
        {
            menores.push(primero);
            mayores.pop(primero);
        }
        else if (mayores.size() < menores.size())
        {
            mayores.push(primero);
            menores.pop(primero);
        }

        std::cout << primero << ' ';
    }

    std::cout << '\n';

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
