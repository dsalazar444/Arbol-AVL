#include "Nodo.h"
#include <iostream>
#include <algorithm>
using namespace std;
/*no hay que poner class... porque eso ya lo indicamos en .h, y estos archivos se "complementan", entonces aquí solo implementamos los métodos.
debemos indicar a qué clase pertenece el metodo (Nodo::metodo), ya que podemos tener varios include de diferentes clases*/

//IMPLEMENTACIÓN DE LOS MÉTODOS DE NODO.H
Nodo::Nodo(int valor):dato(valor),pntDerecha(nullptr),pntIzquierda(nullptr),altura(1){}; //Implementamos constructor
/*La estructura para crear un constructor en C++ es:
Clase::Clase(parametros) : atributo1(valor1), atributo2(valor2) {
    Cuerpo del constructor
}
lo que va despues de : se llama lista inicializadora, y es donde asignamos los valores de los atributos del constructor, a diferencia de Java, que lo
hacemos en el cuerpo del constructor
*/
//Implementación de una función estática
//Obtener altura de un nodo
int Nodo::getAltura(Nodo* actual)
{
    /*
    esto es util ya que en calcularAltura o calcularFactor, en las lineas actual->getPntDerecha()->getAltura(); si el hijo derecho de actual no existe,
    su puntero es null, no podemos restar un null con un número, asi que debemos manejar ese caso, pero eso se deberia hacer en ambas funciones, por lo que es
    más fácil hacerlo en una función aparte, que es getAltura, esto no lo podriamos haber hecho en la funcion getPntDerecha/Izquierda directamente porque
    en otras partes del codigo si necesitamos que retorne null.
    */
    if(actual == nullptr)
    {
        return 0;
    }
    return actual->altura;
}
//Calcular y establecer altura de un nodo
void Nodo::calcularAltura()
{
    /*
     * La altura de un nodo esta dada por la altura máxima de sus hijos más uno, pues al ser un padre será una unidad más "alto" que sus hijos
     */
    int altura = 1 + max(getAltura(this->getPntIzquierda()), getAltura(this->getPntDerecha()));
    this->setAltura(altura); //establecemos altura del nodo.
}
//Calculamos el factor de balance (alturaHijoIzq - alturaHijoDer) respecto a un nodo
int Nodo::calcularFactorBalance(Nodo* actual)
{   /* el return 0 lo aplique porque me salia error al querer obtener el puntero izquierdo/derecho del puntero izquierdo/derecho del nodo, o sea, el nieto de actual,
    porque el hijo era null, entonces null no tiene un ptroDerecha o ptrIzquierda, es decir, no existia el nieto, entonces yo intentaba sacar la altura
    de algo que no exisitia y salia error.
    */
    if(actual == nullptr)
    {
        return 0;
    }
    return getAltura(actual->getPntIzquierda()) - getAltura(actual->getPntDerecha()); //calculamos factor de balance y lo retornamos
}


