#ifndef ARBOL_H
#define ARBOL_H
/*
 *Los includes deben estar dentro de los guardianes de include para evitar que el precompilador incluya la misma clase varias veces, lo que
lleva a errores al compilar.
*/
#include "Nodo.h" /*Como usaremos objetos tipo Nodo, debemos incluirlo. Recordatorio: Siempre que necesitemos incluir una clase para x o y motivos,
                    incluimos el archivo .h, por como funciona el compilador de c++.*/
using namespace std;
class Arbol
{
    //DECLARACIÓN DE ATRIBUTOS
private:
    Nodo* root;
public:
    //DECLARACIÓN DE METODOS (SU FIRMA)
    Arbol();
    void insertarNodo(int valor, Nodo* root);
    Nodo* insertarNodoRec(int valor, Nodo* actual);
    static Nodo* balancear(Nodo* actual);
    static Nodo* rotarSimpleDerecha(Nodo* z);
    static Nodo* rotarSimpleIzquierda(Nodo* z);
    static Nodo* rotarDobleIzquierda(Nodo* z);
    static Nodo* rotarDobleDerecha(Nodo* z);
    void eliminarNodo(int valor, Nodo* root);
    Nodo* eliminarNodoRec(int valor, Nodo* actual);
    Nodo* obtenerMinNodo(Nodo* actual);
    bool busquedaUno(Nodo* actual, int valor);
    void imprimirDatos(Nodo* actual);
    bool busquedaPreorden(Nodo* actual, int valor);
    bool busquedaInorden(Nodo* actual, int valor);
    bool busquedaPostorden(Nodo* actual,int valor);
    //GETTER
    Nodo* getRoot() const { return root;}
    //SETTER
    void setRoot(Nodo* root) { this->root=root;}
};

#endif //ARBOL_H
