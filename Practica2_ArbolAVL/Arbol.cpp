#include "Arbol.h"
#include <iostream>
using namespace std;
//IMPLEMENTACIÓN DE METODOS DE ARBOL
//implementamos el constructor del arbol, e inicializamos el atributo root como nullptr
Arbol::Arbol():root(nullptr){};
//Metodo para añadir elementos al arbol, el cual manejara caso "base" (creación del root) y no lo usaremos de forma recursiva
void Arbol::insertarNodo(int valor, Nodo* root)
{
    if (root==nullptr)
    {
        setRoot(new Nodo(valor));//Si no existe root, lo asignamos.
        /*
         *es root y no root->getDato porque no hay dato, pues el puntero es null.
         *Recordemos que los Nodo* deben apuntar a un objeto tipo Nodo, no a un dato int o x, y que como es un objeto tipo puntero, podemos acceder
         *a los metodos del objeto al que apuntamos, pero ojo, no es lo mismo Nodo* a Nodo, o al valor que este guarda, pues el primero es un puntero:
         *Nodo* != Nodo y Nodo != datoDelNodo
        */
    }else
    {
        //Llamamos a función recursiva y le pasamos la raiz y el valor a insertar.
        setRoot(insertarNodoRec(valor,root));
        /*
         *Ponemos setRoot ya que si al insertar un nodo y el arbol se desbalancea, deberemos hacer rotaciones que pueden cambiar el root del arbol,
         *entonces lo que nos retorne la función será el root del arbol, y como la recursividad usa pilas, el último en salir es el primero en
         *entrar, y el primero que entra es la raiz, por ende, será la última en salir (pues es el "último" nodo del árbol, de abajo hacia arriba)
        */
    }
}

//Funcion recursiva para insertar nodos, esta función no insertará un valor que ya existe.
Nodo* Arbol::insertarNodoRec(int valor, Nodo* actual)
{
    if(valor<actual->getDato()) //iremos a subarbol izquierdo
    {
        if(actual->getPntIzquierda() == nullptr) //si a la izquierda del nodo esta vacio, ponga un nuevo nodo ahi con el valor que fue pasado
        {
            actual->setPntIzquierda(new Nodo(valor));
        }else
        {
            /*
             *avanzamos en el arbol al tomar como actual el nodo que está a la izquierda de actual, recorriendolo, y lo que nos retorne será
             *el nodo que quedará a la izquierda del nodo actual de este FRAME (recordemos que en cada llamada recursiva se crea un frame, y en todos
             *estos los datos son diferentes entre ellos, así que para cierto frame, el actual que exista en ese tendrá como izquierda el nodo
             *que retorne el frame que este arriba de él en la pila).
            */
            actual->setPntIzquierda(insertarNodoRec(valor, actual->getPntIzquierda())); /*Propaga el retorno ya que si no, la función en cada
            frame retorna un dato que queda "flotando", y puede llevar a errores en la compilación*/
        }

    }else if(valor>actual->getDato())
        /*
         *iremos a subarbol derecho, en este if usamos la misma lógica que en el anterior, solo que recorriendo el árbol hacia derecha hasta que
         *encuentre un espacio donde pueda insertar el nodo, es decir, donde actual->derecha sea null
         */
    {
        if(actual->getPntDerecha() == nullptr)
        {
            actual->setPntDerecha(new Nodo(valor));
        }else
        {
            actual->setPntDerecha(insertarNodoRec(valor, actual->getPntDerecha())); // Propaga el retorno
        }
    }
    /*Como al insertar nodos siempre iremos hasta nodos hojas, ya que no insertamos datos en mitad de una rama, nos aseguramos que al hacer pop
     *en la pila de recursión, tomaremos los nodos de abajo hacia arriba (nos devolveremos en el árbol) y les calcularemos la altura y si está
     *desbalanceado,y aunque actual nunca tomará un nodo hoja por la lógica con la que cree el metodo, no es necesario ya que estos los creamos
     *con altura 1 y nunca, respecto a estos, será el desbalance.
    */
    actual->calcularAltura();
    /*
     *primero calculamos altura antes de balancear, ya que esta última depende de la altura de los nodos, y retornamos el nodo,
     *cualesquiera que sea, que nos retorne balancear, pues realizaremos rotaciones, entonces debemos devolvernos en el árbol a partir de
     *donde nos dejen estas
     */
    return balancear(actual);
}

