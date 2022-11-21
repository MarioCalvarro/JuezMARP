// DG, Mario Calvarro Marines
//
// Solución:
//

#include <functional>
#include <iostream>
#include <fstream>

#include "PriorityQueue.h"

//Iniciales, atriles
using tDato = std::pair<size_t, size_t>;

struct comp_atriles 
{
    bool operator () (const tDato& lhs, const tDato& rhs)
    {
        return lhs.first / lhs.second > rhs.first / rhs.second;
    }
};

size_t resolver(PriorityQueue<tDato, comp_atriles> musicos, size_t& p) 
{
    tDato aux;

    while(p > 0 && musicos.top().first != 1)
    {
        musicos.pop(aux);
        ++aux.second;
        musicos.push(aux);
        --p;
    }

    return musicos.top().first / musicos.top().second;
}

bool resuelveCaso() 
{
    //Leer
    size_t p, n;
    std::cin >> p >> n;

    if (!std::cin)
        return false;

    //Iniciales, atriles
    PriorityQueue<tDato, comp_atriles> musicos;
    size_t aux;
    for (size_t i = 0; i < n; ++i) 
    {
        std::cin >> aux;
        musicos.push({aux, 1});
    }

    size_t p_llamada = p - n;

    std::cout << resolver(musicos, p_llamada) << '\n';

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
