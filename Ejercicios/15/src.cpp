// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

#include "Grafo.h"

size_t bfs(const Grafo &grafo, const size_t origen, size_t tiempo, std::vector<bool> &marcados)
{
    size_t res = 1;
    std::queue<size_t> cola;
    marcados[origen] = true;
    size_t nivelActual = 1, nuevoNivel = 0;
    cola.push(origen);
    while(!cola.empty() && tiempo > 0)
    {
        size_t valor = cola.front(); cola.pop();
        for (auto nuevoValor : grafo.ady(valor))
        {
            if (!marcados[nuevoValor])
            {
                marcados[nuevoValor] = true;
                cola.push(nuevoValor);
                ++res; ++nuevoNivel;
            }
        }
        --nivelActual;
        if (nivelActual == 0)
        {
            nivelActual = nuevoNivel;
            nuevoNivel = 0;
            --tiempo;
        }
    }

    return res;
}

bool resuelveCaso() 
{
    //Leer
    Grafo grafo = Grafo(std::cin);

    if (!std::cin)
        return false;

    size_t consultas, origen, tiempo;
    std::cin >> consultas;
    for (size_t i = 0; i < consultas; ++i) 
    {
        std::vector<bool> marcados(grafo.V(), false);
        std::cin >> origen >> tiempo;
        --origen;
        std::cout << grafo.V() - bfs(grafo, origen, tiempo, marcados)<< '\n';
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
