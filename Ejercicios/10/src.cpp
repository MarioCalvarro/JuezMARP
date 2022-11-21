// DG, Mario Calvarro Marines
//
// Solución:
// Ordenamos la lista dando prioridad 
// a aquellos conjuntos de un instrumento
// en los que la división entre nº de músicos 
// y nº de atriles en máxima.
// Con esto vamos dando atriles al primer 
// elemento de la cola hasta que no queden más 
// atriles.
// Si la división no es exacta, debemos sumar 
// 1 para tener el máximo.

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
        size_t lOp = lhs.first / lhs.second;
        size_t rOp = rhs.first / rhs.second;
        lOp += (lhs.first % lhs.second == 0)? 0 : 1;
        rOp += (rhs.first % rhs.second == 0)? 0 : 1;

        return lOp > rOp;
    }
};

//Se ejecuta el bucle p veces con operaciones de coste log(n), n = nº de tipos de 
//instrumento: O(p log(n))
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

    size_t sol = musicos.top().first / musicos.top().second;
    sol += (musicos.top().first % musicos.top().second == 0)? 0 : 1;

    return sol;
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
