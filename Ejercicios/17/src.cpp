// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

const size_t MODULO = 10000;

//Operaciones:
//-- Sumar 1 
//-- Multiplicar por 2 
//-- Dividir entre 3
size_t bfs(const size_t original, const size_t final)
{
    if (original == final) 
        return 0;

    size_t pasos = 1, aux, nivelActual = 1, nivelSiguiente = 0;
    std::queue<size_t> numeros;
    numeros.push(original);
    std::vector<bool> marcados(10001, false);
    bool encontrado = false;
    while(!numeros.empty() && !encontrado)
    {
        size_t valor = numeros.front(); numeros.pop();
        aux = (valor + 1) % MODULO;
        if (!marcados[aux])
        {
            if(aux == final)
                encontrado = true;
            else 
            {
                numeros.push(aux);
                marcados[aux] = true;
                ++nivelSiguiente;
            }
        }

        aux = (valor * 2) % MODULO;
        if (!marcados[aux])
        {
            if(aux == final)
                encontrado = true;
            else 
            {
                numeros.push(aux);
                marcados[aux] = true;
                ++nivelSiguiente;
            }
        }

        aux = (valor / 3) % MODULO;
        if (!marcados[aux])
        {
            if(aux == final)
                encontrado = true;
            else 
            {
                numeros.push(aux);
                marcados[aux] = true;
                ++nivelSiguiente;
            }
        }

        --nivelActual;
        if(!encontrado && nivelActual == 0)
        {
            nivelActual = nivelSiguiente;
            nivelSiguiente = 0;
            ++pasos;
        }
    }
    return pasos;
}

bool resuelveCaso() 
{
    //Leer
    size_t original, final;
    std::cin >> original >> final;

    if (!std::cin)
        return false;

    std::cout << bfs(original, final) << '\n';

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
