// DG, Mario Calvarro Marines
//
// Solución:
// Realizamos una cola de prioridad
// en la que el primer elemento será el 
// de mayor urgencia y, en caso de igualdad, 
// el que antes haya llegado. 
// Cuando se realiza un ingreso se añade el elemento
// a la cola de prioridad y se suma uno a las llegadas. 
// Cuando se realiza una atención se elimina el primer
// paciente de la cola y se muestra su nombre.

#include <iostream>
#include <fstream>
#include <utility>
#include <string>
 
#include "PriorityQueue.h"

struct comp_periods 
{
    //Id, urgencia, llegada 
    bool operator() (const std::tuple<std::string, size_t, size_t>& lhs, const std::tuple<std::string, size_t, size_t>& rhs) 
    {
        auto[lId, lUrgencia, lLlegada] = lhs;
        auto[rId, rUrgencia, rLlegada] = rhs;
        return lUrgencia > rUrgencia || (lUrgencia == rUrgencia && lLlegada < rLlegada);
    }
};

// Id, urgencia, llegada
// Coste O(mlog(n)) con m = número de eventos y n = nº de pacientes en la lista, puesto
// que cada iteración se realizan operaciones de coste logarítmico (ya sea insertar o eliminar).
bool resuelveCaso() 
{
    //Leer
    size_t N; std::cin >> N;
    size_t llegada = 0;

    if (N == 0)
        return false;

    char evento; std::string id; size_t urgencia;
    PriorityQueue<std::tuple<std::string, size_t, size_t>, comp_periods> pacientes; 
    for (size_t i = 0; i < N; ++i) 
    {
        std::cin >> evento; 
        if (evento == 'I') 
        {
            std::cin >> id; std::cin >> urgencia;
            pacientes.push({id, urgencia, llegada});
            ++llegada;
        }
        else if (evento == 'A') 
        {
            auto [idPac, urgPac, llegadaPac] = pacientes.top(); pacientes.pop();
            std::cout << idPac << '\n';
        }
    }

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
