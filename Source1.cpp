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
    "chicharron", "chicharron", "chicharron", "chicharron", "chicharron", "chicharron", "chicharron", "chicharron", "chicharron", "chicharron", "chicharron", "chicharron", "chicharron", "chicharron",
    "picada", "picada", "picada", "picada", "picada", "picada", "picada", "picada", "picada", "picada", "picada", "picada", "picada", "picada",
    "empanadas", "empanadas", "empanadas", "empanadas", "empanadas", "empanadas", "empanadas", "empanadas", "empanadas", "empanadas", "empanadas", "empanadas", "empanadas", "empanadas",
    "arepa boyacense", "arepa boyacense", "arepa boyacense", "arepa boyacense", "arepa boyacense", "arepa boyacense",
    "arepa rellena", "arepa rellena", "arepa rellena", "arepa rellena", "arepa rellena", "arepa rellena",
    "arepa", "arepa", "arepa", "arepa", "arepa",
    "arroz guerrillero(1)", "arroz guerrillero(1)", "arroz guerrillero(1)", "arroz guerrillero(1)", "arroz guerrillero(1)", "arroz guerrillero(1)",
    "arroz guerrillero(2)", "arroz guerrillero(2)", "arroz guerrillero(2)", "arroz guerrillero(2)", "arroz guerrillero(2)", "arroz guerrillero(2)", "arroz guerrillero(2)", "arroz guerrillero(2)",
    "arroz guerrillero(3)", "arroz guerrillero(3)", "arroz guerrillero(3)", "arroz guerrillero(3)", "arroz guerrillero(3)", "arroz guerrillero(3)", "arroz guerrillero(3)", "arroz guerrillero(3)", "arroz guerrillero(3)", "arroz guerrillero(3)", "arroz guerrillero(3)", "arroz guerrillero(3)",
    "natilla", "natilla", "natilla", "natilla", "natilla", "natilla", "natilla", "natilla", "natilla", "natilla",
    "mantequilla", "mantequilla", "mantequilla", "mantequilla", "mantequilla", "mantequilla",
    "tenedor", "tenedor", "tenedor", "tenedor"
    }},
    {"Sushi Deluxe", {
        "chicharron", "chicharron", "chicharron", "chicharron", "chicharron", "chicharron", "chicharron", "chicharron", "chicharron", "chicharron", "chicharron", "chicharron", "chicharron", "chicharron",
        "yuca", "yuca", "yuca", "yuca", "yuca", "yuca", "yuca", "yuca", "yuca", "yuca","yuca", "yuca", "yuca", "yuca", "yuca",
        "empanadas", "empanadas", "empanadas", "empanadas", "empanadas", "empanadas", "empanadas", "empanadas", "empanadas", "empanadas", "empanadas", "empanadas", "empanadas", "empanadas",
        "arepa boyacense", "arepa boyacense", "arepa boyacense", "arepa boyacense", "arepa boyacense", "arepa boyacense",
        "arepa rellena", "arepa rellena", "arepa rellena", "arepa rellena", "arepa rellena", "arepa rellena",
        "arepa", "arepa", "arepa", "arepa", "arepa",
        "arroz con pollo(1)", "arroz con pollo(1)", "arroz con pollo(1)", "arroz con pollo(1)", "arroz con pollo(1)", "arroz con pollo(1)",
        "arroz con pollo(2)", "arroz con pollo(2)", "arroz con pollo(2)", "arroz con pollo(2)", "arroz con pollo(2)", "arroz con pollo(2)", "arroz con pollo(2)", "arroz con pollo(2)",
        "arroz con pollo(3)", "arroz con pollo(3)", "arroz con pollo(3)", "arroz con pollo(3)", "arroz con pollo(3)", "arroz con pollo(3)", "arroz con pollo(3)", "arroz con pollo(3)", "arroz con pollo(3)", "arroz con pollo(3)", "arroz con pollo(3)", "arroz con pollo(3)",
        "ensalada de fruta", "ensalada de fruta", "ensalada de fruta", "ensalada de fruta", "ensalada de fruta", "ensalada de fruta", "ensalada de fruta", "ensalada de fruta", "ensalada de fruta", "ensalada de fruta"
        "mantequilla", "mantequilla", "mantequilla", "mantequilla", "mantequilla", "mantequilla",
        "tenedor", "tenedor", "tenedor", "tenedor",
    }},
    {"mi primer aperitivo",{
        "chicharron", "chicharron", "chicharron", "chicharron", "chicharron", "chicharron", "chicharron", "chicharron", "chicharron", "chicharron", "chicharron", "chicharron", "chicharron", "chicharron",
        "picada", "picada", "picada", "picada", "picada", "picada", "picada", "picada", "picada", "picada", "picada", "picada", "picada", "picada",
        "consome", "consome", "consome", "consome", "consome", "consome", "consome", "consome", "consome", "consome", "consome", "consome", "consome", "consome", "consome", "consome",
        "arepa boyacense", "arepa boyacense", "arepa boyacense", "arepa boyacense", "arepa boyacense", "arepa boyacense",
        "arepa rellena", "arepa rellena", "arepa rellena", "arepa rellena", "arepa rellena", "arepa rellena",
        "arepa", "arepa", "arepa", "arepa", "arepa",
        "arroz guerrillero(1)", "arroz guerrillero(1)", "arroz guerrillero(1)", "arroz guerrillero(1)", "arroz guerrillero(1)", "arroz guerrillero(1)",
        "arroz guerrillero(2)", "arroz guerrillero(2)", "arroz guerrillero(2)", "arroz guerrillero(2)", "arroz guerrillero(2)", "arroz guerrillero(2)", "arroz guerrillero(2)", "arroz guerrillero(2)",
        "arroz guerrillero(3)", "arroz guerrillero(3)", "arroz guerrillero(3)", "arroz guerrillero(3)", "arroz guerrillero(3)", "arroz guerrillero(3)", "arroz guerrillero(3)", "arroz guerrillero(3)", "arroz guerrillero(3)", "arroz guerrillero(3)", "arroz guerrillero(3)", "arroz guerrillero(3)",
        "ensalada de fruta", "ensalada de fruta", "ensalada de fruta", "ensalada de fruta", "ensalada de fruta", "ensalada de fruta", "ensalada de fruta", "ensalada de fruta", "ensalada de fruta", "ensalada de fruta"
        "mantequilla", "mantequilla", "mantequilla", "mantequilla", "mantequilla", "mantequilla",
        "ensalada de fruta", "ensalada de fruta", "ensalada de fruta", "ensalada de fruta",
    }}
};