//Metodo en donde miraremos si hay un desbalance, y si lo hay, llamamos los métodos para hacer las rotaciones
Nodo* Arbol::balancear(Nodo* actual)
{
    //Calculamos los factores del padre y los hijos, pues estos nos indicarán qué tipo de rotación realizar
    int factorPadre, factorHijoIzq, factorHijoDer;

    factorPadre=Nodo::calcularFactorBalance(actual);
    factorHijoIzq=Nodo::calcularFactorBalance(actual->getPntIzquierda());
    factorHijoDer=Nodo::calcularFactorBalance(actual->getPntDerecha());

    /*
     *Si los factores del padre y del hijo tienen mismo signo, realizaremos rotaciones simples, si tienen diferente, realizaremos dobles.
     *Recodemos que el signo del factor nos dice hacia donde esta el debalance, pues en a-b (izquierda-derecha), si el resultado es positivo es
     *porque a es mayor, en nuestro caso, ese subarbol tiene más hijos, y si es negativo, lo mismo.
     */
    if(factorPadre>1 && factorHijoIzq>=0) //si desbalance es hacia la izquierda, rotamos a la derecha.
    {
        return rotarSimpleDerecha(actual);
    }
    if(factorPadre<-1 && factorHijoDer<=0)//si desbalance es hacia la derecha, rotamos a la izquierda.
    {
        return rotarSimpleIzquierda(actual);
    }
    if(factorPadre>1 && factorHijoIzq<0) //Indica que hay un zigzag, pues padre tiene un desbalance hacia un lado, y el hijo hacia otro, asi que debemos
        //rotar de tal forma que quede un desbalance simple, es decir, hijo y padre tengan mismo signo.
    {
        return rotarDobleDerecha(actual);
    }
    if(factorPadre<-1 && factorHijoDer>0)
    {
        return rotarDobleIzquierda(actual);
    }
    return actual; //si no hay un desbalance, retornamos actual, pero si entra en alguna condición, se retornara el nodo que retornen las rotaciones
    //recordemos que solo llegara hasta acá si no entra en ningun if por como funcionan los return en las funciones.
}
// Metodo donde rotamos hacia la derecha
Nodo* Arbol::rotarSimpleDerecha(Nodo* z)
{
    //Usamos como guia los nombres de los nodos del ejemplo al explicar rotaciones.
    Nodo* y =z->getPntIzquierda();
    Nodo* l3 =y->getPntDerecha();
    y->setPntDerecha(z);
    z->setPntIzquierda(l3);
    /*
     *actualizamos altura de los nodos z,y ya que fueron los que rotamos.
     *OJO, el orden en que actualizamos la altura de los nodos importa, ya que como 'y' tiene como hijo a 'z', debemos calcular primero la
     *altura de 'z' y luego la de 'y'.
     */
    z->calcularAltura();
    y->calcularAltura();
    /* retornamos 'y' porque ya debimos de haber recorrido 'z' y 'l3' puesto que estamos calculando el balance en z, y debemos de actualizar aca
     * sus alturas pues dejaremos "atrás" esos nodos, ya que no estan en la pila de añadirRec, entonces estas operaciones no las haremos en esa funcion
     * por lo que las tenemos que hacer acá
     * devolvemos "y" porque debemos dejar el recorrido en el mismo lugar, y ese mismo lugar ya esta ocupado por "y" en lugar de "z"*/
    return y;
}
// Metodo donde rotamos hacia la izquierda
Nodo* Arbol::rotarSimpleIzquierda(Nodo* z)
{
    //Misma lógica que rotarSimpleDerecha.
    Nodo* y=z->getPntDerecha();
    Nodo* l2=y->getPntIzquierda();
    y->setPntIzquierda(z);
    z->setPntDerecha(l2);
    //actualizamos alturas
    z->calcularAltura();
    y->calcularAltura();
    return y;
}
// Metodo donde hacemos rotación doble hacia la izquierda
Nodo* Arbol::rotarDobleIzquierda(Nodo* z)
{
    z->setPntDerecha(rotarSimpleDerecha(z->getPntDerecha()));//El puntero de z derecha será el nodo que retorne la rotacion simple a la derecha,
    //es decir, el root de ese subarbol, y ya el subarbol de z lo rotamos a la izquierda.
    return rotarSimpleIzquierda(z);
}
// Metodo donde hacemos rotación doble hacia la derecha
Nodo* Arbol::rotarDobleDerecha(Nodo* z)
{
    //misma lógica que rotarDobleIzquierda.
    z->setPntIzquierda(rotarSimpleIzquierda(z->getPntIzquierda()));
    return rotarSimpleDerecha(z);
}
/*Metodo donde obtenemos valor minimo albergado en el árbol, esto lo hacemos recorriendo el árbol por la rama izquierda de este, que es donde
 *se almacenan los valores menores.
 */
