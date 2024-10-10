#include <iostream>
#include <string>
#include "Nodo.h"
#include "Arbol.h"
using namespace std;
int main(){
    auto* arbol=new Arbol();
    /*porque estamos creando un objeto tipo puntero, entonces debe ser arbol* y no arbol, pues con new creamos punteros.
    Con auto, el compilador deduce el tipo del puntero dependiendo del constructor usado, en nuestro caso deducira que es tipo Nodo, con esto se
    simplifica el realizar cambios en el código, además de que lo hace más legible
    */
    //AÑADIMOS NODOS AL ARBOL
    arbol->insertarNodo(30, arbol->getRoot());
    arbol->insertarNodo(20, arbol->getRoot());
    arbol->insertarNodo(40, arbol->getRoot());
    arbol->insertarNodo(25, arbol->getRoot());
    arbol->insertarNodo(29, arbol->getRoot());
    arbol->insertarNodo(10, arbol->getRoot());
    arbol->insertarNodo(15, arbol->getRoot());
    arbol->insertarNodo(45, arbol->getRoot());
    arbol->insertarNodo(32, arbol->getRoot());
    arbol->insertarNodo(28, arbol->getRoot());
    arbol->insertarNodo(55, arbol->getRoot());
    arbol->insertarNodo(60, arbol->getRoot());
    arbol->insertarNodo(24, arbol->getRoot());

    //ELIMINAMOS DATOS DEL ARBOL
    arbol->eliminarNodo(10,arbol->getRoot());
    arbol->eliminarNodo(40,arbol->getRoot());
    arbol->eliminarNodo(45,arbol->getRoot());
    arbol->eliminarNodo(15,arbol->getRoot());
    arbol->eliminarNodo(30,arbol->getRoot());

    //BUSCAMOS ELEMENTOS EN ARBOL
    arbol->busquedaUno(arbol->getRoot(),60);
    arbol->busquedaUno(arbol->getRoot(),10);
    arbol->busquedaUno(arbol->getRoot(),40);

    //IMPRIMIMOS DATOS DEL ARBOL
    cout<<"Los datos del arbol son: "<<endl;
    arbol->imprimirDatos(arbol->getRoot());
    //VERIFICAMOS FUNCIONALIDAD DE BUSQUEDAS CON DIFERENTES MÉTODOS
    //Metodo preorden
    if (arbol->busquedaPreorden(arbol->getRoot(), 60)) {
        cout << "Valor encontrado en preorden!" << endl;
    } else {
        cout << "Valor no encontrado en preorden!" << endl;
    }
    //Metodo inprden
    if (arbol->busquedaInorden(arbol->getRoot(), 60)) {
        cout << "Valor encontrado en inorden!" << endl;
    } else {
        cout << "Valor no encontrado en inorden!" << endl;
    }
    //Metodo postprden
    if (arbol->busquedaPostorden(arbol->getRoot(), 60)) {
        cout << "Valor encontrado en postorden!" << endl;
    } else {
        cout << "Valor no encontrado en postorden!" << endl;
    }
}

