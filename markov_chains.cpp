#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const double TOL = 1e-10; //Tolerancia para la convergencia
const int MAX_ITER = 40; //Número máximo de iteraciones

//Función que multiplica el vector de estado por la matriz de transición
vector<double> multiply(const vector<double>& state, const vector<vector<double>>& transition) {
    vector<double> newState(state.size(), 0.0);
    for (int i = 0; i < state.size(); ++i) {
        for (int j = 0; j < transition[i].size(); ++j) {
            newState[j] += state[i] * transition[i][j];
        }
    }
    return newState;
}

//Función que calcula diferencia máxima entre dos vectores
//Definimos la diferencia máxima como la mayor diferencia absoluta entre los elementos correspondientes de dos vectores
double maxDifference(const vector<double>& a, const vector<double>& b) {
    double maxDiff = 0.0;
    for (int i = 0; i < a.size(); ++i) {
        double diff = fabs(a[i] - b[i]);
        if (diff > maxDiff) {
            maxDiff = diff;
        }
    }
    return maxDiff;
}

//Función que calcula la distribución estacionaria 
vector<double> markov_chains(const vector<vector<double>>& transition, const vector<double>& initialState, int &iter, bool &convergencia) {
    vector<double> state = initialState;
    convergencia = false;
    for (iter = 1; iter <= MAX_ITER && maxDifference(state, multiply(state, transition)) >= TOL; ++iter) {
        vector<double> newState = multiply(state, transition);
        state = newState;
    }
    if (iter < MAX_ITER) {
        convergencia = true;
    }
    return state;
}


int main() {
    //Ejemplo de uso
    vector<vector<double>> transition = {
        {0.5, 0.5, 0.0},
        {0.25, 0.5, 0.25},
        {0, 0.5, 0.5}
    };
    vector<double> initialState = {0.6, 0.25, 0.15}; //Estado inicial

    int iterations = 0;
    bool convergencia = false;
    vector<double> stationaryDistribution = markov_chains(transition, initialState, iterations, convergencia);

    cout << "Distribución estacionaria: ";
    for (double prob : stationaryDistribution) {
        cout << prob << " ";
    }
    cout << endl;
    cout << "Número de iteraciones: " << iterations << endl;
    cout << "Convergencia alcanzada: " << (convergencia ? "Sí" : "No") << ". Tolerancia " << TOL << endl;

    return 0;
}