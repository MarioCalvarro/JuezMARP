// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

enum Finales {
    Siempre, 
    Posible,
    Nunca
};

//Tipo de instruccion y salto
using Instruccion = std::pair<char, size_t>;

Finales resolver(const std::vector<Instruccion> &siguientes) 
{
    //Instruccion y posicion de la misma
    std::queue<std::pair<Instruccion, size_t>> cola;
    std::vector<bool> marcados (siguientes.size(), false);
    bool end = false, ciclo = false;

    cola.push({siguientes[0], 0});
    size_t posicion_nueva = 0;
    
    while (!cola.empty()) {
        std::pair<Instruccion, size_t> actual = cola.front(); cola.pop();  
        marcados[actual.second] = true;
        if (actual.first.first == 'A') 
        {
            posicion_nueva = actual.second + 1;

            if (posicion_nueva == siguientes.size())
                end = true;
            else 
                cola.push({siguientes[posicion_nueva], posicion_nueva});
        }
        else if (actual.first.first == 'J')
        {
            posicion_nueva = actual.first.second;

            if (!marcados[posicion_nueva])
                cola.push({siguientes[posicion_nueva], posicion_nueva});
        }
        else 
        {
            //Un paso
            posicion_nueva = actual.second + 1;

            if (posicion_nueva == siguientes.size())
                end = true;
            else
                cola.push({siguientes[posicion_nueva], posicion_nueva});
            

            //Salto
            posicion_nueva = actual.first.second;

            if (!marcados[posicion_nueva])
                cola.push({siguientes[posicion_nueva], posicion_nueva});
            else 
                ciclo = true;
        }
    }

    if (end && ciclo)
        return Posible;
    else if (end) 
        return Siempre;
    else 
        return Nunca;
}

bool resuelveCaso() 
{
    //Leer
    size_t L;
    std::cin >> L;

    if (!std::cin)
        return false;

    std::vector<Instruccion> siguientes(L);

    char instruccion; size_t salto;
    for (size_t i = 0; i < L; ++i)
    {
        std::cin >> instruccion;
        if (instruccion == 'A')
            siguientes[i] = {instruccion, i + 1};
        else if (instruccion == 'J')
        {
            std::cin >> salto;
            siguientes[i] = {instruccion, salto - 1};
        }
        else if (instruccion == 'C')
        {
            std::cin >> salto;
            siguientes[i] = {instruccion, salto - 1};
        }
    }

    //Escribir
    switch (resolver(siguientes)) {
        case Siempre:
            std::cout << "SIEMPRE\n";
            break;
        case Posible:
            std::cout << "A VECES\n";
            break;
        case Nunca:
            std::cout << "NUNCA\n";
            break;
    }

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
