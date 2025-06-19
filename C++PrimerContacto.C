#include <iostream>
#include <string>

using namespace std;

enum MENU{
    VER=1,
    CAMBIAR,
    SALIR
};

class Vehiculo{
private:
    string duenio;
    string patente;
    string modelo;
    string estado;
public:
    Vehiculo(string due, string pat, string mod){
        duenio = due;
        patente = pat;
        modelo = mod;
        estado = "En reparacion";
    }
    void ActualizarEstado(string NuevoEstado){
        if(NuevoEstado == "En reparacion" || NuevoEstado == "Listo" || NuevoEstado == "Entregado"){
            estado = NuevoEstado;
            cout << "Estado actualizado a: " << estado << endl;
        } 
        else{
            cout << "\033[1;31mEstado no valido, lo correcto sería que uses: En reparacion, Listo o Entregado\033[0m" << endl;
        }
    }
    void MostrarDatos(){
        cout << "\nDuenio: " << duenio << endl;
        cout << "Patente: " << patente << endl;
        cout << "Modelo: " << modelo << endl;
        cout << "Estado: " << estado << endl;
    }
};

int main (){
    Vehiculo v1("Carlitos", "AH232XT", "HILUX");
    int opcion;
    string NuevoEstado;
    do{
        cout << "\n\033[1;32m- - - Menu - - -\033[0m\n";
        cout << VER << ". Ver información del vehículo\n";
        cout << CAMBIAR <<". Cambiar estado\n";
        cout << SALIR << ". Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();
        switch(opcion){
            case VER:
                v1.MostrarDatos();
                break;
            case CAMBIAR:
                cout << "\033[1;36mIngrese nuevo estado (En reparación / Listo / Entregado): \033[0m";
                getline(cin, NuevoEstado);
                v1.ActualizarEstado(NuevoEstado);
                break;
            case SALIR:
                cout << "Saliendo del sistema...\n";
                break;
            default:
                cout << "\033[1;31mOpción no válida.\033[0m\n";
        }
    } while(opcion != 3);
    return 0;
}
