#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>
#include <map>
#include <limits>

using namespace std;

// Estructura para cada jugador
struct Jugador {
    vector<string> mano;
    vector<string> cartasJugadas;
    int puntos = 0;
    int pudines = 0;
};

// Mazo de cartas
vector<string> mazoBase = {
    "tempura", "tempura", "tempura", "tempura", "tempura", "tempura", "tempura", "tempura", "tempura", "tempura", "tempura", "tempura", "tempura", "tempura",
    "sashimi", "sashimi", "sashimi", "sashimi", "sashimi", "sashimi", "sashimi", "sashimi", "sashimi", "sashimi", "sashimi", "sashimi", "sashimi", "sashimi",
    "gyoza", "gyoza", "gyoza", "gyoza", "gyoza", "gyoza", "gyoza", "gyoza", "gyoza", "gyoza", "gyoza", "gyoza", "gyoza", "gyoza",
    "nigiri de salmon", "nigiri de salmon", "nigiri de salmon", "nigiri de salmon", "nigiri de salmon", "nigiri de salmon",
    "nigiri de calamar", "nigiri de calamar", "nigiri de calamar", "nigiri de calamar", "nigiri de calamar", "nigiri de calamar",
    "nigiri de tortilla", "nigiri de tortilla", "nigiri de tortilla", "nigiri de tortilla", "nigiri de tortilla",
    "maki(1)", "maki(1)", "maki(1)", "maki(1)", "maki(1)", "maki(1)",
    "maki(2)", "maki(2)", "maki(2)", "maki(2)", "maki(2)", "maki(2)", "maki(2)", "maki(2)",
    "maki(3)", "maki(3)", "maki(3)", "maki(3)", "maki(3)", "maki(3)", "maki(3)", "maki(3)", "maki(3)", "maki(3)", "maki(3)", "maki(3)",
    "pudin", "pudin", "pudin", "pudin", "pudin", "pudin", "pudin", "pudin", "pudin", "pudin",
    "wasabi", "wasabi", "wasabi", "wasabi", "wasabi", "wasabi",
    "palillos", "palillos", "palillos", "palillos"
};

// Función para barajar el mazo
void barajar(vector<string>& mazo) {
    random_device rd;
    mt19937 g(rd());
    shuffle(mazo.begin(), mazo.end(), g);
}

// Función para obtener el número de cartas por jugador
int obtenerCartasPorJugador(int num_jugadores) {
    switch (num_jugadores) {
    case 2: return 10;
    case 3: return 9;
    case 4: return 8;
    case 5: return 7;
    default: return 0;
    }
}

// Función para mostrar la mano de un jugador
void mostrarMano(const vector<string>& mano, int jugadorId) {
    cout << "\n📋 Mano del Jugador " << jugadorId + 1 << ":" << endl;
    for (int i = 0; i < mano.size(); ++i) {
        cout << i + 1 << ": " << mano[i] << endl;
    }
}

// Función para seleccionar una carta (con validación)
int seleccionarCarta(const vector<string>& mano) {
    int eleccion;
    cout << "👉 Elige una carta (1-" << mano.size() << "): ";
    while (!(cin >> eleccion) || eleccion < 1 || eleccion > mano.size()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "❌ Inválido. Elige de nuevo (1-" << mano.size() << "): ";
    }
    return eleccion - 1; // Convertir a índice base 0
}

// Función para calcular puntos de gyoza
int puntosGyoza(int cantidad) {
    if (cantidad == 1) return 1;
    if (cantidad == 2) return 3;
    if (cantidad == 3) return 6;
    if (cantidad == 4) return 10;
    if (cantidad >= 5) return 15;
    return 0;
}