Nodo* Arbol::obtenerMinNodo(Nodo* actual)
{
    while(actual->getPntIzquierda() != nullptr) //porque si pongo solo actual != nullptr siempre me retornara nullptr, no el nodo menor
    {
        actual=actual->getPntIzquierda(); //recorremos rama izquierda
    }
    return actual;
}
//Metodo para añadir elementos al arbol, el cual manejara caso "base" (árbol vacio) y no lo usaremos de forma recursiva
void Arbol::eliminarNodo(int valor, Nodo* root)
{
    if(root==nullptr)
    {
        cout<<"El árbol está vacío, por lo que no hay elementos para eliminar"<<endl;
    } else
    {
        setRoot(eliminarNodoRec(valor, root)); //Porque al realizar rotaciones el root cambiará
    }
}

//Funcion recursiva para insertar nodos.
Nodo* Arbol::eliminarNodoRec(int valor, Nodo* actual)
{
    /*Al eliminar nodos, se pueden dar 3 casos, eliminar nodos:
     * hoja ->puntero de padre se actualiza a nullptr
     * con un hijo-> el hijo del nodo a eliminar reemplaza a este, es decir, si el nodo a eliminar era izquierda de un nodo, ya la izquierda de ese
     * nodo será el hijo de este nodo a eliminar, esto lo logramos propagando los return.
     * con dos hijos-> obtenemos el valor minimo del subarbol derecho del nodo a eliminar, y reescribimos el valor del nodo a eliminar, para luego eliminar
     * el nodo del que tomamos el valor (nodo minimo)
     */
    if(valor<actual->getDato()) //recorremos el subarbol derecho
    {
        actual->setPntIzquierda(eliminarNodoRec(valor,actual->getPntIzquierda())); //propagamos retorno, lo cual es importante al hacer
        //cambios en un árbol AVl
    }else if(valor>actual->getDato())//recorremos el subarbol  izquierdo
    {
        actual->setPntDerecha(eliminarNodoRec(valor,actual->getPntDerecha()));
    }else
    {
        if(actual->getPntIzquierda()==nullptr) //Es decir, si solo tiene un hijo, pues uno de sus lados es nullptr
        {
            return actual->getPntDerecha();// el otro hijo reemplaza al padre, como explique a inicio de método.
        }
        if(actual->getPntDerecha()==nullptr)
        {
            return actual->getPntIzquierda();
        }
        //si no dentra en ninguno de los if, es porque tiene dos hijos.
        Nodo* aux= obtenerMinNodo(actual->getPntDerecha());
        //pasamos el nodo a la derecha de actual, porque debemos tomar el subarbol derecho, y encontrar el minimo ahi
        actual->setDato(aux->getDato());
        //copiamos el valor de minimo, "eliminando" actual, pero ahora debemos eliminar el nodo del valor que copiamos, pues no queremos datos iguales
        actual->setPntDerecha(eliminarNodoRec(aux->getDato(),actual->getPntDerecha()));
        /*recorremos subarbol derecho para borrar dato repetido, esto nos obliga a llegar hasta una hoja, haciendo que al hacer pop en la pila de
         *recursividad todos los nodos sean recalculados en altura y se verifique su balanceo.
         */
    }
    //misma logica que en añadir nodo
    actual->calcularAltura();
    return balancear(actual);

}

/* Creamos un metodo de busqueda para un elemento en especifico
 * Requerimos de los parametros actual (posición que se encuentra el puntero en ese momento) y el valor el cual se quiere buscar en el arbol
 * (valor ingresado).
 */
