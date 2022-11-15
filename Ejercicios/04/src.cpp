// DG, Mario Calvarro Marines
//
// Solución:
// Realizamos una cola de prioridad que compara 
// los elementos para ver cuál lleva menos tiempo 
// acumulado (esté será el de mayor prioridad). 
// Una vez que un elemento salga se sumará su periodo
// al acumulado y se volverá a insertar en la cola de 
// prioridad hasta que la vuelva a tocar.

#include <iostream>
#include <fstream>
#include <utility>
 
#include "PriorityQueue.h"

struct comp_periods 
{
    //Id, periodo
    bool operator() (const std::tuple<size_t, size_t, size_t>& lhs, const std::tuple<size_t, size_t, size_t>& rhs) 
    {
        auto [lId, lAcum, lPer] = lhs;
        auto [rId, rAcum, rPer] = rhs;
        return lAcum < rAcum || (lAcum == rAcum && lId < rId);
    }
};

// Coste O(mlog(n)), con m = nº de usuarios a mostrar y n = nº de elementos de la cola con prioridad, puesto que 
// se realizan m iteraciones (se muestran m usuarios) y en cada una se realizan operaciones de coste logarítmico
// sobre n (eliminar un elemento o añadirlo).
//
// Id, acumulado, periodo
void resolver(PriorityQueue<std::tuple<size_t, size_t, size_t>, comp_periods>& elementos, const size_t tiempo) 
{
    for (size_t i = 0; i < tiempo; ++i)
    {
        auto[id, acumulado, periodo] = elementos.top(); elementos.pop();
        std::cout << id << '\n';

        acumulado += periodo; elementos.push({id, acumulado, periodo});
    }
}

bool resuelveCaso() 
{
    //Leer
    //Identificador, periodo
    size_t N; std::cin >> N;

    if (N == 0)
        return false;

    //Id, acumulado, periodo
    PriorityQueue<std::tuple<size_t, size_t, size_t>, comp_periods> elementos;

    for (size_t i = 0; i < N; ++i) 
    {
        size_t id, periodo;
        std::cin >> id; std::cin >> periodo;
        elementos.push({id, periodo, periodo});
    }

    size_t tiempo; std::cin >> tiempo;

    resolver(elementos, tiempo);

    std::cout << "---\n";

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