struct Jugador {
    vector<string> mano;
    vector<string> cartasJugadas;
    int puntos = 0;
    int natillas = 0;
    int ensalada_fruta = 0;
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

bool alguienJugoconsome(const vector<Jugador>& jugadores, int jugadorActual) {
    for (size_t i = 0; i < jugadores.size(); ++i) {
        if (i != static_cast<size_t>(jugadorActual)) { // No comparar con sí mismo
            for (const auto& carta : jugadores[i].cartasJugadas) {
                if (carta == "consome") {
                    return true;
                }
            }
        }
    }
    return false;
}

// Modificar la función seleccionarCarta para esta carta especial
int seleccionarCartaEspecial(const vector<string>& mano, const vector<Jugador>& jugadores, int jugadorId) {
    for (size_t i = 0; i < mano.size(); ++i) {
        if (mano[i] == "consome") {
            if (alguienJugoconsome(jugadores, jugadorId)) {
                cout << "\n⚠️ ¡Otro jugador ya jugó consome! Esta carta será descartada.\n";
                return i; // Devuelve el índice de la consome para descartarla
            }
        }
    }
    return seleccionarCarta(mano); // Comportamiento normal para otras cartas
}

pair<string, int> obtenerTipoMasRepetido(const vector<string>& cartas) {
    map<string, int> contador;

    // Excluir la carta ensalada de fruta del conteo
    for (const auto& carta : cartas) {
        if (carta != "ensalada de fruta") {
            contador[carta]++;
        }
    }

    if (contador.empty()) return make_pair("", 0);

    auto max_it = max_element(contador.begin(), contador.end(),
        [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second < b.second;
        });

    return *max_it;
}

int contararroz_guerrillero(const vector<string>&cartas) {
    int total = 0;
    for (const auto& carta : cartas) {
        if (carta == "arroz guerrillero(1)") total += 1;
        else if (carta == "arroz guerrillero(2)") total += 2;
        else if (carta == "arroz guerrillero(3)") total += 3;
    }
    return total;
}

int contararroz_con_pollo(const vector<string>& cartas) {
    int total = 0;
    for (const auto& carta : cartas) {
        if (carta == "arroz con pollo(1)") total += 1;
        else if (carta == "arroz con pollo(2)") total += 2;
        else if (carta == "arroz con pollo(3)") total += 3;
    }
    return total;
}

int puntosyuca(int cantidad) {
    if (cantidad == 1) return 1;
    if (cantidad == 2) return 6;
    return 0;
}

int puntosempanadas(int cantidad) {
    if (cantidad == 1) return 1;
    if (cantidad == 2) return 3;
    if (cantidad == 3) return 6;
    if (cantidad == 4) return 10;
    if (cantidad >= 5) return 15;
    return 0;
}

// ================== FUNCIÓN PRINCIPAL ==================

int main() {
    cout << "🎌 ¡Bienvenido a La Comelona! 🎌\n";

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
                int cartaElegida = seleccionarCartaEspecial(jugadores[j].mano, jugadores, j);

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

        // Calcular puntuación de la ronda (sin contar natillas ni helados)
        vector<int> arroz_guerrilleros(jugadores_count, 0);
        vector<int> arroz_con_pollos(jugadores_count, 0);

        for (int j = 0; j < jugadores_count; ++j) {
            map<string, int> contador;
            for (const auto& carta : jugadores[j].cartasJugadas) {
                contador[carta]++;
                // Solo contamos, no sumamos puntos aún
                if (carta == "natilla") jugadores[j].natillas++;
                if (carta == "ensalada de fruta") jugadores[j].ensalada_fruta++;
            }

            arroz_guerrilleros[j] = contararroz_guerrillero(jugadores[j].cartasJugadas);
            arroz_con_pollos[j] = contararroz_con_pollo(jugadores[j].cartasJugadas);

            // Sumar puntos (excepto natillas y helados)
            jugadores[j].puntos += (contador["chicharron"] / 2) * 5;
            jugadores[j].puntos += (contador["picada"] / 3) * 10;
            jugadores[j].puntos += puntosempanadas(contador["empanadas"]);
            jugadores[j].puntos += puntosyuca(contador["yuca"]);
            jugadores[j].puntos += contador["arepa boyacense"] * 2;
            jugadores[j].puntos += contador["arepa rellena"] * 3;
            jugadores[j].puntos += contador["arepa"];
            if (contador["consome"] > 0 && !alguienJugoconsome(jugadores, j)) {
                jugadores[j].puntos += 3;

                // Reemplazar el uso de enlaces estructurados con una alternativa compatible con C++11  
                pair<string, int> tipoMasRepetido = obtenerTipoMasRepetido(jugadores[j].cartasJugadas);
                string tipo_mas_repetido = tipoMasRepetido.first;
                int cantidad = tipoMasRepetido.second;
                // Sumar puntos por cartas de pollo
                int cartasaguapanela = contador["ensalada de fruta"];
                if (cartasaguapanela > 0 && cantidad > 0) {
                    int puntosaguapanela = cantidad * cartasaguapanela;
                    jugadores[j].puntos += puntosaguapanela;
                    cout << "   + " << cartasaguapanela << " carta(s) de aguapanela: "
                        << puntosaguapanela << " puntos (por " << cantidad << " "
                        << tipo_mas_repetido << "(s))\n";
                }

            }

            // Puntos por arroz con pollo
            int max_arroz_con_pollo = *max_element(arroz_con_pollos.begin(), arroz_con_pollos.end());
            if (max_arroz_con_pollo > 0) {
                int segundo_arroz_con_pollo = 0;
                for (int val : arroz_con_pollos) {
                    if (val < max_arroz_con_pollo && val > segundo_arroz_con_pollo) segundo_arroz_con_pollo = val;
                }

                for (int j = 0; j < jugadores_count; ++j) {
                    if (arroz_con_pollos[j] == max_arroz_con_pollo) jugadores[j].puntos += 4;
                    else if (arroz_con_pollos[j] == segundo_arroz_con_pollo && segundo_arroz_con_pollo > 0) jugadores[j].puntos -= 4;
                }
            }

            // Puntos por arroz guerrillero
            int max_arroz_guerrillero = *max_element(arroz_guerrilleros.begin(), arroz_guerrilleros.end());
            if (max_arroz_guerrillero > 0) {
                int segundo_arroz_guerrillero = 0;
                for (int val : arroz_guerrilleros) {
                    if (val < max_arroz_guerrillero && val > segundo_arroz_guerrillero) segundo_arroz_guerrillero = val;
                }

                for (int j = 0; j < jugadores_count; ++j) {
                    if (arroz_guerrilleros[j] == max_arroz_guerrillero) jugadores[j].puntos += 6;
                    else if (arroz_guerrilleros[j] == segundo_arroz_guerrillero && segundo_arroz_guerrillero > 0) jugadores[j].puntos += 3;
                }
            }

            // Mostrar puntuación parcial (sin natillas ni helados)
            cout << "\n📊 Puntuación después de la ronda " << ronda << " (sin contar natillas/helados):\n";
            for (int j = 0; j < jugadores_count; ++j) {
                cout << "Jugador " << j + 1 << ": " << jugadores[j].puntos << " puntos\n";
                cout << "   - natillas acumulados: " << jugadores[j].natillas << "\n";
                cout << "   - Helados acumulados: " << jugadores[j].ensalada_fruta << "\n";
            }
        }

        // Puntos por pudín al final del juego (con penalización)
        vector<int> natillas(jugadores_count);
        for (int j = 0; j < jugadores_count; ++j) {
            natillas[j] = jugadores[j].natillas;
        }

        int max_natilla = *max_element(natillas.begin(), natillas.end());
        int min_natilla = *min_element(natillas.begin(), natillas.end());

        for (int j = 0; j < jugadores_count; ++j) {
            if (natillas[j] == max_natilla && max_natilla > 0) jugadores[j].puntos += 6;
            if (natillas[j] == min_natilla && min_natilla > 0) jugadores[j].puntos -= 6;
        }

        // Puntos por helado de té verde al final del juego (12 puntos por cada 4 cartas)
        for (int j = 0; j < jugadores_count; ++j) {
            jugadores[j].puntos += (jugadores[j].ensalada_fruta / 4) * 12;
        }

        // Mostrar puntuación final
        cout << "\n🏁 Puntuación final:\n";
        for (int j = 0; j < jugadores_count; ++j) {
            cout << "Jugador " << j + 1 << ": " << jugadores[j].puntos << " puntos\n";
            cout << "   - natillas: " << jugadores[j].natillas << " (";
            if (jugadores[j].natillas == max_natilla && max_natilla > 0) cout << "+6";
            else if (jugadores[j].natillas == min_natilla && min_natilla > 0) cout << "-6";
            else cout << "0";
            cout << " puntos)\n";

            cout << "   - Helados de té verde: " << jugadores[j].ensalada_fruta
                << " (+" << (jugadores[j].ensalada_fruta / 4) * 12 << " puntos)\n";
        }

        return 0;
    }
}