// Función principal
int main() {
    int jugadores_count, rondas;

    // Configuración inicial
    cout << "🎌 ¡Bienvenido a Sushi Go! 🎌" << endl;
    cout << "Ingrese el número de jugadores (2-5): ";
    cin >> jugadores_count;

    int cartas_por_jugador = obtenerCartasPorJugador(jugadores_count);
    if (cartas_por_jugador == 0) {
        cout << "❌ Número de jugadores inválido." << endl;
        return 1;
    }

    cout << "Ingrese el número de rondas a jugar: ";
    cin >> rondas;

    vector<Jugador> jugadores(jugadores_count);

    // Bucle principal de rondas
    for (int ronda = 1; ronda <= rondas; ++ronda) {
        cout << "\n🌀 Ronda " << ronda << endl;

        // Barajar y repartir cartas
        vector<string> mazo = mazoBase;
        barajar(mazo);
        for (auto& jugador : jugadores) {
            jugador.mano.clear();
            jugador.cartasJugadas.clear();
        }

        for (int i = 0; i < jugadores_count * cartas_por_jugador; ++i) {
            jugadores[i % jugadores_count].mano.push_back(mazo[i]);
        }

        // Bucle de turnos
        for (int turno = 0; turno < cartas_por_jugador; ++turno) {
            for (int j = 0; j < jugadores_count; ++j) {
                cout << "\n🎮 Turno del Jugador " << j + 1 << endl;
                mostrarMano(jugadores[j].mano, j);
                int cartaElegida = seleccionarCarta(jugadores[j].mano);

                // Mover carta de "mano" a "cartasJugadas"
                jugadores[j].cartasJugadas.push_back(jugadores[j].mano[cartaElegida]);
                jugadores[j].mano.erase(jugadores[j].mano.begin() + cartaElegida);
            }

            // Rotar manos (excepto en el último turno)
            if (turno < cartas_por_jugador - 1) {
                vector<string> ultimaMano = jugadores.back().mano;
                for (int j = jugadores_count - 1; j > 0; --j) {
                    jugadores[j].mano = jugadores[j - 1].mano;
                }
                jugadores[0].mano = ultimaMano;
            }
        }

        // Calcular puntuación de la ronda
        vector<int> makis(jugadores_count, 0);
        for (int j = 0; j < jugadores_count; ++j) {
            map<string, int> contador;
            for (const auto& carta : jugadores[j].cartasJugadas) {
                contador[carta]++;
                if (carta.find("maki") != string::npos) {
                    makis[j] += (carta == "maki(1)") ? 1 : (carta == "maki(2)") ? 2 : 3;
                }
                if (carta == "pudin") jugadores[j].pudines++;
            }

            // Sumar puntos
            jugadores[j].puntos += (contador["tempura"] / 2) * 5;
            jugadores[j].puntos += (contador["sashimi"] / 3) * 10;
            jugadores[j].puntos += puntosGyoza(contador["gyoza"]);
            jugadores[j].puntos += contador["nigiri de salmon"] * 2;
            jugadores[j].puntos += contador["nigiri de calamar"] * 3;
            jugadores[j].puntos += contador["nigiri de tortilla"];
        }

        // Puntos por maki
        int max_maki = *max_element(makis.begin(), makis.end());
        int segundo_maki = 0;
        for (int val : makis) {
            if (val < max_maki && val > segundo_maki) segundo_maki = val;
        }
        for (int j = 0; j < jugadores_count; ++j) {
            if (makis[j] == max_maki) jugadores[j].puntos += 6;
            else if (makis[j] == segundo_maki) jugadores[j].puntos += 3;
        }

        // Mostrar puntuación parcial
        cout << "\n📊 Puntuación después de la ronda " << ronda << ":" << endl;
        for (int j = 0; j < jugadores_count; ++j) {
            cout << "Jugador " << j + 1 << ": " << jugadores[j].puntos << " puntos" << endl;
        }
    }

    // Puntos por pudín al final del juego
    vector<int> pudines(jugadores_count);
    for (int j = 0; j < jugadores_count; ++j) pudines[j] = jugadores[j].pudines;

    int max_pudin = *max_element(pudines.begin(), pudines.end());
    int min_pudin = *min_element(pudines.begin(), pudines.end());

    for (int j = 0; j < jugadores_count; ++j) {
        if (pudines[j] == max_pudin) jugadores[j].puntos += 6;
        if (pudines[j] == min_pudin) jugadores[j].puntos -= 6;
    }

    // Mostrar puntuación final
    cout << "\n🏁 Puntuación final:" << endl;
    for (int j = 0; j < jugadores_count; ++j) {
        cout << "Jugador " << j + 1 << ": " << jugadores[j].puntos << " puntos (Pudines: " << jugadores[j].pudines << ")" << endl;
    }

    return 0;
}
