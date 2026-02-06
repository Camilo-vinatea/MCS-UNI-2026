#include "types.h"

// 1. Bernaola Gayoso - César Raúl
template <typename T>
T addition(T a, T b) { 
    return a + b;
}

// 2. Cuadros-Vargas Ernesto
template <typename T>
void intercambiar(T &a, T &b){
    T tmp = a;
    a     = b;
    b     = tmp;
}

// 3. Diaz Tapia Adderly
double subtraction (Ts n, Ts m);

// 4. Lopez Flores Royer Amed
// multiplication
MultParam multiplicar(MultParam &a, MultParam &b);
// 5. López Sandoval, Heiner
// division
float division(float &f1, float &f2);

// 6. Mallaupoma Cesar
// genera un numero aleatorio
int generarNumAleatorio();

// 7. Miranda Zarate Jorge Luis
unsigned int factorial(unsigned int number);
// factorial

// 8. Riveros Guevara
// IsPrime
bool esPrimo(int &n);

// 9. Segovia Giancarlo
// fibonacci
template <typename T>
T fibonacci(T n){
    if(n <= 0) return 0;
    if(n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// 10. Suarez Maciel Susana Isabel
// average()
float average(int x, int y);

// 11. Tellez Jhon
// sumar 10 numeros naturales

// 12. Valcarcel Julian
// float round(float f, int n)

// 13. Vilca Aguilar Luis
// root
float raiz(float a);

// 14. Vinatea Chávez Camilo Jorge
float power(float base, int exponent);
