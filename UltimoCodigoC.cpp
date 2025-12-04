#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

enum MENU{
    AGREGAR = 1,
    LISTAR,
    BUSCAR,
    PRESTAR,
    DEVOLVER,
    SALIR
};

struct Libro{
    string titulo;
    string autor;
    int year;
    bool prestado;
};

class Biblioteca{
private:
    vector<Libro> libros;
public:
    void Agregar(const Libro& l){ 
        libros.push_back(l);
    }
    void Listar() const{
        if(libros.empty()){
            cout << "\033[1;31mNo hay libros en la biblioteca\033[0m\n";
            return;
        }
        cout << " \033[1;36m- - - LISTA DE LIBROS - - - \033[0m\n";
        for(size_t i = 0; i < libros.size(); i++){
            cout << i + 1 << ". " << libros[i].titulo
                 << " | " << libros[i].autor
                 << " | " << libros[i].year
                 << " | " << (libros[i].prestado ? "Prestado" : "Disponible")
                 << "\n";
        }
    }

    void Buscar(const string& titulo) const{
        bool encontrado = false;
        for(auto &l : libros){
            if (l.titulo == titulo){
                cout << "Encontrado: " << l.titulo
                     << " | " << l.autor
                     << " | " << l.year
                     << " | " << (l.prestado ? "Prestado" : "Disponible") << "\n";
                encontrado = true;
            }
        }
        if(!encontrado) cout << "\033[1;31mNo se encontro el libro\033[0m\n";
    }

    void Prestar(const string& titulo){
        for(auto &l : libros){
            if(l.titulo == titulo){
                if (!l.prestado){
                    l.prestado = true;
                    cout << "Libro prestado\n";
                }
                else cout << "\033[1;31mEl libro ya esta prestado en este momento\033[0m\n";
                return;
            }
        }
        cout << "\033[1;31mNo se encontro el libro\033[0m\n";
    }

    void Devolver(const string& titulo){
        for (auto &l : libros){
            if (l.titulo == titulo){
                if (l.prestado){
                    l.prestado = false;
                    cout << "\033[1;32mLibro devuelto con exito\033[0m\n";
                } 
                else cout << "\033[1;32mEl libro no estaba prestado\033[0m\n";
                return;
            }
        }
        cout << "\033[1;31mNo se encontro el libro\033[0m\n";
    }

    void GuardarArchivo(const string& archivo) const{
        ofstream out(archivo);
        for(auto &l : libros) out << l.titulo << ";" << l.autor << ";" << l.year << ";" << l.prestado << "\n";
        out.close();
    }

    void CargarArchivo(const string& archivo){
        ifstream in(archivo);
        if (!in.is_open()) return;
        libros.clear();
        string linea;
        while (getline(in, linea)){
            Libro l;
            size_t p1 = linea.find(';');
            size_t p2 = linea.find(';', p1 + 1);
            size_t p3 = linea.find(';', p2 + 1);
            l.titulo = linea.substr(0, p1);
            l.autor = linea.substr(p1 + 1, p2 - p1 - 1);
            l.year = stoi(linea.substr(p2 + 1, p3 - p2 - 1));
            l.prestado = (linea.substr(p3 + 1) == "1");
            libros.push_back(l);
        }
        in.close();
    }
};

Libro CrearLibro(){
    Libro l;
    cout << "Titulo: ";
    getline(cin, l.titulo);
    cout << "Autor: ";
    getline(cin, l.autor);
    cout << "Year: ";
    cin >> l.year;
    cin.ignore();
    l.prestado = false;
    return l;
}

int main(){
    Biblioteca biblio;
    biblio.CargarArchivo("biblioteca.txt");
    int opcion;
    do{
        cout << "\n\033[1;33m - - - MENU BIBLIOTECA - - -\033[0m\n";
        cout << AGREGAR << ". Agregar libro\n";
        cout << LISTAR << ". Listar libros\n";
        cout << BUSCAR << ". Buscar libro\n";
        cout << PRESTAR << ". Prestar libro\n";
        cout << DEVOLVER<< ". Devolver libro\n";
        cout << SALIR << ". Guardar y salir\n";
        cout << "Opcion: ";
        cin >> opcion;
        cout << "\n";
        cin.ignore();
        switch (opcion){
            case AGREGAR:{
                Libro l = CrearLibro();
                biblio.Agregar(l);
                break;
            }
            case LISTAR:
                biblio.Listar();
                break;
            case BUSCAR:{
                string titulo;
                cout << "Ingresa el titulo a buscar: ";
                getline(cin, titulo);
                biblio.Buscar(titulo);
                break;
            }
            case PRESTAR:{
                string titulo;
                cout << "Ingrese el titulo a prestar: ";
                getline(cin, titulo);
                biblio.Prestar(titulo);
                break;
            }
            case DEVOLVER:{
                string titulo;
                cout << "Ingrese el titulo a devolver: ";
                getline(cin, titulo);
                biblio.Devolver(titulo);
                break;
            }
            case SALIR:
                biblio.GuardarArchivo("biblioteca.txt");
                cout << "Biblioteca guardada. \033[1;31mSaliendo...\033[0m\n";
                break;
            default:
                cout << "\033[1;31mOpcion invalida\033[0m\n";
        }
    }while (opcion != SALIR);
    return 0;
}
