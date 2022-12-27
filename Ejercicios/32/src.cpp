// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>

const size_t MINUTOS_LIBRES = 10;

size_t resolver(const std::vector<std::pair<size_t, size_t>> &peliculas) 
{
    size_t sol = 1;
    size_t inicio = peliculas[0].first, final = peliculas[0].second;

    for (size_t i = 1; i < peliculas.size(); ++i) 
    {
        if (peliculas[i].first < final && peliculas[i].second < final)
            final = peliculas[i].second;
        else if (peliculas[i].first >= final + 10)
        {
            ++sol;
            final = peliculas[i].second;
        }
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

    //Inicio (en minutos desde las 00:00) y duración en minutos
    std::vector<std::pair<size_t, size_t>> peliculas (N);

    size_t inicio, hora_inicio;
    std::string aux1; size_t duracion;
    std::string horas_string, minutos_string;
    for (size_t i = 0; i < N; ++i)
    {
        std::cin >> aux1 >> duracion;

        minutos_string = aux1.substr(3, 2);
        std::stringstream sstream2(minutos_string);
        sstream2 >> inicio;

        horas_string = aux1.substr(0, 2); 
        std::stringstream sstream1(horas_string);
        sstream1 >> hora_inicio;
        inicio += hora_inicio * 60;

        peliculas[i] = {inicio, duracion + inicio};
    }

    std::sort(peliculas.begin(), peliculas.end());

    //Escribir
    std::cout << resolver(peliculas) << '\n';

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
