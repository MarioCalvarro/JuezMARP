// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>

size_t resolver(const size_t casillas, const size_t K, const std::unordered_map<size_t, size_t> &teleport) 
{
    std::queue<size_t> q;
    std::vector<size_t> distancia (casillas + 1);
    for (size_t i = 1; i <= casillas; ++i) 
    {
        distancia[i] = casillas;
    }
    distancia[1] = 0;

    q.push(1);
    bool end = false;
    while(!end)
    {
        size_t current = q.front();
        q.pop();
        for (size_t i = 1; i <= K && current + i <= casillas; ++i)
        {
            size_t next = (teleport.count(current + i))? teleport.at(current + i) : current + i;

            if (distancia[next] > distancia[current] + 1)
            {
                q.push(next);
                distancia[next] = distancia[current] + 1;
                if (next == casillas) {
                    end = true;
                }
            }
        }
    }

    return distancia[casillas];
}

bool resuelveCaso() 
{
    //Leer
    size_t N, K, S, E;
    std::cin >> N >> K >> S >> E;

    if (N == 0 && K == 0 && S == 0 && E == 0)
        return false;

    size_t aux1, aux2;

    std::unordered_map<size_t, size_t> teleport(S + E);
    for (size_t i = 0; i < S + E; ++i) 
    {
        std::cin >> aux1 >> aux2;
        teleport[aux1] = aux2;
    }

    //Escribir
    std::cout << resolver(N * N, K, teleport) << '\n';

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
