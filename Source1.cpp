#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>
#include <map>
#include <limits>

using namespace std;

// ================== CONSTANTES Y ESTRUCTURAS ==================

const map<string, vector<string>> MAZOS = {
    {"Clásico", {
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
    }},
    {"Sushi Deluxe", {
        "tempura", "tempura", "tempura", "tempura", "tempura", "tempura", "tempura", "tempura", "tempura", "tempura", "tempura", "tempura", "tempura", "tempura",
        "tofu", "tofu", "tofu", "tofu", "tofu",
        "gyoza", "gyoza", "gyoza", "gyoza", "gyoza", "gyoza", "gyoza", "gyoza", "gyoza", "gyoza", "gyoza", "gyoza", "gyoza", "gyoza",
        "nigiri de salmon", "nigiri de salmon", "nigiri de salmon", "nigiri de salmon", "nigiri de salmon", "nigiri de salmon",
        "nigiri de calamar", "nigiri de calamar", "nigiri de calamar", "nigiri de calamar", "nigiri de calamar", "nigiri de calamar",
        "nigiri de tortilla", "nigiri de tortilla", "nigiri de tortilla", "nigiri de tortilla", "nigiri de tortilla",
        "temaki(1)", "temaki(1)", "temaki(1)", "temaki(1)", "temaki(1)", "temaki(1)",
        "temaki(2)", "temaki(2)", "temaki(2)", "temaki(2)", "temaki(2)", "temaki(2)", "temaki(2)", "temaki(2)",
        "temaki(3)", "temaki(3)", "temaki(3)", "temaki(3)", "temaki(3)", "temaki(3)", "temaki(3)", "temaki(3)", "temaki(3)", "temaki(3)", "temaki(3)", "temaki(3)",
        "helado de te verde", "helado de te verde", "helado de te verde", "helado de te verde", "helado de te verde", "helado de te verde", "helado de te verde", "helado de te verde", "helado de te verde", "helado de te verde"
        "wasabi", "wasabi", "wasabi", "wasabi", "wasabi", "wasabi",
        "palillos", "palillos", "palillos", "palillos",
        "helado de te verde", "helado de te verde", "helado de te verde", "helado de te verde"
    }}
};

struct Jugador {
    vector<string> mano;
    vector<string> cartasJugadas;
    int puntos = 0;
    int pudines = 0;
    int helados_te_verde = 0;
};

// ================== FUNCIONES AUXILIARES ==================

void mostrarMazos() {
    cout << "\n🎴 Mazos disponibles:\n";
    int i = 1;
    for (const auto& par : MAZOS) {
        cout << i++ << ". " << par.first << " (" << par.second.size() << " cartas)\n";
    }
}

const vector<string>& elegirMazo() {
    mostrarMazos();
    int eleccion;

    while (true) {
        cout << "👉 Elige un mazo (1-" << MAZOS.size() << "): ";
        cin >> eleccion;

        if (cin.fail() || eleccion < 1 || eleccion > static_cast<int>(MAZOS.size())) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "❌ Opción inválida. Intenta nuevamente.\n";
        }
        else {
            break;
        }
    }

    auto it = MAZOS.begin();
    advance(it, eleccion - 1);
    cout << "✔️ Mazo seleccionado: " << it->first << "\n\n";
    return it->second;
}

void barajar(vector<string>& mazo) {
    random_device rd;
    mt19937 g(rd());
    shuffle(mazo.begin(), mazo.end(), g);
}

void mostrarMano(const vector<string>& mano, int jugadorId) {
    cout << "\n📋 Mano del Jugador " << jugadorId + 1 << ":\n";
    for (size_t i = 0; i < mano.size(); ++i) {
        cout << i + 1 << ": " << mano[i] << "\n";
    }
}

int seleccionarCarta(const vector<string>& mano) {
    int eleccion;

    while (true) {
        cout << "👉 Elige una carta (1-" << mano.size() << "): ";
        cin >> eleccion;

        if (cin.fail() || eleccion < 1 || eleccion > static_cast<int>(mano.size())) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "❌ Selección inválida. Intenta nuevamente.\n";
        }
        else {
            break;
        }
    }

    return eleccion - 1;
}

int obtenerCartasPorJugador(int num_jugadores) {
    switch (num_jugadores) {
    case 2: return 10;
    case 3: return 9;
    case 4: return 8;
    case 5: return 7;
    default: return 0;
    }
}

int contarMaki(const vector<string>& cartas) {
    int total = 0;
    for (const auto& carta : cartas) {
        if (carta == "maki(1)") total += 1;
        else if (carta == "maki(2)") total += 2;
        else if (carta == "maki(3)") total += 3;
    }
    return total;
}

int contarTemaki(const vector<string>& cartas) {
    int total = 0;
    for (const auto& carta : cartas) {
        if (carta == "temaki(1)") total += 1;
        else if (carta == "temaki(2)") total += 2;
        else if (carta == "temaki(3)") total += 3;
    }
    return total;
}

int puntostofu(int cantidad) {
    if (cantidad == 1) return 1;
    if (cantidad == 2) return 6;
    return 0;
}

int puntosGyoza(int cantidad) {
    if (cantidad == 1) return 1;
    if (cantidad == 2) return 3;
    if (cantidad == 3) return 6;
    if (cantidad == 4) return 10;
    if (cantidad >= 5) return 15;
    return 0;
}

// ================== FUNCIÓN PRINCIPAL ==================

