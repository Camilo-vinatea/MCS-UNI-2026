#ifndef __POINTERS_H__
#define __POINTERS_H__
#include <iostream>
#include <string>
using namespace std;

template <typename T>
void aviso(string msg, T x){
    cout << msg << x << endl;
}

void DemoBasico();

// Aqui veremos varios tipos de parametros
void DemoParametros();

void DemoPunteros();
void DemoEstructuras();
void DemoChars();

#endif // __POINTERS_H__