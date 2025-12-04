#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

enum MENU{
    CONSULTAR = 1,
    DEPOSITAR,
    RETIRAR,
    HISTORIAL,
    SALIR
};

class CuentaBancaria{
private:
    string NombreUsuario;
    string password;
    double saldo;

public:
    CuentaBancaria() : saldo(0.0) {}

    CuentaBancaria(string user, string pass, double SaldoInicial = 0.0){
        NombreUsuario = user;
        password = pass;
        saldo = SaldoInicial;
    }

    bool VerificarPassword(string input){
        return input == password;
    }

    void Depositar(double monto){
        saldo += monto;
        GuardarTransaccion("Deposito", monto);
    }

    bool Retirar(double monto){
        if (monto > saldo) return false;
        saldo -= monto;
        GuardarTransaccion("Retiro", monto);
        return true;
    }

    double GetSaldo() const{
        return saldo;
    }

    string GetUsuario() const{
        return NombreUsuario;
    }

    void GuardarEnArchivo(){
        ifstream ArchivoIn("usuarios.dat");
        ofstream ArchivoTemp("temp.dat");
        string user, pass;
        double s;
        bool actualizado = false;
        while (getline(ArchivoIn, user)){
            getline(ArchivoIn, pass);
            ArchivoIn >> s;
            ArchivoIn.ignore();
            if(user == NombreUsuario){
                ArchivoTemp << NombreUsuario << '\n' << password << '\n' << saldo << '\n';
                actualizado = true;
            } 
            else ArchivoTemp << user << '\n' << pass << '\n' << s << '\n';
        }
        if(!actualizado)ArchivoTemp << NombreUsuario << '\n' << password << '\n' << saldo << '\n';
        ArchivoIn.close();
        ArchivoTemp.close();
        remove("usuarios.dat");
        rename("temp.dat", "usuarios.dat");
    }

    bool CargarDeArchivo(string usuario){
        ifstream archivo("usuarios.dat", ios::binary);
        string user, pass;
        double s;
        while(getline(archivo, user)){
            getline(archivo, pass);
            archivo >> s;
            archivo.ignore();
            if(user == usuario){
                NombreUsuario = user;
                password = pass;
                saldo = s;
                archivo.close();
                return true;
            }
        }
        archivo.close();
        return false;
    }

    void GuardarTransaccion(string tipo, double monto){
        string archivoHist = "historial_" + NombreUsuario + ".txt";
        ofstream archivo(archivoHist, ios::app);
        time_t now = time(0);
        char* dt = ctime(&now);
        archivo << left << setw(20) << tipo << " | "
                << fixed << setprecision(2) << monto << " | " << dt;
        archivo.close();
    }

    void MostrarHistorial(){
        string archivoHist = "historial_" + NombreUsuario + ".txt";
        ifstream archivo(archivoHist);
        if(!archivo){
            cout << "\nNo hay historial disponible.\n";
            return;
        }
        cout << "\n--- Historial de Transacciones ---\n";
        string linea;
        while (getline(archivo, linea)) cout << linea << "/n";
        archivo.close();
    }
};

void MenuUsuario(CuentaBancaria &cuenta){
    int opcion;
    do{
        cout << "\n--- Menu de Usuario ---\n";
        cout << CONSULTAR << ". Consultar saldo\n";
        cout << DEPOSITAR << ". Depositar\n";
        cout << RETIRAR << ". Retirar\n";
        cout << HISTORIAL << ". Ver historial\n";
        cout << SALIR << ". Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        if (opcion == CONSULTAR) cout << "Saldo actual: $" << fixed << setprecision(2) << cuenta.GetSaldo() << endl;
        else if(opcion == DEPOSITAR){
            double monto;
            cout << "Monto a depositar: $";
            cin >> monto;
            cuenta.Depositar(monto);
            cout << "Deposito exitoso.\n";
        } 
        else if(opcion == RETIRAR){
            double monto;
            cout << "Monto a retirar: $";
            cin >> monto;
            if(cuenta.Retirar(monto)) cout << "Retiro exitoso.\n";
            else cout << "Fondos insuficientes.\n";
        }
        else if(opcion == HISTORIAL) cuenta.MostrarHistorial();
    } while(opcion != SALIR);
    cuenta.GuardarEnArchivo();
}

int main(){
    int opcion;
    cout << "\n=== SISTEMA BANCARIO ===\n";
    cout << CONSULTAR << ". Registrarse\n";
    cout << DEPOSITAR << ". Iniciar Sesion\n";
    cout << "Seleccione una opcion: ";
    cin >> opcion;
    if (opcion == CONSULTAR){
        string usuario, pass;
        cout << "Ingrese nombre de usuario: ";
        cin >> usuario;
        cout << "Ingrese una contrasenia: ";
        cin >> pass;
        CuentaBancaria cuenta(usuario, pass);
        cuenta.GuardarEnArchivo();
        cout << "Cuenta creada exitosamente. Iniciando sesion automaticamente...\n";
        MenuUsuario(cuenta);
    }
    else if (opcion == DEPOSITAR){
        string usuario, pass;
        cout << "Ingrese nombre de usuario: ";
        cin >> usuario;
        CuentaBancaria cuenta;
        if(cuenta.CargarDeArchivo(usuario)){
            cout << "Ingrese su contrasena: ";
            cin >> pass;
            if(cuenta.VerificarPassword(pass)){
                cout << "Inicio de sesion exitoso.\n";
                MenuUsuario(cuenta);
            }
            else cout << "Contrasena incorrecta.\n";
        }
        else cout << "Usuario no encontrado.\n";
    }
    else cout << "Opcion no valida.\n";
    return 0;
}