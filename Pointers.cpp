#include <iostream>
#include <string>
#include "Pointers.h"
#include "util.h"

using namespace std;

void DemoBasico(){
    int x    = 10;
    int* ptr = nullptr, *ptr2 = nullptr, *ptr3;
    
    ptr  = &x; // ptr apunta a x
    ptr2 = &x;
    ptr3 = ptr2;

    cout << "Valor de x    : " << x << endl; // git rImprime el valor de x
    cout << "Direccion de x: " << &x << endl; // Imprime la dirección de x
    cout << "Valor   de ptr: " << ptr << endl; // Imprime la dirección almacenada en ptr (dirección de x)
    cout << "Valor apuntado por ptr: " << *ptr << endl; // Imprime el valor al que apunta ptr (valor de x)
    cout << endl;

    *ptr = 20; // Modifica el valor de x a través del puntero
    cout << "Nuevo valor de x: " << x << endl; // Imprime el nuevo valor de x
    cout << "Direccion de x  : " << &x << endl; // Imprime la dirección de x
    cout << "Valor   de ptr  : " << ptr << endl; // Imprime la dirección almacenada en ptr (dirección de x)
    cout << "Valor apuntado por ptr: " << *ptr << endl; // Imprime el valor al que apunta ptr (valor de x)

    *ptr3 = 50;
    cout << "Nuevo valor de x: " << x << endl; // Imprime el nuevo valor de x
}

void f1(T1  n)  {    ++n;   } // n pasa por valor, no afecta la variable enviada
void f2(T1 &n)  {    ++n;   } // C++ style n pasa por referencia, afecta la variable enviada
void f3(T1 *px){ // C-style pi es un puntero a un int, afecta la variable enviada
    ++*px;          // Modifica la variable a la que apunta
    px = nullptr;   // Esto no afecta al puntero original, solo cambia la copia local de pi
}
void f4(T1 *&px){ // C++ style pi es una referencia a un puntero a un int, afecta la variable enviada
    ++*px;          // Modifica la variable a la que apunta
    px = nullptr;   // Esto sí afecta al puntero original, lo hace apuntar a nullptr
}

void f5(T1 **pp){
    ++**pp;         // Modifica la variable a la que apunta el puntero al que pp apunta
    *pp = nullptr;  // Esto hace que el puntero al que pp apunta ahora apunte a nullptr
}

void DemoParametros(){
    T1   x = 10, &r = x; // r es una referencia a x
    auto y = x+20;

    T1  *pi = &x;
    T1 **pp = &pi;

    aviso("Valor de x antes   de llamar a f1: ", x); // Imprime el valor de x antes de llamar a f1
    f1(x); // Llama a la función f1 pasando x por valor
    aviso("Valor de x después de llamar a f1: ", x); // Imprime el valor de x después de llamar a f1 (no cambia)
    f1(25);
    f1(x+30);
    f1(y);
    aviso("Valor de y después de llamar a f1: ", y);

    cout << "f2" <<endl;
    x = 10;
    f2(x); // Llama a la función f2 pasando x por referencia
    aviso("Valor de x después de llamar a f2: ", x);
    f2(r); // Llama a la función f2 pasando r por referencia
    aviso("Valor de x después de llamar a f2(r): ", x);
    f2(y);
    aviso("Valor de y después de llamar a f1: ", y);
    // f2(x+30); // No se puede pasar una expresión a una función que espera una referencia no constante
    f2(*pi);
    aviso("Valor de x después de llamar a f1: ", x);
    // f2(35); // No se puede pasar un literal a una función que espera una referencia no constante

    cout << "f3" <<endl;
    x = 10; y = x+20;
    f3(&x); // Llama a la función f3 pasando la dirección de x
    aviso("Valor de x después de llamar a f3: ", x);
    f3(pi); // Llama a la función f3 pasando el puntero pi
    aviso("Valor de x después de llamar a f3: ", x);
    f3(&y); // Llama a la función f3 pasando la dirección de y
    aviso("Valor de y después de llamar a f3: ", y);

    cout << "f4" <<endl;
    x = 10; y = x+20;
    f4(pi); // Llama a la función f4 pasando el puntero pi
    aviso("Valor de x después de llamar a f4: ", x);
    aviso("Valor de pi después de llamar a f4: ", pi);
    // *pi = 50; // Esto causará un error de segmentación porque pi ahora es nullptr
    pi = &x; // Restauramos pi para evitar el error

    f4(*pp); // pp apunta a pi, *pi apunta a x
    aviso("Valor de x después de llamar a f4: ", x);
    aviso("Valor de pi después de llamar a f4: ", pi);

    pi = &x;
    cout << "f5" <<endl;
    x = 10; y = x+20;
    f5(pp); // Llama a la función f5 pasando el puntero a pi
    aviso("Valor de x después de llamar a f5: ", x);
    aviso("Valor de pi después de llamar a f5: ", pi);
}

struct S{
    T1   a;
    T2   b;
    char nom[30];
};

void PrintS(S &s){
    // s.a = 100; // Modifica el miembro a de la estructura s
    cout <<   "a  : " << s.a
         << ", b  : " << s.b
         << ", nom: " << s.nom << endl;
}

void PrintT(S *pS){
    PrintS(*pS);
}

void DemoEstructuras(){
    S s1 = {10, 3.14, "Ejemplo"};
    s1.b = 2.718;
    cout << "Acceso a miembros de la estructura directamente:" << endl;
    cout << "s1.a  : " << s1.a   << endl; // Acceso al miembro a
    cout << "s1.b  : " << s1.b   << endl; // Acceso al miembro b
    cout << "s1.nom: " << s1.nom << endl; // Acceso al miembro nom
    
    S *ps = &s1;
    ps->a = 20; // Modifica el miembro a a través del puntero
    cout << "Acceso a miembros de la estructura usando el puntero ps:" << endl;
    cout << "s1.a  : " << ps->a   << endl; // Acceso al miembro a
    cout << "s1.b  : " << ps->b   << endl; // Acceso al miembro b
    cout << "s1.nom: " << ps->nom << endl; // Acceso al miembro nom

    cout << "Usando la función PrintS para mostrar los valores de la estructura:" << endl;
    PrintS(s1); // Llama a la función PrintS pasando la estructura por referencia
    PrintS(*ps); // Llama a la función PrintS pasando la estructura a través del puntero

    cout << "Usando la función PrintT para mostrar los valores de la estructura:" << endl;
    PrintT(&s1); // Llama a la función PrintT pasando la direccion de la estructura 
    PrintT(ps);  // Llama a la función PrintT pasando la estructura a través del puntero

    S as[3] = {
        {1, 1.1, "Uno"},
        {2, 2.2, "Dos"},
        {3, 3.3, "Tres"}
    };
    as[0].a = 20; // Modifica el miembro a del primer elemento del arreglo
    cout << "Imprimiendo estructuras en un arreglo (PrintS):" << endl;
    for(auto i = 0; i < 3; ++i)
        PrintS(as[i]);
    cout << "Imprimiendo estructuras en un arreglo (PrintT):" << endl;
    for(auto i = 0; i < 3; ++i)
        PrintT(&as[i]);
    cout << "Imprimiendo con un bucle mas corto:" << endl;
    for(auto &s1 : as)
        PrintS(s1);
    cout << "sizeof(S): " << sizeof(S) << endl;
}

void DemoPunteros(){
    DemoBasico();
    DemoParametros();
    DemoEstructuras();
}