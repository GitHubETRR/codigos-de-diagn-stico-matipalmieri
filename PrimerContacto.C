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
            cout << "\n\033[1;31mNo hay historial disponible.\033[0\n";
            return;
        }
        cout << "\n\033[1;35m- - - Historial de Transacciones - - -\033[0m\n";
        string linea;
        while (getline(archivo, linea)) cout << linea <<"\n";
        archivo.close();
    }
};

void MenuUsuario(CuentaBancaria &cuenta){
    int opcion;
    do{
        cout << "\n\033[1;36m- - - Menu de Usuario - - -\033[0m\n";
        cout << CONSULTAR << ". Consultar saldo\n";
        cout << DEPOSITAR << ". Depositar\n";
        cout << RETIRAR << ". Retirar\n";
        cout << HISTORIAL << ". Ver historial\n";
        cout << SALIR << ". Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        if (opcion == CONSULTAR) cout << "\033[1;33m----> Saldo actual: $ \033[0m" << fixed << setprecision(2) << cuenta.GetSaldo() << endl;
        else if(opcion == DEPOSITAR){
            double monto;
            cout << "Monto a depositar: $";
            cin >> monto;
            cuenta.Depositar(monto);
            cout << "\033[1;32mDeposito exitoso.\033[0m\n";
        } 
        else if(opcion == RETIRAR){
            double monto;
            cout << "Monto a retirar: $";
            cin >> monto;
            if(cuenta.Retirar(monto)) cout << "\033[1;32mRetiro exitoso.\033[0m\n";
            else cout << "\033[1;31mFondos insuficientes.\033[0m\n";
        }
        else if(opcion == HISTORIAL) cuenta.MostrarHistorial();
    } while(opcion != SALIR);
    cuenta.GuardarEnArchivo();
}

int main(){
    int opcion;
    cout << "\n\033[1;34m= = = SISTEMA BANCARIO = = =\033[0m\n";
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
        cout << "\033[1;32mCuenta creada exitosamente. Iniciando sesion automaticamente...\033[0\n";
        MenuUsuario(cuenta);
    }
    else if (opcion == DEPOSITAR){
        string usuario, pass;
        cout << "Ingrese nombre de usuario: ";
        cin >> usuario;
        CuentaBancaria cuenta;
        if(cuenta.CargarDeArchivo(usuario)){
            cout << "Ingrese su contrasenia: ";
            cin >> pass;
            if(cuenta.VerificarPassword(pass)){
                cout << "\033[1;32mInicio de sesion exitoso.\033[0m\n";
                MenuUsuario(cuenta);
            }
            else cout << "\033[1;31mContrasena incorrecta.\033[0m\n";
        }
        else cout << "\033[1;31mUsuario no encontrado.\033[0m\n";
    }
    else cout << "\033[1;31mOpcion no valida.\033[0m\n";
    return 0;
}