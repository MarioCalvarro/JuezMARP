// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <utility>
#include <vector>

#include "ConjuntosDisjuntos.h"

const std::pair<int, int> DIRECCIONES_POSIBLES[8] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

template <typename T,typename U>                                                   
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return { l.first + r.first, l.second + r.second };                                    
}

using MatrizMar = std::vector<std::vector<bool>>;
void nueva_mancha(const MatrizMar &mar, ConjuntosDisjuntos &manchas, 
        std::pair<int, int> pos, size_t C)
{
    for (auto it : DIRECCIONES_POSIBLES)
    {
        auto [i, ii] = it + pos;
        if (i >= 0 && i < mar.size() &&
            ii >= 0 && ii < mar[0].size() &&
            mar[i][ii])
        {
            manchas.unir(pos.first * C + pos.second, i * C + ii);
        }
    }
}

bool resuelveCaso() 
{
    //Leer
    size_t F, C;
    std::cin >> F >> C;

    if (!std::cin)
        return false;

    char aux; std::cin.get(aux); //Salto de línea
    MatrizMar mar (F, std::vector<bool> (C, false));
    ConjuntosDisjuntos manchas(F * C);
    bool existeMancha = false;
    for (size_t i = 0; i < F; ++i)
    {
        for (size_t ii = 0; ii < C; ++ii)
        {
            std::cin.get(aux); 
            if (aux == ' ')
                mar[i][ii] = false;
            else 
            {
                existeMancha = true;
                mar[i][ii] = true;
                nueva_mancha(mar, manchas, {i, ii}, C);
            }
        }
        std::cin.get(aux); //Salto de línea
    }

    if (existeMancha) std::cout << manchas.maximo();
    else std::cout << "0";

    size_t N, pos1, pos2;
    std::cin >> N;

    if(N > 0) std::cout << ' ';

    for (size_t i = 0; i < N; ++i)
    {
        std::cin >> pos1 >> pos2;
        --pos1; --pos2;

        mar[pos1][pos2] = true;
        nueva_mancha(mar, manchas, {pos1, pos2}, C);

        std::cout << manchas.maximo();
        if (i < N - 1) std::cout << ' ';
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
