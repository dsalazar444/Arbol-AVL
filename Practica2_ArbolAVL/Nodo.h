#ifndef NODO_H
#define NODO_H
class Nodo
{
    //DECLARAMOS LOS ATRIBUTOS DE LA CLASE
private:
    int dato;
    Nodo* pntDerecha; //porque apuntan a un nodo, a pesar de que el objeto (el nodo) al que apunta guarde un int, pues el dato del puntero
    //está dado por el objeto al que apunta, sin importar qué guarde este
    Nodo* pntIzquierda;
    int altura;

public:
    //DECLARAMOS LA FIRMA DE LOS METODOS QUE TENDRA LA CLASE, estos van sin llaves ({})
    Nodo(int valor); // Declaración del constructor (sin {})
    /*
    GETTERS, pues los atributos son privados.
    le ponemos cons para indicarle al compilador que ese metodo no modificará ningun atributo. Recordatorio: Los objetos constantes solo
    pueden utilizar métodos constantes.
    */
    int getDato() const { return dato;} //ponemos cuerpo a metodos que sean in-line, de resto será en nodo.cpp
    Nodo* getPntDerecha() const { return pntDerecha;}
    Nodo* getPntIzquierda() const { return pntIzquierda;}
    //Declaracion de una funcion estatica
    static int getAltura(Nodo* actual);
    //declaración de función no estatica.
    void calcularAltura();
    int static calcularFactorBalance(Nodo* actual);

    //SETTERS (no le pondemos cons porque sí modificarán atributos)
    void setDato(int dato) { this->dato = dato;}
    void setPntDerecha(Nodo* pnt_derecha) { pntDerecha = pnt_derecha;}
    void setPntIzquierda(Nodo* pnt_izquierda) { pntIzquierda = pnt_izquierda;}
    void setAltura(int altura) { this->altura = altura;}
};

#endif //NODO_H