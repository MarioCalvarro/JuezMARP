// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <algorithm>

size_t resolver(const std::vector<std::pair<size_t, size_t>> &edificios) 
{
    size_t sol = 1;
    size_t pos_tunel = edificios[0].second;

    for (size_t i = 1; i < edificios.size(); ++i)
    {
        if (edificios[i].first >= pos_tunel)
        {
            pos_tunel = edificios[i].second;
            ++sol; 
        }
        else 
            pos_tunel = std::min(pos_tunel, edificios[i].second);
    }

    return sol;
}

bool resuelveCaso() 
{
    //Leer
    size_t N;
    std::cin >> N;

    if (N == 0)
        return false;

    std::vector<std::pair<size_t, size_t>> edificios (N);

    size_t aux1, aux2;
    for (size_t i = 0; i < N; ++i) 
    {
        std::cin >> aux1 >> aux2;
        edificios[i] = {aux1, aux2};
    }
    std::sort(edificios.begin(), edificios.end());

    //Escribir
    std::cout << resolver(edificios) << '\n';

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