int main() {
    cout << "🎌 ¡Bienvenido a Sushi Go! 🎌\n";

    // Configuración inicial
    const vector<string>& mazoBase = elegirMazo();

    int jugadores_count;
    do {
        cout << "\nIngrese el número de jugadores (2-5): ";
        cin >> jugadores_count;

        if (cin.fail() || jugadores_count < 2 || jugadores_count > 5) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "❌ Número de jugadores inválido.\n";
        }
    } while (jugadores_count < 2 || jugadores_count > 5);

    int cartas_por_jugador = obtenerCartasPorJugador(jugadores_count);

    int rondas;
    do {
        cout << "Ingrese el número de rondas a jugar (1-5): ";
        cin >> rondas;

        if (cin.fail() || rondas < 1 || rondas > 5) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "❌ Número de rondas inválido.\n";
        }
    } while (rondas < 1 || rondas > 5);

    vector<Jugador> jugadores(jugadores_count);

    // Bucle principal del juego
    for (int ronda = 1; ronda <= rondas; ++ronda) {
        cout << "\n🌀 Ronda " << ronda << "\n";

        // Preparar mazo y repartir cartas
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
                cout << "\n🎮 Turno del Jugador " << j + 1 << "\n";
                mostrarMano(jugadores[j].mano, j);
                int cartaElegida = seleccionarCarta(jugadores[j].mano);

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

        // Calcular puntuación de la ronda (sin contar pudines ni helados)
        vector<int> makis(jugadores_count, 0);
        vector<int> temakis(jugadores_count, 0);

        for (int j = 0; j < jugadores_count; ++j) {
            map<string, int> contador;
            for (const auto& carta : jugadores[j].cartasJugadas) {
                contador[carta]++;
                // Solo contamos, no sumamos puntos aún
                if (carta == "pudin") jugadores[j].pudines++;
                if (carta == "helado de te verde") jugadores[j].helados_te_verde++;
            }

            makis[j] = contarMaki(jugadores[j].cartasJugadas);
            temakis[j] = contarTemaki(jugadores[j].cartasJugadas);

            // Sumar puntos (excepto pudines y helados)
            jugadores[j].puntos += (contador["tempura"] / 2) * 5;
            jugadores[j].puntos += (contador["sashimi"] / 3) * 10;
            jugadores[j].puntos += puntosGyoza(contador["gyoza"]);
            jugadores[j].puntos += puntostofu(contador["tofu"]);
            jugadores[j].puntos += contador["nigiri de salmon"] * 2;
            jugadores[j].puntos += contador["nigiri de calamar"] * 3;
            jugadores[j].puntos += contador["nigiri de tortilla"];
        }

        // Puntos por temaki
        int max_temaki = *max_element(temakis.begin(), temakis.end());
        if (max_temaki > 0) {
            int segundo_temaki = 0;
            for (int val : temakis) {
                if (val < max_temaki && val > segundo_temaki) segundo_temaki = val;
            }

            for (int j = 0; j < jugadores_count; ++j) {
                if (temakis[j] == max_temaki) jugadores[j].puntos += 4;
                else if (temakis[j] == segundo_temaki && segundo_temaki > 0) jugadores[j].puntos -= 4;
            }
        }

        // Puntos por maki
        int max_maki = *max_element(makis.begin(), makis.end());
        if (max_maki > 0) {
            int segundo_maki = 0;
            for (int val : makis) {
                if (val < max_maki && val > segundo_maki) segundo_maki = val;
            }

            for (int j = 0; j < jugadores_count; ++j) {
                if (makis[j] == max_maki) jugadores[j].puntos += 6;
                else if (makis[j] == segundo_maki && segundo_maki > 0) jugadores[j].puntos += 3;
            }
        }

        // Mostrar puntuación parcial (sin pudines ni helados)
        cout << "\n📊 Puntuación después de la ronda " << ronda << " (sin contar pudines/helados):\n";
        for (int j = 0; j < jugadores_count; ++j) {
            cout << "Jugador " << j + 1 << ": " << jugadores[j].puntos << " puntos\n";
            cout << "   - Pudines acumulados: " << jugadores[j].pudines << "\n";
            cout << "   - Helados acumulados: " << jugadores[j].helados_te_verde << "\n";
        }
    }

    // Puntos por pudín al final del juego (con penalización)
    vector<int> pudines(jugadores_count);
    for (int j = 0; j < jugadores_count; ++j) {
        pudines[j] = jugadores[j].pudines;
    }

    int max_pudin = *max_element(pudines.begin(), pudines.end());
    int min_pudin = *min_element(pudines.begin(), pudines.end());

    for (int j = 0; j < jugadores_count; ++j) {
        if (pudines[j] == max_pudin && max_pudin > 0) jugadores[j].puntos += 6;
        if (pudines[j] == min_pudin && min_pudin > 0) jugadores[j].puntos -= 6;
    }

    // Puntos por helado de té verde al final del juego (12 puntos por cada 4 cartas)
    for (int j = 0; j < jugadores_count; ++j) {
        jugadores[j].puntos += (jugadores[j].helados_te_verde / 4) * 12;
    }

    // Mostrar puntuación final
    cout << "\n🏁 Puntuación final:\n";
    for (int j = 0; j < jugadores_count; ++j) {
        cout << "Jugador " << j + 1 << ": " << jugadores[j].puntos << " puntos\n";
        cout << "   - Pudines: " << jugadores[j].pudines << " (";
        if (jugadores[j].pudines == max_pudin && max_pudin > 0) cout << "+6";
        else if (jugadores[j].pudines == min_pudin && min_pudin > 0) cout << "-6";
        else cout << "0";
        cout << " puntos)\n";

        cout << "   - Helados de té verde: " << jugadores[j].helados_te_verde
            << " (+" << (jugadores[j].helados_te_verde / 4) * 12 << " puntos)\n";
    }

    return 0;
}
