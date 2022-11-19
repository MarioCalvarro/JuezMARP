// DG, Mario Calvarro Marines

#include <algorithm>
#include <functional>
#include <iostream>
#include <fstream>
#include <vector>

#include "PriorityQueue.h"

void resolver(PriorityQueue<int, std::greater<int>>& pilasA, PriorityQueue<int, std::greater<int>>& pilasB, const size_t N) 
{
    int auxA, auxB;
    while(!pilasA.empty() && !pilasB.empty())
    {
        size_t i = 0, res = 0;
        std::vector<int> vA, vB;

        while(!pilasA.empty() && !pilasB.empty() && i < N)
        {
            pilasA.pop(auxA); pilasB.pop(auxB);
            res += std::min(auxA, auxB);

            int minAB = std::min(auxA, auxB);
            auxA = std::max(0, auxA - minAB); 
            auxB = std::max(0, auxB - minAB); 

            vA.push_back(auxA); vB.push_back(auxB);
            ++i;
        }

        std::cout << res << ' ';

        for (size_t i = 0; i < vA.size(); ++i)
            if (vA[i] > 0) pilasA.push(vA[i]);

        for (size_t i = 0; i < vB.size(); ++i)
            if (vB[i] > 0) pilasB.push(vB[i]);
    }
}

bool resuelveCaso() 
{
    //Leer
    size_t N, A, B;
    std::cin >> N >> A >> B;

    if (!std::cin)
        return false;

    PriorityQueue<int, std::greater<int>> pilasA;
    PriorityQueue<int, std::greater<int>> pilasB;

    int aux;
    for (size_t i = 0; i < A; ++i)
    {
        std::cin >> aux; 
        pilasA.push(aux);
    }

    for (size_t i = 0; i < B; ++i)
    {
        std::cin >> aux; 
        pilasB.push(aux);
    }

    resolver(pilasA, pilasB, N);

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
