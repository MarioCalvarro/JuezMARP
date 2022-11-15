// DG, Mario Calvarro Marines
//
// Solución:
//
// Utilizamos una cola de prioridad en la que se colocan los 
// elementos considerando como mínimo aquel que empiece antes.
// Con esta cola lo que hacemos es mirar si el inicio de un 
// elemento es inferior al final del siguiente (se va almacenando 
// en currentTime). Si se da este caso, hay conflictos, sino, se 
// continúa. 
//
// El coste en el caso peor será el caso de una cola con tareas periódicas
// sin conflicto que se den cada minuto. En este caso, la operación 
// push es de coste logarítmico por lo que el algoritmo será O(T * log(n)) con 
// n = nº elementos de la cola y T = Tiempo a observar

#include <iostream>
#include <fstream>
#include <tuple>

#include "PriorityQueue.h"

//Inicio, final, periódica, periodo
using tData = std::tuple<size_t, size_t, bool, size_t>;

struct comp_prio 
{
    bool operator() (const tData& left, const tData& right)
    {
        auto[lIn, lFin, lPer, lPerTime] = left;
        auto[rIn, rFin, rPer, wPerTime] = right;

        return lIn < rIn || (lIn == rIn && lFin < rFin);
    }
};

//Hay conflictos -> True
bool resolver(PriorityQueue<tData, comp_prio>& datos, const size_t T) 
{
    size_t currentTime = 0;

    while (currentTime < T && !datos.empty())
    {
        tData elem; datos.pop(elem);
        auto [in, fin, per, perTime] = elem;

        if (currentTime > in)
            return true;

        currentTime = fin;
        
        if (per)
            datos.push({in + perTime, fin + perTime, per, perTime});
    }

    //Por si se solapan las últimas tareas 
    if (!datos.empty())
    {
        tData elem; datos.pop(elem);
        auto [in, fin, per, perTime] = elem;

        if (T > in)
            return true;
    }

    return false;
}

bool resuelveCaso() 
{
    //Leer
    size_t N, M, T;
    std::cin >> N; 

    if (!std::cin)
        return false;

    std::cin >> M >> T;

    //Inicio, final, periódica, periodo
    tData elem;
    PriorityQueue<tData, comp_prio> datos;
    for (size_t i = 0; i < N; ++i)
    {
        size_t in, fin;
        std::cin >> in >> fin;
        elem = {in, fin, false, 0};
        datos.push(elem);
    }

    for (size_t i = 0; i < M; ++i)
    {
        size_t in, fin, per;
        std::cin >> in >> fin >> per;
        elem = {in, fin, true, per};
        datos.push(elem);
    }

    std::cout << (resolver(datos, T)? "SI" : "NO") << '\n';

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