bool Arbol::busquedaUno(Nodo* actual, int valor){
    // Creamos un condicional el cual evalua si el nodo está vacío, si es así es porque hemos llegado al final, no hay más nodos y el elemento
    //no se encuentra en el árbol, puesto que todavia estamos en la funcion (el return no nos ha "sacado").
    if(actual == nullptr)
    {
        cout<<"El dato "<<valor<<" no se encuentra en el arbol"<<endl;
        return false;
    }
    /* Con este condicional comparamos el valor del nodo actual con el valor que estamos buscando, y si coinciden arrojamos true,
     * eso nos indica que si existe ese valor en el arbol*/
    if(actual->getDato() == valor)
    {
        cout<<"Encontre nodo con dato "<<valor<<endl;
        return true;
    }
    //Este útlimo if nos sirve para verificar si el valor ingresado es menor que el dato del nodo actual, continúa la búsqueda en el subárbol izquierdo
    if(valor < actual->getDato())
    {
        return busquedaUno(actual->getPntIzquierda(), valor);
     // Y si el valor es mayor, continúa la búsqueda en el subárbol derecho
    }else
    {
        return busquedaUno(actual->getPntDerecha(), valor);
    }
}
//Funcion para imprimir datos del arbol
void Arbol::imprimirDatos(Nodo* actual)
{
    // Verificamos si el arbol no está vacío (el nodo actual no esté vacío)
    if (actual == nullptr){
        // Si llega a cumplirse simplemente no se imprime nada
        return;
    }
    /*Aquí es donde llegamos a requerir el uso de recursividad, que primeramente imprime el subárbol izquierdo, en la zona de
     *"std::cout << actual->dato << "  ";", y luego de eso hacemos llamado con ayuda de recursividad nuevamente a la funcion imprimirDatos, pero
     *para el subárbol derecho
     */
    imprimirDatos(actual->getPntIzquierda());

    // Esta línea se encarga de imprimir el dato del nodo que se está cargando en ese momento
    cout << actual->getDato() << "  "<<endl;

    // Lo mismo que en el caso del subárbol izquierdo.
    imprimirDatos(actual->getPntDerecha());
}

// TRES RECORRIDOS PARA LA BUSQUEDA DE UN VALOR :)
//   LOS TRES MÉTODOS DE BUSQUEDA PARA EL ARBOLITO

// Primer metodo: recorrido por preorden, va de raíz, izquierda, derecha
bool Arbol::busquedaPreorden(Nodo* actual, int valor){
        // este condicional nos avisa cuando hemos llegado al extremo del arbolito, ya que no encuentra nada y nos devuelve false
    if(actual==nullptr)
    {
        return false;
    }
        // Con este condicional verificamos cuadno el valor del Nodo actual es igual al que estamos buscando, asi que nos arroja true
    if(actual->getDato()== valor){
        return true;
    }
        // ------------------------Uso de recursividad--------------------------
        // Para este ultimo caso lo que hace es que si no encuentra el valor en el nodo actual irá a buscar al subarbol izquierdo y luego al derecho
    if(busquedaPreorden(actual->getPntIzquierda(), valor ))
    {
        return true;
    }
        // busqueda hacia la derecha
    return busquedaPreorden(actual->getPntDerecha(), valor);
    }


// Segundo metodo: recorrido Inorden, va de izquierda, raíz, derecha
bool Arbol::busquedaInorden(Nodo* actual, int valor){
        // Con este condicional comprobamos que no halló el valor
    if(actual==nullptr)
    {
        return false;
    }
        // Este condiocnal lo que hace es buscar con el subarbolito izquierdo el valor, al hallarlo devolverá un true
    if (busquedaInorden(actual->getPntIzquierda(), valor)) {
        return true;
    }
        // En este condicional se verifica si el valor actual coincide con el valor
    if (actual->getDato() == valor)
    {
        return true;
    }
        // Luego buscamos el valor en el lado derecho
    return busquedaInorden(actual->getPntDerecha(), valor);

}

// Tercer metodo: recorrido postorden, va de izquierda, derecha, raíz
bool Arbol::busquedaPostorden(Nodo* actual,int valor) {
    if (actual == nullptr)
    {
        return false;
    }
        // Con este condicional buscamos por el lado izquierdo, es el mismo proceso que en los anteriores
    if (busquedaPostorden(actual->getPntIzquierda(), valor )) {
        return true;
    }
        // Luego con este condicional buscamos por el subarbolito derecho, el mismo proceso
    if (busquedaPostorden(actual->getPntDerecha(),valor))
    {
        return true;
    }
        // En este apartado lo que se hace es verificar el nodo actual (el mismo proceso que los anteriores)
    if (actual->getDato() == valor)
    {
        return true;
    }
        // En los tres casos aseguramos que si se llega a encontrar algo, devolvemos un true, si no es así, o sea, que no entra en ninguno de
        // esos tres casos, nos devolverá un false
    return false;
}