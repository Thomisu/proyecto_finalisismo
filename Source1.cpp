#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

// Lista de nombres de cartas
vector<string> mazoBase = {
    "uno", "dos", "tres", "cuatro", "cinco",
    "seis", "siete", "ocho", "nueve", "diez",
    "uno", "dos", "tres", "cuatro", "cinco"
};

// Función para barajar el mazo
void barajar(vector<string>& mazo) {
    random_device rd;
    mt19937 g(rd());
    shuffle(mazo.begin(), mazo.end(), g);
}

// Función auxiliar para aplicar el efecto de una carta y retornar los puntos ganados
int aplicarEfectoCarta(const string& carta, int puntosActuales, int& modificadorMultiplicador) {
    if (carta == "uno") {
        return 1;
    }
    else if (carta == "dos") {
        modificadorMultiplicador *= 2;
        return 0;
    }
    else if (carta == "tres") {
        return 3;
    }
    else if (carta == "cuatro") {
        return -1;
    }
    else if (carta == "cinco") {
        return 5;
    }
    else if (carta == "seis") {
        return 2;
    }
    else if (carta == "siete") {
        modificadorMultiplicador += 1;
        return 0;
    }
    else if (carta == "ocho") {
        return 0;
    }
    else if (carta == "nueve") {
        return -2;
    }
    else if (carta == "diez") {
        return 10;
    }
    else {
        return 0;
    }
}

// Función para repartir 3 cartas por jugador
vector<vector<string>> repartirCartas(vector<string>& mazo, int jugadores) {
    vector<vector<string>> manos(jugadores);
    for (int i = 0; i < jugadores * 3 && i < mazo.size(); ++i) {
        manos[i % jugadores].push_back(mazo[i]);
    }
    return manos;
}

int main() {
    int jugadores, rondas;

    cout << "Ingrese el número de jugadores: ";
    cin >> jugadores;

    cout << "Ingrese el número de rondas a jugar: ";
    cin >> rondas;

    vector<int> puntos(jugadores, 0);  // Sistema de puntuación

    for (int ronda = 1; ronda <= rondas; ++ronda) {
        cout << "\n?? Ronda " << ronda << "\n";

        vector<string> mazo = mazoBase;
        barajar(mazo);

        vector<vector<string>> manos = repartirCartas(mazo, jugadores);
        vector<vector<string>> elegidas(jugadores);

        while (!manos[0].empty()) {
            vector<vector<string>> nuevasManos(jugadores);

            for (int i = 0; i < jugadores; ++i) {
                cout << "\nJugador " << i + 1 << " tiene:\n";
                for (size_t j = 0; j < manos[i].size(); ++j) {
                    cout << j + 1 << ". " << manos[i][j] << endl;
                }

                int eleccion = 0;
                if (manos[i].size() == 1) {
                    eleccion = 1;
                    cout << "Sólo queda una carta. Se elige automáticamente.\n";
                }
                else {
                    cout << "Elige una carta (1-" << manos[i].size() << "): ";
                    cin >> eleccion;
                }

                elegidas[i].push_back(manos[i][eleccion - 1]);

                // Pasar el resto al siguiente jugador
                for (size_t j = 0; j < manos[i].size(); ++j) {
                    if (j != (size_t)(eleccion - 1)) {
                        int siguiente = (i + 1) % jugadores;
                        nuevasManos[siguiente].push_back(manos[i][j]);
                    }
                }
            }

            manos = nuevasManos;
        }

        // Mostrar cartas elegidas y calcular puntos
        cout << "\n?? Cartas finales elegidas:\n";
        for (int i = 0; i < jugadores; ++i) {
            cout << "Jugador " << i + 1 << ": ";
            int modificador = 1;
            int puntosRonda = 0;

            for (const string& carta : elegidas[i]) {
                cout << carta << " ";
                puntosRonda += aplicarEfectoCarta(carta, puntos[i], modificador);
            }

            puntosRonda *= modificador;
            puntos[i] += puntosRonda;

            cout << "(Puntos ganados: " << puntosRonda << ")\n";
        }
    }

    // Puntajes finales
    cout << "\n?? Puntajes finales:\n";
    for (int i = 0; i < jugadores; ++i) {
        cout << "Jugador " << i + 1 << ": " << puntos[i] << " puntos\n";
    }

    return 0;
}
