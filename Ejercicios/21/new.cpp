// DG, Mario Calvarro Marines

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <unordered_map>

using Digrafo = std::vector<std::vector<size_t>>;

enum Finales {
    Siempre, 
    Posible,
    Nunca
};

bool dfs (const Digrafo &grafo, std::stack<size_t> &pila, std::vector<bool> &marcados, const size_t k)
{
    bool final = false;
    marcados[k] = true;

    for (auto v : grafo[k])
    {
        if (v < grafo.size())
        {
            if (!marcados[v])
                final |= dfs(grafo, pila, marcados, v);
        }
        else
        {
            final = true;    
        }
    }

    pila.push(k);
    return final;
}

Finales resolver(const Digrafo &grafo) 
{
    std::stack<size_t> pila;
    std::vector<bool> marcados (grafo.size(), false);

    bool fin = dfs(grafo, pila, marcados, 0);

    std::unordered_map<size_t, size_t> pos; 
    size_t index = 0; bool ciclo = false;
    while(!pila.empty())
    {
        pos[pila.top()] = index;
        ++index;
        pila.pop();
    }

    for (size_t i = 0; i < pos.size(); ++i)
    {
        for (auto v : grafo[i])
        {
            if (v < grafo.size() && pos[i] > pos[v])
                ciclo = true;
        }
    }
    
    if (fin && ciclo) return Posible;
    else if (!fin && ciclo) return Nunca;
    else return Siempre;
}

bool resuelveCaso() 
{
    //Leer
    size_t L;
    std::cin >> L;

    if (!std::cin)
        return false;

    Digrafo grafo = Digrafo(L);

    char instruccion; size_t salto;
    for (size_t i = 0; i < L; ++i)
    {
        std::cin >> instruccion;
        if (instruccion == 'A')
            grafo[i].push_back(i + 1);
        else if (instruccion== 'J')
        {
            std::cin >> salto;
            grafo[i].push_back(salto - 1);
        }
        else if (instruccion == 'C')
        {
            std::cin >> salto;
            grafo[i].push_back(i + 1);
            grafo[i].push_back(salto - 1);
        }
    }

    //Escribir
    switch (resolver(grafo)) {
        case Siempre:
            std::cout << "SIEMPRE\n";
            break;
        case Posible:
            std::cout << "A VECES\n";
            break;
        case Nunca:
            std::cout << "NUNCA\n";
            break;
    }

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
