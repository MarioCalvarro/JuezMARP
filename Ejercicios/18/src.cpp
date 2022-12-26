// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <unordered_map>

#include "Digrafo.h"

void dfs(const Digrafo &gr, std::stack<int> &sol, std::vector<bool> &marcados, const size_t k)
{
    marcados[k] = true;

    for (auto v : gr.ady(k)) 
        if (!marcados[v]) dfs(gr, sol, marcados, v);

    sol.push(k);
}

bool resolver(const Digrafo &gr, std::vector<int> &res) 
{
    std::stack<int> sol;

    std::vector<bool> marcados (gr.V(), false);
    for (int i = 0; i < gr.V(); ++i)
        if (!marcados[i]) dfs(gr, sol, marcados, i);

    std::vector<int> pos (gr.V());
    int index = 0;
    while(!sol.empty()) 
    {
        pos[sol.top()] = index;
        res.push_back(sol.top());
        ++index;
        sol.pop();
    }

    for(size_t i = 0; i < gr.V(); ++i)
    {
        for (auto ite : gr.ady(i))
        {
            //La posición del padre es posterior a la del hijo
            if (pos[i] > pos[ite]) 
                return false;
        }
    }

    return true;
}

bool resuelveCaso() 
{
    //Leer
    Digrafo gr = Digrafo(std::cin);

    if (!std::cin)
        return false;

    std::vector<int> res;

    //Escribir
    if (resolver(gr, res)) 
    {
        for (size_t i = 0; i < res.size(); ++i)
        {
            std::cout << res[i] + 1 << ' ';
        }
    }
    else 
    {
        std::cout << "Imposible";
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
