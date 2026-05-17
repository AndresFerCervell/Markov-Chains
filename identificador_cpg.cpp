#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

//  TAMAÑO VENTANA
const int W = 10;

// MATRIZ LOG-ODDS
const double matriz_beta[4][4] = {
    {-0.740,  0.419,  0.580, -0.803},
    {-0.913,  0.302,  1.812, -0.685},
    {-0.624,  0.461,  0.331, -0.730},
    {-1.169,  0.573,  0.393, -0.679}
};

int indiceNucleotido(char nucleotido) {
    switch(nucleotido) {
        case 'A': return 0;
        case 'C': return 1;
        case 'G': return 2;
        case 'T': return 3;
        default: return -1; //LETRA ERRÓNEA
    }
}

// CÁLCULO VENTANA: S = Tr(C^T * B)
double calcularPuntuacionVentana(const string& ventana) {
    double puntuacion_total = 0.0;

    // Evaluamos los (W - 1) saltos entre los nucleótidos de la ventana
    for (int i = 0; i < W - 1; ++i) {
        int fila = indiceNucleotido(ventana[i]);
        int columna = indiceNucleotido(ventana[i+1]);

        if (fila != -1 && columna != -1) {
            puntuacion_total += matriz_beta[fila][columna];
        }
    }

    return puntuacion_total;
}

int main() {
    // SECUENCIA DE PRUEBA
    string secuencia = "ATATTTACATAGTAATATAACGCGCCGGCGCGCGCGCCGTAATTATATATCATATAAATA";

    int longitud_secuencia = secuencia.length();
    int numero_ventanas = longitud_secuencia - W + 1;

    //información que luego se ignora al graficar (#)
    cout << "# Ventana\tPuntuacion" << endl;

    // SALIDA
    cout << fixed << setprecision(3);

    //BUCLE VENTANAS
    for (int i = 0; i < numero_ventanas; ++i) {
        string subcadena = secuencia.substr(i, W);
        double puntuacion = calcularPuntuacionVentana(subcadena);

        cout << i + 1 << "\t" << puntuacion << endl;
    }

    return 0;
}