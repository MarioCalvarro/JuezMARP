// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

size_t resolver(const size_t peso_maximo, const std::vector<size_t> &usuarios) 
{
    size_t res = 0;
    size_t i = 0, j = usuarios.size() - 1;
    while(i < j)
    {
        if(usuarios[i] + usuarios[j] > peso_maximo)
        {
            --j;
        }
        else {
            ++i; --j;
        }

        ++res;
    }

    if (i == j) ++res;

    return res;
}

bool resuelveCaso() 
{
    //Leer
    size_t peso_maximo, num_usuarios;
    std::cin >> peso_maximo >> num_usuarios;

    if (!std::cin)
        return false;

    std::vector<size_t> usuarios(num_usuarios);

    for(auto &usuario : usuarios)
        std::cin >> usuario;

    std::sort(usuarios.begin(), usuarios.end());

    //Escribir
    std::cout << resolver(peso_maximo, usuarios) << '\n';

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
