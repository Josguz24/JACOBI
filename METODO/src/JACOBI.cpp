#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

class Ecuacion {
private:
    double coeficiente_x;
    double coeficiente_y;
    double coeficiente_z;
    double resultado;

public:
    Ecuacion(double coef_x, double coef_y, double coef_z, double res)
        : coeficiente_x(coef_x), coeficiente_y(coef_y), coeficiente_z(coef_z), resultado(res) {}

    double obtenerCoeficienteX() const { return coeficiente_x; }
    double obtenerCoeficienteY() const { return coeficiente_y; }
    double obtenerCoeficienteZ() const { return coeficiente_z; }
    double obtenerResultado() const { return resultado; }

    double despejarX(double y, double z) const {
        return (resultado - coeficiente_y * y - coeficiente_z * z) / coeficiente_x;
    }

    double despejarY(double x, double z) const {
        return (resultado - coeficiente_x * x - coeficiente_z * z) / coeficiente_y;
    }

    double despejarZ(double x, double y) const {
        return (resultado - coeficiente_x * x - coeficiente_y * y) / coeficiente_z;
    }
};

bool compararCoeficientesX(const Ecuacion& ec1, const Ecuacion& ec2) {
    return ec1.obtenerCoeficienteX() > ec2.obtenerCoeficienteX();
}

bool verificarRepeticion(const vector<double>& valoresX, const vector<double>& valoresY, const vector<double>& valoresZ, double x, double y, double z) {
    const double tolerancia = 1e-6;  // Tolerancia para comparar valores en punto flotante
    int contador = 0;
    for (int i = 0; i < valoresX.size(); i++) {
        if (abs(valoresX[i] - x) < tolerancia && abs(valoresY[i] - y) < tolerancia && abs(valoresZ[i] - z) < tolerancia) {
            contador++;
        }
    }
    return contador >= 2;
}

class SistemaEcuaciones {
private:
    vector<Ecuacion> sistema;

public:
    void ingresarEcuaciones() {
        cout << "Ingrese los coeficientes de las ecuaciones:" << endl;
        for (int i = 0; i < 3; i++) {
            cout << "Ecuacion " << i + 1 << ":" << endl;
            double coef_x, coef_y, coef_z, res;
            cout << "Coeficiente de x: ";
            cin >> coef_x;
            cout << "Coeficiente de y: ";
            cin >> coef_y;
            cout << "Coeficiente de z: ";
            cin >> coef_z;
            cout << "Resultado: ";
            cin >> res;
            cout << endl;
            Ecuacion ecuacion(coef_x, coef_y, coef_z, res);
            sistema.push_back(ecuacion);
        }
    }

    void resolverSistema() {
        sort(sistema.begin(), sistema.end(), compararCoeficientesX);

        double x = 0.0;
        double y = 0.0;
        double z = 0.0;

        vector<double> valoresX;
        vector<double> valoresY;
        vector<double> valoresZ;

        do {
            x = sistema[0].despejarX(y, z);
            y = sistema[1].despejarY(x, z);
            z = sistema[2].despejarZ(x, y);

            valoresX.push_back(x);
            valoresY.push_back(y);
            valoresZ.push_back(z);
        } while (!verificarRepeticion(valoresX, valoresY, valoresZ, x, y, z));

        imprimirEcuacionesReorganizadas();
        imprimirDespejesFinales(x, y, z);
        imprimirSolucion(x, y, z);
    }

private:
    void imprimirEcuacionesReorganizadas() const {
        cout << "Ecuaciones reorganizadas:" << endl;
        cout << "Ecuacion 1: x = " << sistema[0].obtenerCoeficienteX() << "y + " << sistema[0].obtenerCoeficienteZ() << "z + " << sistema[0].obtenerResultado() << endl;
        cout << "Ecuacion 2: y = " << sistema[1].obtenerCoeficienteY() << "x + " << sistema[1].obtenerCoeficienteZ() << "z + " << sistema[1].obtenerResultado() << endl;
        cout << "Ecuacion 3: z = " << sistema[2].obtenerCoeficienteZ() << "x + " << sistema[2].obtenerCoeficienteY() << "y + " << sistema[2].obtenerResultado() << endl;
        cout << endl;
    }

    void imprimirDespejesFinales(double x, double y, double z) const {
        cout << "Despejes finales:" << endl;
        cout << "x = (" << sistema[0].obtenerResultado() << " - " << sistema[0].obtenerCoeficienteY() << "y - " << sistema[0].obtenerCoeficienteZ() << "z) / " << sistema[0].obtenerCoeficienteX() << endl;
        cout << "y = (" << sistema[1].obtenerResultado() << " - " << sistema[1].obtenerCoeficienteX() << "x - " << sistema[1].obtenerCoeficienteZ() << "z) / " << sistema[1].obtenerCoeficienteY() << endl;
        cout << "z = (" << sistema[2].obtenerResultado() << " - " << sistema[2].obtenerCoeficienteX() << "x - " << sistema[2].obtenerCoeficienteY() << "y) / " << sistema[2].obtenerCoeficienteZ() << endl;
        cout << endl;
    }

    void imprimirSolucion(double x, double y, double z) const {
        cout << "Solucion:" << endl;
        cout << "x = " << x << endl;
        cout << "y = " << y << endl;
        cout << "z = " << z << endl;
    }
};

int main() {
    SistemaEcuaciones sistema;
    sistema.ingresarEcuaciones();
    sistema.resolverSistema();

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return 0;
}
