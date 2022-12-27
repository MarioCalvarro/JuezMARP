// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

size_t resolver(const std::vector<size_t> &necesarias, const std::vector<size_t> &disponibles) 
{
    size_t sol = necesarias.size();

    size_t it_necesarias = 0, it_disponibles = 0;
    while(it_disponibles < disponibles.size() && it_necesarias < necesarias.size())
    {
        if (disponibles[it_disponibles] < necesarias[it_necesarias])
        {
            ++it_disponibles;
        }
        else if (disponibles[it_disponibles] == necesarias[it_necesarias] ||
            disponibles[it_disponibles] == necesarias[it_necesarias] + 1)
        {
            --sol;
            ++it_necesarias;
            ++it_disponibles;
        }
        else {
            ++it_necesarias;
        }
    }

    return sol;
}

bool resuelveCaso() 
{
    //Leer
    size_t N, M;
    std::cin >> N >> M;

    if (!std::cin)
        return false;

    size_t min = 101, max = 0;

    std::vector<size_t> necesarias(N);

    for (size_t i = 0; i < N; ++i)
    {
        std::cin >> necesarias[i];
        if (necesarias[i] < min)
            min = necesarias[i];
        if (necesarias[i] > max)
            max = necesarias[i];
    }

    size_t aux;
    std::vector<size_t> disponibles;
    for (size_t i = 0; i < M; ++i)
    {
        std::cin >> aux; 
        if (aux >= min && aux <= max + 1)
            disponibles.push_back(aux);
    }

    std::sort(necesarias.begin(), necesarias.end());
    std::sort(disponibles.begin(), disponibles.end());

    //Escribir
    std::cout << resolver(necesarias, disponibles) << '\n';

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
