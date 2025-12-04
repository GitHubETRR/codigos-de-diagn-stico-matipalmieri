#include <iostream>
#include <vector>
using namespace std;

class Animal{
public:
    string nombre;
    Animal(string n) : nombre(n) {}
    void comer() {
        cout << nombre << " está comiendo." << endl;
    }
    virtual void hacerSonido(){
        cout << nombre << " hace un sonido desconocido." << endl;
    }
    virtual ~Animal() {}
};

class Perro : public Animal{
public:
    Perro(string n) : Animal(n) {}
    void hacerSonido() override{
        cout << nombre << " dice: Guau" << endl;
    }
};

class Gato : public Animal{
public:
    Gato(string n) : Animal(n) {}
    void hacerSonido() override{
        cout << nombre << " dice: Miau" << endl;
    }
};

int main(){
    vector<Animal*> animales;
    animales.push_back(new Perro("Kala"));
    animales.push_back(new Gato("Suri"));
    animales.push_back(new Perro("Sasha"));
    for (Animal* a : animales){
        a->comer();
        a->hacerSonido();
        cout << endl;
    }
    for (Animal* a : animales){
        delete a;
    }
    return 0;
}
