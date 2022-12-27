#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

size_t resolver(const std::vector<size_t> &ataques, const std::vector<size_t> &defensas) 
{
    size_t solucion = 0;
    size_t i = 0, indice = 0;

    while(i < defensas.size() && indice < defensas.size())
    {
        if (ataques[i] <= defensas[indice])
        {
            ++solucion;
            ++i;
        }

        ++indice; 
    }

    return solucion;
}

bool resuelveCaso() 
{
    //Leer
    size_t N, min = 1000001;
    std::cin >> N;

    if (!std::cin)
        return false;

    std::vector<size_t> ataques (N);
    for (size_t i = 0; i < N; ++i)
    {
        std::cin >> ataques[i];
        if (ataques[i] < min) min = ataques[i];
    }

    size_t aux;
    std::vector<size_t> defensas;
    for (size_t i = 0; i < N; ++i)
    {
        std::cin >> aux;
        if (min <= aux) defensas.push_back(aux);
    }

    std::sort(ataques.begin(), ataques.end());
    std::sort(defensas.begin(), defensas.end());

    //Escribir
    std::cout << resolver(ataques, defensas) << '\n';

    return true;
}

int main() {
    while(resuelveCaso());

    return 0;
}
