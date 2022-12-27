// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <vector>

size_t resolver(const std::vector<size_t> &posiciones, const size_t L) 
{
    size_t solucion = 1;
    size_t primero = posiciones[0], segundo;

    for (size_t i = 1; i < posiciones.size(); ++i)
    {
        segundo = posiciones[i];
        if ((segundo - primero) > L)
        {
            ++solucion;
            primero = segundo;
        }
    }

    return solucion;
}

bool resuelveCaso() 
{
    //Leer
    size_t N, L;
    std::cin >> N >> L;

    if (!std::cin)
        return false;

    std::vector<size_t> posiciones (N);

    for (size_t i = 0; i < N; ++i)
        std::cin >> posiciones[i];

    //Escribir
    std::cout << resolver(posiciones, L) << '\n';

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
