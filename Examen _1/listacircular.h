#ifndef LISTA_H
#define LISTA_H
#include "iostream"
template <class T>
class ListaCircular
{
    class Nodo
    {  private:
        T dato;
        Nodo* siguiente=0;
       public:
           Nodo(T pDato){
               dato=pDato;
               siguiente=0;
           }
           void asignarNodo(Nodo *pSiguiente){
               siguiente=pSiguiente;
           }
           void setSiguiente(Nodo *pSiguiente){
               siguiente=pSiguiente;
           }
           Nodo* getSiguiente(){
               return siguiente;
           }
           T getDato(){
               return dato;
           }
           void setDato(T pDato){
               dato=pDato;
           }
           ~Nodo(){;}
    };


private:
    Nodo *nodoInicio=0;
    Nodo *nodoFinal=0;
    Nodo *nodoActual=0;
public:
    ListaCircular(T dato);
    void avanzarEnLista();
    void agregarFinal(T dato);
    void agregarInicio(T dato);
    void agregarSiguiente(T dato);
    void irNodoInicio();
    int cantidadDeNodos();
    void irNodoFinal();
    bool verSiguiente();
    T getDatoNodoActual();
    void eliminarSiguiente();
    T GetDatoPosicion(int Posicion);
    void SetDatoPosicion(T dato,int Posicion);
    ~ListaCircular();
};
#endif // LISTA_H

template <class T>
ListaCircular<T>::ListaCircular(T dato)
{
    nodoActual= new Nodo(dato);
    nodoFinal=nodoActual;
    nodoInicio=nodoActual;
}

template <class T>
void ListaCircular<T>::agregarSiguiente( T dato){
    Nodo *nuevoNodo= new Nodo(dato);
    if (nodoActual==nodoFinal){
        nuevoNodo->setSiguiente(nodoInicio);

        nodoFinal->setSiguiente(nuevoNodo);
        nodoFinal=nuevoNodo;
    }else{
            nuevoNodo->setSiguiente(nodoActual->getSiguiente());
            nodoActual->setSiguiente(nuevoNodo);
        }
    }

template <class T>
void ListaCircular<T>::agregarInicio(T dato){
    Nodo *nuevoNodo=new Nodo(dato);
    nodoFinal->setSiguiente(nuevoNodo);
    nuevoNodo->setSiguiente(nodoInicio);
    nodoInicio=nuevoNodo;
}

template <class T>
void ListaCircular<T>::agregarFinal(T dato){
    Nodo *nuevoNodo=new Nodo(dato);
    nodoFinal->setSiguiente(nuevoNodo);
    nuevoNodo->setSiguiente(nodoInicio);
    nodoFinal=nuevoNodo;
}
template <class T>
void ListaCircular<T>::avanzarEnLista(){
    if (!(nodoActual==nodoFinal && nodoActual==nodoInicio))
       nodoActual=nodoActual->getSiguiente();
        return;
}
template <class T>
void ListaCircular<T>::irNodoFinal(){
    nodoActual=nodoFinal;
}
template <class T>
void ListaCircular<T>::irNodoInicio(){
    nodoActual=nodoInicio;
}
template <class T>
bool ListaCircular<T>::verSiguiente(){
    if (nodoActual->getSiguiente()==nodoInicio)
        return 0;
    return 1;
}
template <class T>
T ListaCircular<T>::getDatoNodoActual(){
    return nodoActual->getDato();
}
template <class T>
void ListaCircular<T>::eliminarSiguiente(){
    Nodo *nodoSig=nodoActual->getSiguiente();
    if (nodoSig->getSiguiente()==nodoSig){
        return;
    }
    nodoActual->setSiguiente(nodoSig->getSiguiente() );
    delete nodoSig;
}
template <class T>
T ListaCircular<T>::GetDatoPosicion(int Posicion){
    Nodo *NodoAux=0;
    T datoDeRetorno;
    NodoAux=nodoInicio;
    for (int n=0;n<Posicion;n++){
        NodoAux=NodoAux->getSiguiente();
    }
    datoDeRetorno=NodoAux->getDato();
    return datoDeRetorno;
}

template <class T>
int ListaCircular<T>::cantidadDeNodos(){
    Nodo *NodoAux=0;
    int cont=0;
    NodoAux=nodoInicio;
    while(NodoAux->getSiguiente()!=nodoInicio){
        NodoAux=NodoAux->getSiguiente();
        cont++;

    }
    return cont;
}
template <class T>
void ListaCircular<T>::SetDatoPosicion(T dato,int Posicion){
    Nodo *NodoAux=0;
    NodoAux=nodoInicio;
    for (int n=0;n<Posicion;n++){
        NodoAux=NodoAux->getSiguiente();
    }
    NodoAux->setDato(dato);
    NodoAux=0;
    delete NodoAux;
    return;
}

template <class T>
ListaCircular<T>::~ListaCircular(){;}

