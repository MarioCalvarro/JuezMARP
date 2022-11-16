// DG, Mario Calvarro Marines
//
// Solución:
// Tenemos una cola con los clientes. Los 
// primeros N clientes los colocamos directamente 
// en las N cajas por orden y en una lista de prioridad
// ordenada por el tiempo que tardan y su caja (a menor valor, 
// mayor prioridad). El resto de clientes van sustituyendo 
// al cliente ocupado con mayor prioridad. Cuando ya no quedan 
// clientes la caja del último que sale es el resultado.
//
// El coste en el caso peor será recorrer toda la lista de clientes 
// insertando cada uno en la cola de prioridad, por tanto, O(n log(n)) 
// con n = nº de clientes 

#include <iostream>
#include <fstream>
#include <queue>
#include <utility>

#include "PriorityQueue.h"

size_t resolver(std::queue<size_t>& clientes, const size_t N) 
{
    size_t caja = 1;

    //Tiempo, caja ocupada
    PriorityQueue<std::pair<size_t, size_t>> ocupados;

    while (caja <= N && !clientes.empty())
    {
        ocupados.push({clientes.front(), caja});
        clientes.pop(); ++caja;
    }

    //En caso de que halla menos cajas que clientes
    if (caja > N) 
    {
        std::pair<size_t, size_t> saliente;
        while (!clientes.empty())
        {
            ocupados.pop(saliente); 
            ocupados.push({clientes.front() + saliente.first, saliente.second});
            clientes.pop();
        }
     
        ocupados.pop(saliente); 
        caja = saliente.second;
    }

    return caja;
}

bool resuelveCaso() 
{
    //Leer
    size_t N, C;
    std::cin >> N >> C;

    if (N == 0 && C == 0)
        return false;

    std::queue<size_t> clientes;

    for (size_t i = 0; i < C; ++i) 
    {
        size_t esp; std::cin >> esp;
        clientes.push(esp);
    }

    size_t sol = resolver(clientes, N);

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
